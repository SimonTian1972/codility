




#include <riscv_vector.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>

#include <stdio.h>
#include <stdlib.h>

// Function to find two numbers that add up to the target
int* twoSum_c(int* nums, int numsSize, int target, int* returnSize) {
    // Allocate memory for the return array
    int* result = (int*)malloc(2 * sizeof(int));
    // Initialize returnSize to 2
    *returnSize = 2;

    // Loop through the array to find the two numbers
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            // Check if the sum of nums[i] and nums[j] equals the target
            if (nums[i] + nums[j] == target) {
                // Store the indices in the result array
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }

    // If no solution is found, set returnSize to 0
    *returnSize = 0;
    // Free the allocated memory
    free(result);
    // Return NULL to indicate no solution
    return NULL;
}

void print_vint32m1(vint32m1_t vec) {
    int32_t buffer[100]; // VLENMAX should be the maximum vector length
    size_t vl = __riscv_vsetvl_e32m1(100); // Set the vector length

    // Store vector elements into a buffer
    __riscv_vse32_v_i32m1(buffer, vec, vl);

    // Print each element
    for (size_t i = 0; i < vl; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
// Function to find two numbers that add up to the target
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Allocate memory for the return array
    int* result = (int*)malloc(2 * sizeof(int));
    // Initialize returnSize to 2
    *returnSize = 2;
    size_t vl = 0;
    for (int n = 0; n < numsSize; n += vl) {
        vl = __riscv_vsetvl_e32m1(numsSize - n);
        vint32m1_t vec_a = __riscv_vle32_v_i32m1(nums + n, vl);
        print_vint32m1(vec_a);
        printf("numsSize = %d, n= %d vl = %u \n", numsSize, n, vl);
        for (int m = n + 1; m < numsSize; m = m + vl) {
            int valid_m = numsSize - m;
            vint32m1_t vec_b = __riscv_vle32_v_i32m1(nums + m, MIN(valid_m, vl));
            vint32m1_t seq = __riscv_vid_v_i32m1(vl);
            vbool32_t mask = __riscv_vmsge_vx_i32m1_b32(seq, MIN(valid_m, vl), vl);
            vec_b = __riscv_vmerge_vxm_i32m1(vec_b, INT_MAX, mask, vl);
            print_vint32m1(vec_b);
            // over boundary should be set with INT_MAX
            for (int i = 0; i < vl; i++) {
                // sum vec_a + vec_b, 
                vint32m1_t vec_c = __riscv_vsadd_vv_i32m1(vec_a, vec_b, vl);
                vbool32_t is_find = __riscv_vmseq_vx_i32m1_b32(vec_c, target, vl);
                int pos = __riscv_vfirst_m_b32(is_find, vl);
                if (pos != -1) {
                    result[0] = n + pos;
                    result[1] = m + pos + i;
                    return result;
                }
                vec_b = __riscv_vslide1down_vx_i32m1(vec_b, INT_MAX, vl);
            }
        }
    }

    // If no solution is found, set returnSize to 0
    *returnSize = 0;
    // Free the allocated memory
    free(result);
    // Return NULL to indicate no solution
    return NULL;
}

/*

; Assuming n (total elements) is 10 and m (elements to keep) is 5

sub a0, a1, a2  ; Calculate upper element index (a1 = 10, a2 = 5, a0 = 5)
vseqvli vmask, a0, e32  ; Create a mask with zeros in first 5 elements and ones in upper elements

li t0, 0x7FFFFFFF  ; Load INT_MAX into t0
vmerge vt, vo, vmask, t0  ; Merge elements from vo and t0 based on vmask

*/


int main_old() {
    // Test case 1
    int nums1[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
    int target1 = 3;
    int returnSize1;
    int* result1 = twoSum(nums1, sizeof(nums1) / sizeof(int), target1, &returnSize1);

    if (result1 != NULL) {
        printf("Test case 1: Indices [%d, %d]\n", result1[0], result1[1]);
        free(result1); // Free the allocated memory
    }
    else {
        printf("Test case 1: No solution found\n");
    }

    // Test case 2
    int nums2[] = { 3, 2, 4 };
    int target2 = 6;
    int returnSize2;
    int* result2 = twoSum(nums2, 3, target2, &returnSize2);

    if (result2 != NULL) {
        printf("Test case 2: Indices [%d, %d]\n", result2[0], result2[1]);
        free(result2); // Free the allocated memory
    }
    else {
        printf("Test case 2: No solution found\n");
    }

    // Test case 3
    int nums3[] = { 3, 3 };
    int target3 = 6;
    int returnSize3;
    int* result3 = twoSum(nums3, 2, target3, &returnSize3);

    if (result3 != NULL) {
        printf("Test case 3: Indices [%d, %d]\n", result3[0], result3[1]);
        free(result3); // Free the allocated memory
    }
    else {
        printf("Test case 3: No solution found\n");
    }

    return 0;
}


#include <stdbool.h>
int* twoSum_c(int* nums, int numsSize, int target, int* returnSize);
int* twoSum(int* nums, int numsSize, int target, int* returnSize);

bool compare_results(int* result1, int* result2, int size1, int size2) {
    if (size1 != size2) {
        return false;
    }
    for (int i = 0; i < size1; i++) {
        if (result1[i] != result2[i]) {
            return false;
        }
    }
    return true;
}

void run_test_case(int* nums, int numsSize, int target) {
    int returnSize_c;
    int returnSize_v;
    int* result_c = twoSum_c(nums, numsSize, target, &returnSize_c);
    int* result_v = twoSum(nums, numsSize, target, &returnSize_v);

    printf("Test case: nums = [");
    for (int i = 0; i < numsSize; i++) {
        printf("%d%s", nums[i], (i < numsSize - 1) ? ", " : "");
    }
    printf("], target = %d\n", target);

    if (compare_results(result_c, result_v, returnSize_c, returnSize_v)) {
        printf("Results are the same.\n");
    }
    else {
        printf("Results differ!\n");
        printf("twoSum_c result: ");
        if (returnSize_c == 0) {
            printf("No solution\n");
        }
        else {
            printf("[%d, %d]\n", result_c[0], result_c[1]);
        }
        printf("twoSum result: ");
        if (returnSize_v == 0) {
            printf("No solution\n");
        }
        else {
            printf("[%d, %d]\n", result_v[0], result_v[1]);
        }
    }

    if (result_c) free(result_c);
    if (result_v) free(result_v);
}

int main() {
    // Test cases
    int nums1[] = { 2, 7, 11, 15 };
    run_test_case(nums1, 4, 9);

    int nums2[] = { 3, 2, 4 };
    run_test_case(nums2, 3, 6);

    int nums3[] = { 3, 3 };
    run_test_case(nums3, 2, 6);

    int nums4[] = { 1, 2, 3, 4, 5 };
    run_test_case(nums4, 5, 10);

    int nums5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
    run_test_case(nums5, 11, 3);

    int nums6[] = { 5, 75, 25 };
    run_test_case(nums6, 3, 100);

    int nums7[] = { 1, 2, 3, 4, 4, 9, 56, 90 };
    run_test_case(nums7, 8, 8);

    int nums8[] = { -1, -2, -3, -4, -5 };
    run_test_case(nums8, 5, -8);

    return 0;
}
