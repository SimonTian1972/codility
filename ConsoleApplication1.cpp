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
#include <string.h>

void* memcpy_vec(void* restrict destination, const void* restrict source,
    size_t n) {
    unsigned char* dst = destination;
    unsigned char* src = source;
    for (size_t vl; n > 0; n -= vl, dst += vl, src += vl) {
        vl = __riscv_vsetvl_e8m8(n);
        //vuint8m8_t vec_src = __riscv_vle8ff_v_u8m8(src, &vl, vl);
        vuint8m8_t vec_src = __riscv_vle8_v_u8m8(src, vl);
        __riscv_vse8_v_u8m8(dst, vec_src, vl);
        /*
        vbool1_t mask = __riscv_vmseq_vx_u8m8_b1(vec_src, 0, vl);
        int first_set_bit_index = __riscv_vfirst_m_b1(mask, vl);
        if (first_set_bit_index > 0) {
            __riscv_vse8_v_u8m8(dst, vec_src, first_set_bit_index);
            dst += first_set_bit_index;
            break;
        }
        else {
            __riscv_vse8_v_u8m8(dst, vec_src, vl);
        }
        */
    }
    return destination;
}

int main() {
    const int N = 127;
    const uint32_t seed = 0xdeadbeef;
    srand(seed);

    // data gen
    double A[N];
    gen_rand_1d(A, N);

    // compute
    double golden[N], actual[N];
    memcpy(golden, A, sizeof(A));
    memcpy_vec(actual, A, sizeof(A));

    // compare
    puts(compare_1d(golden, actual, N) ? "pass" : "fail");
}
