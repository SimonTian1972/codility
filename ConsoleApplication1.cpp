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
#include <stdio.h>



unsigned char* strncpy_vec(unsigned char* destination, const unsigned char* source, size_t n) {
    //size_t i;

    // Copy up to num characters from source to destination
//    for (i = 0; i < num && source[i] != '\0'; i++) {
//        destination[i] = source[i];
//    }

    // If we haven't reached num characters, pad the rest with '\0'
//    for (; i < num; i++) {
//        destination[i] = '\0';
//    }
    unsigned char* dst = destination;
    unsigned const char* src = source;

    for (size_t vl; n > 0; n -= vl, src += vl, dst += vl) {
        vl = __riscv_vsetvl_e8m8(n);
        vuint8m8_t vec_src = __riscv_vle8ff_v_u8m8(src, &vl, vl);
        __riscv_vse8_v_u8m8(dst, vec_src, vl);
        // find \0
        // count number which is  not \0
        vbool1_t mask = __riscv_vmseq_vx_u8m8_b1(vec_src, '\0', vl);
        int valid = __riscv_vfirst_m_b1(mask, vl);
        if (valid >= 0) {
            n -= valid;
            src += valid;
            dst += valid;
            break;
        }
    }


    size_t vlmax = __riscv_vsetvlmax_e8m8();
    vuint8m8_t zero_vector = __riscv_vmv_v_x_u8m8(0, vlmax);
    for (size_t vl; n > 0; n -= vl, dst += vl) {
        vl = __riscv_vsetvl_e8m8(n);
        __riscv_vse8_v_u8m8(dst, zero_vector, vl);
    }

    /*
    size_t vlmax = __riscv_vsetvlmax_e8m8();

    // Create a zero vector
    vuint8m8_t zero_vector = __riscv_vmv_v_x_u8m8(0, vlmax);

    // Iterate over the array in chunks of vl elements
    while (n > 0) {
        // Set the vector length for the current chunk
        size_t vl = __riscv_vsetvl_e8m8(n);

        // Store the zero vector into the destination array
        __riscv_vse8_v_u8m8(dst, zero_vector, vl);

        // Move the destination pointer forward by vl elements
        dst += vl;

        // Decrease the remaining number of elements to process
        n -= vl;
    }
    */

    /*
    while (n > 0) {
        *dst = '\0';
        dst++;
        n--;
    }
    */

    return destination;
}


int main() {
    const int N = 1320;
    const uint32_t seed = 0xdeadbeef;
    srand(seed);

    // data gen
    char s0[N];
    gen_string(s0, N);
    char s1[] = "the quick brown fox jumps over the lazy dog";
    size_t count = strlen(s1) + rand() % 500;

    // compute
    char golden[N], actual[N];
    strcpy(golden, s0);
    strcpy(actual, s0);
    strncpy(golden, s1, count);
    strncpy_vec(actual, s1, count);

    // compare
    puts(compare_string(golden, actual, N) ? "pass" : "fail");
}