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


// reference https://github.com/riscv/riscv-v-spec/blob/master/example/strcmp.s
#define min(a, b) (((a) < (b)) ? (a) : (b))

int strcmp_vec(const char* source1, const char* source2) {
    size_t vlmax = __riscv_vsetvlmax_e8m8();
    while (true) {
        size_t vl = vlmax;
        vuint8m8_t vec_1 = __riscv_vle8ff_v_u8m8(source1, &vl, vl);
        vbool1_t mask1 = __riscv_vmseq_vx_u8m8_b1(vec_1, 0, vl);
        int len1;
        if (__riscv_vfirst_m_b1(mask1, vl) < 0) {
            len1 = vl;
        }
        else {
            len1 = __riscv_vfirst_m_b1(mask1, vl);
        }

        vuint8m8_t vec_2 = __riscv_vle8ff_v_u8m8(source2, &vl, vl);
        vbool1_t mask2 = __riscv_vmseq_vx_u8m8_b1(vec_2, 0, vl);
        int len2;
        if (__riscv_vfirst_m_b1(mask2, vl) < 0) {
            len2 = vl;
        }
        else {
            len2 = __riscv_vfirst_m_b1(mask2, vl);
        }

        vbool1_t mask12 = __riscv_vmsne_vv_u8m8_b1(vec_1, vec_2, min(len1, len2));
        int pos_diff = __riscv_vfirst_m_b1(mask12, min(len1, len2));

        if (pos_diff >= 0) {
            return (int)source1[pos_diff] - (int)source2[pos_diff];
        }
        else {
            if (len1 == len2) {
                source1 += len1;
                source2 += len2;
                if (__riscv_vfirst_m_b1(mask2, vl) >= 0) {
                    return 0;
                }
                else {
                    continue;
                }
            }
            else {
                return len1 - len2;
            }
        }
    }
}

int main() {
    const int N = 1023;
    const uint32_t seed = 0xdeadbeef;
    srand(seed);

    // data gen
    char s0[N], s1[N];
    gen_string(s0, N);
    gen_string(s1, N);

    // compute
    int golden, actual;
    golden = strcmp(s0, s1);
    actual = strcmp_vec(s0, s1);

    // compare
    puts(golden == actual ? "pass" : "fail");
}

