// common.h
// common utilities for the test code under exmaples/

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void gen_rand_1d(double* a, int n) {
    for (int i = 0; i < n; ++i)
        a[i] = (double)rand() / (double)RAND_MAX + (double)(rand() % 1000);
}

void gen_string(char* s, int n) {
    // char value range: -128 ~ 127
    for (int i = 0; i < n - 1; ++i)
        s[i] = (char)(rand() % 127) + 1;
    s[n - 1] = '\0';
}

void gen_rand_2d(double** ar, int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            ar[i][j] = (double)rand() / (double)RAND_MAX + (double)(rand() % 1000);
}

void print_string(const char* a, const char* name) {
    printf("const char *%s = \"", name);
    int i = 0;
    while (a[i] != 0)
        putchar(a[i++]);
    printf("\"\n");
    puts("");
}

void print_array_1d(double* a, int n, const char* type, const char* name) {
    printf("%s %s[%d] = {\n", type, name, n);
    for (int i = 0; i < n; ++i) {
        printf("%06.2f%s", a[i], i != n - 1 ? "," : "};\n");
        if (i % 10 == 9)
            puts("");
    }
    puts("");
}

void print_array_2d(double** a, int n, int m, const char* type,
    const char* name) {
    printf("%s %s[%d][%d] = {\n", type, name, n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%06.2f", a[i][j]);
            if (j == m - 1)
                puts(i == n - 1 ? "};" : ",");
            else
                putchar(',');
        }
    }
    puts("");
}

bool double_eq(double golden, double actual, double relErr) {
    return (fabs(actual - golden) < relErr);
}

bool compare_1d(double* golden, double* actual, int n) {
    for (int i = 0; i < n; ++i)
        if (!double_eq(golden[i], actual[i], 1e-6))
            return false;
    return true;
}

bool compare_string(const char* golden, const char* actual, int n) {
    for (int i = 0; i < n; ++i)
        if (golden[i] != actual[i])
            return false;
    return true;
}

bool compare_2d(double** golden, double** actual, int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!double_eq(golden[i][j], actual[i][j], 1e-6))
                return false;
    return true;
}

double** alloc_array_2d(int n, int m) {
    double** ret;
    ret = (double**)malloc(sizeof(double*) * n);
    for (int i = 0; i < n; ++i)
        ret[i] = (double*)malloc(sizeof(double) * m);
    return ret;
}

void init_array_one_1d(double* ar, int n) {
    for (int i = 0; i < n; ++i)
        ar[i] = 1;
}

void init_array_one_2d(double** ar, int n, int m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            ar[i][j] = 1;
}



#include <riscv_vector.h>

// accumulate and reduce
void reduce_golden(double* a, double* b, double* result_sum,
    int* result_count, int n) {
    int count = 0;
    double s = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] != 42.0) {
            s += a[i] * b[i];
            count++;
        }
    }

    *result_sum = s;
    *result_count = count;
}

void reduce_vec(double* a, double* b, double* result_sum, int* result_count,
    int n) {
    int count = 0;
    int vlmax = __riscv_vsetvlmax_e64m8();
    vfloat64m1_t vec_zero = __riscv_vfmv_v_f_f64m1(0.0f, vlmax);
    vfloat64m8_t vec_s = __riscv_vfmv_v_f_f64m8(0.0f, vlmax);
    for (size_t vl; n > 0; n -= vl, a += vl, b += vl) {
        vl = __riscv_vsetvl_e64m8(n);
        vfloat64m8_t vec_a = __riscv_vle64_v_f64m8(a, vl);
        vfloat64m8_t vec_b = __riscv_vle64_v_f64m8(b, vl);
        vbool8_t mask = __riscv_vmfne_vf_f64m8_b8(vec_a, 42.0, vl);
        vec_a = __riscv_vfmul_vv_f64m8(vec_a, vec_b, vl);
        vec_s = __riscv_vfadd_vv_f64m8_m(mask, vec_a, vec_s, vl);
        count = count + __riscv_vcpop_m_b8(mask, vl);
    }
    vec_zero = __riscv_vfredusum_vs_f64m8_f64m1(vec_s, vec_zero, vlmax);
    *result_sum = __riscv_vfmv_f_s_f64m1_f64(vec_zero);
    *result_count = count;
}

int main() {
    const int N = 31;
    uint32_t seed = 0xdeadbeef;
    srand(seed);

    // data gen
    double A[N], B[N];
    gen_rand_1d(A, N);
    gen_rand_1d(B, N);

    // compute
    double golden_sum, actual_sum;
    int golden_count, actual_count;
    reduce_golden(A, B, &golden_sum, &golden_count, N);
    reduce_vec(A, B, &actual_sum, &actual_count, N);

    // compare
    puts(golden_sum - actual_sum < 1e-6 && golden_count == actual_count ? "pass"
        : "fail");
}
