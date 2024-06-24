﻿




#include <riscv_vector.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Partition function to place the pivot element at its correct position
// and place smaller elements to the left and greater elements to the right
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int i = (low - 1);      // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;  // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// QuickSort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void print_vint32m1(vint32m1_t vec, size_t vl) {
    int32_t buffer[100]; // VLENMAX should be the maximum vector length
    // Store vector elements into a buffer
    __riscv_vse32_v_i32m1(buffer, vec, vl);

    // Print each element
    for (size_t i = 0; i < vl; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void print_mask(vbool32_t mask, size_t vl) {
    uint8_t buffer[100];
    __riscv_vsm_v_b32(buffer, mask, vl);
    for (size_t i = 0; i < vl / 8 + (vl % 8 != 0); i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}

void printArray1(int arr[], int low, int high) {
    printf("low=%d high=%d ", low, high);
    for (int i = low; i <= high; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int partitionRisc(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int l = low; // low of unknow area
    int h = high - 1; // high of unknow area
    size_t vl = 0;
    size_t vlmax = __riscv_vsetvlmax_e32m1();
    printArray1(arr, low, high);
    while (l <= h) { // l will point the first high element 
        vl = __riscv_vsetvl_e32m1(h - l + 1); // h will point the last low element
        vint32m1_t vec_a = __riscv_vle32_v_i32m1(arr + l, vl);
        vint32m1_t vec_b = __riscv_vle32_v_i32m1(arr + h - (vl - 1), vl);
        //print_vint32m1(vec_a, vl);


        vbool32_t mask = __riscv_vmsle_vx_i32m1_b32(vec_a, pivot, vl);
        vint32m1_t leElement = __riscv_vcompress_vm_i32m1(vec_a, mask, vl);
        print_mask(mask, vl);

        size_t active_count = __riscv_vcpop_m_b32(mask, vl);
        __riscv_vse32_v_i32m1(arr + l, leElement, active_count);
        printf("save low vl=%d active_count=%d ", vl, active_count);
        printArray1(arr, low, high);
        l = l + active_count;

        mask = __riscv_vmsgt_vx_i32m1_b32(vec_a, pivot, vl);
        vint32m1_t gtElement = __riscv_vcompress_vm_i32m1(vec_a, mask, vl);
        //print_vint32m1(gtElement);

        active_count = __riscv_vcpop_m_b32(mask, vl);
        __riscv_vse32_v_i32m1(arr + h - (active_count - 1), gtElement, active_count);
        printf("save high vl=%d active_count=%d ", vl, active_count);
        printArray1(arr, low, high);
        int overlap = 2 * (int)active_count - (h - l + 1);
        if (overlap < 0) {
            overlap = 0;
        }
        h = h - active_count;

        vec_b = __riscv_vslidedown_vx_i32m1(vec_b, vlmax - active_count + overlap, vl);
        printf("move low active_count=%d ", active_count - overlap);
        __riscv_vse32_v_i32m1(arr + l, vec_b, active_count - overlap);
        printArray1(arr, low, high);
    }

    swap(&arr[l], &arr[high]);// swap with pivot
    printArray1(arr, low, high);
    return l;
}


void quickSortRisc(int arr[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partitionRisc(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSortRisc(arr, low, pi - 1);
        quickSortRisc(arr, pi + 1, high);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Driver program to test the above functions
int main() {
    int arr[] = { 10, 7, 8, 9, 1, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Given array is \n");
    printArray(arr, n);

    quickSortRisc(arr, 0, n - 1);

    printf("Sorted array is \n");
    printArray(arr, n);
    return 0;
}

