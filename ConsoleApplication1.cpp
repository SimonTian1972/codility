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

// index arithmetic
void index_golden(double* a, double* b, double* c, int n) {
    for (int i = 0; i < n; ++i) {
        a[i] = b[i] + (double)i * c[i];
    }
}

void index_vec(double* a, double* b, double* c, int n) {
    size_t vlmax = __riscv_vsetvlmax_e32m4();
    vuint32m4_t vec_i = __riscv_vid_v_u32m4(vlmax);
    for (size_t vl; n > 0; n -= vl, a += vl, b += vl, c += vl) {
        vl = __riscv_vsetvl_e64m8(n);
        vfloat64m8_t vec_i_double = __riscv_vfwcvt_f_xu_v_f64m8(vec_i, vl);

        vfloat64m8_t vec_b = __riscv_vle64ff_v_f64m8(b, &vl, vl);
        vfloat64m8_t vec_c = __riscv_vle64_v_f64m8(c, vl);
        vec_c = __riscv_vfmul_vv_f64m8(vec_c, vec_i_double, vl);

        vfloat64m8_t vec_a = __riscv_vfadd_vv_f64m8(vec_b, vec_c, vl);
        //vfloat64m8_t vec_a = __riscv_vfmadd_vv_f64m8(vec_c, vec_i_double, vec_b, vl);
        __riscv_vse64_v_f64m8(a, vec_a, vl);

        vec_i = __riscv_vadd_vx_u32m4(vec_i, vl, vl);
    }
}

int main() {
    const int N = 31;
    const uint32_t seed = 0xdeadbeef;
    srand(seed);

    // data gen
    double B[N], C[N];
    gen_rand_1d(B, N);
    gen_rand_1d(C, N);

    // compute
    double golden[N], actual[N];
    index_golden(golden, B, C, N);
    index_vec(actual, B, C, N);

    // compare
    puts(compare_1d(golden, actual, N) ? "pass" : "fail");
}
