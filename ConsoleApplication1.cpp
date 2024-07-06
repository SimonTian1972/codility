#include <riscv_vector.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include <stdio.h>
#include <limits.h>  // For INT_MIN
#define max(a, b) ((a) > (b) ? (a) : (b))

int maxRiscv(int* energy, int energySize, int k) {
    int ret = INT_MIN;
    int n = k;
    size_t vl;
    for (int i = 0; i < k; i = i + vl, n = n - vl) {
        size_t vl = __riscv_vsetvl_e32m1(n);
        vint32m1_t vec_sum = __riscv_vmv_v_x_i32m1(0, vl);
        for (int j = i; j < energySize; j = j + k) {
            vint32m1_t vec_seq;
            vec_seq = __riscv_vid_v_i32m1(vl);
            vec_seq = __riscv_vadd_vx_i32m1(vec_seq, j, vl);
            vbool32_t mask = __riscv_vmslt_vx_i32m1_b32(vec_seq, energySize, vl);
            vint32m1_t vec_cur = __riscv_vmv_v_x_i32m1(0, vl);
            size_t temp;
            vec_cur = __riscv_vle32ff_v_i32m1_m(mask, energy + j, &temp, vl);

            vbool32_t maskPrev = __riscv_vmslt_vx_i32m1_b32(vec_sum, 0, vl);
            mask = __riscv_vmand_mm_b32(mask, maskPrev, vl);

            // Set elements to zero based on the mask
            vec_sum = __riscv_vmerge_vxm_i32m1(vec_sum, 0, mask, vl);
            vec_sum = __riscv_vadd_vv_i32m1(vec_sum, vec_cur, vl);
        }
        vint32m1_t vec_scalar = __riscv_vmv_v_x_i32m1(INT_MIN, vl);
        vec_sum = __riscv_vredmax_vs_i32m1_i32m1(vec_sum, vec_scalar, vl);
        int curMax = __riscv_vmv_x_s_i32m1_i32(vec_sum);
        ret = max(ret, curMax);
    }
    return ret;
}

int maximumEnergy(int* energy, int energySize, int k) {
    int sumMax = INT_MIN;
    for (int i = 0; i < k && i < energySize; i++) {
        int sum = 0;
        for (int j = i; j < energySize; j = j + k) {
            sum = sum + energy[j];
            if (j + k >= energySize) {
                break;
            }
            else if (sum < 0) {
                sum = 0;
            }
        }
        sumMax = max(sumMax, sum);
    }
    return sumMax;
}

#include "assert.h"

void testMaximumEnergy() {
    // Test case 1
    int energy1[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
    int energySize1 = sizeof(energy1) / sizeof(energy1[0]);
    int k1 = 3;
    int result1 = maximumEnergy(energy1, energySize1, k1);
    int result1a = maxRiscv(energy1, energySize1, k1);
    printf("Test case 1: The maximum energy is: %d %d\n", result1, result1a);

    // Test case 2
    int energy2[] = { -1, -2, -3, -4, -5, -6, -7, -8 };
    int energySize2 = sizeof(energy2) / sizeof(energy2[0]);
    int k2 = 2;
    int result2 = maximumEnergy(energy2, energySize2, k2);
    int result2a = maxRiscv(energy2, energySize2, k2);
    printf("Test case 2: The maximum energy is: %d %d\n", result2, result2a);

    // Test case 3
    int energy3[] = { 5, -1, 3, -2, 4, -3, 2, -4, 1 };
    int energySize3 = sizeof(energy3) / sizeof(energy3[0]);
    int k3 = 4;
    int result3 = maximumEnergy(energy3, energySize3, k3);
    int result3a = maxRiscv(energy3, energySize3, k3);
    printf("Test case 3: The maximum energy is: %d %d\n", result3, result3a);

    // Test case 4
    int energy4[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int energySize4 = sizeof(energy4) / sizeof(energy4[0]);
    int k4 = 5;
    int result4 = maximumEnergy(energy4, energySize4, k4);
    int result4a = maxRiscv(energy4, energySize4, k4);
    printf("Test case 4: The maximum energy is: %d %d\n", result4, result4a);

    // Test case 5
    int energy5[] = { 10, -10, 20, -20, 30, -30, 40, -40, 50, -50 };
    int energySize5 = sizeof(energy5) / sizeof(energy5[0]);
    int k5 = 6;
    int result5 = maximumEnergy(energy5, energySize5, k5);
    int result5a = maxRiscv(energy5, energySize5, k5);
    printf("Test case 5: The maximum energy is: %d %d\n", result5, result5a);
}

int main() {
    testMaximumEnergy();
    return 0;
}

