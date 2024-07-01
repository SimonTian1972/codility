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
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#define N 31

float input[N] = { -0.4325648115282207, -1.6655843782380970, 0.1253323064748307,
                  0.2876764203585489,  -1.1464713506814637, 1.1909154656429988,
                  1.1891642016521031,  -0.0376332765933176, 0.3272923614086541,
                  0.1746391428209245,  -0.1867085776814394, 0.7257905482933027,
                  -0.5883165430141887, 2.1831858181971011,  -0.1363958830865957,
                  0.1139313135208096,  1.0667682113591888,  0.0592814605236053,
                  -0.0956484054836690, -0.8323494636500225, 0.2944108163926404,
                  -1.3361818579378040, 0.7143245518189522,  1.6235620644462707,
                  -0.6917757017022868, 0.8579966728282626,  1.2540014216025324,
                  -1.5937295764474768, -1.4409644319010200, 0.5711476236581780,
                  -0.3998855777153632 };

float output_golden[N] = {
    1.7491401329284098,  0.1325982188803279,  0.3252281811989881,
    -0.7938091410349637, 0.3149236145048914,  -0.5272704888029532,
    0.9322666565031119,  1.1646643544607362,  -2.0456694357357357,
    -0.6443728590041911, 1.7410657940825480,  0.4867684246821860,
    1.0488288293660140,  1.4885752747099299,  1.2705014969484090,
    -1.8561241921210170, 2.1343209047321410,  1.4358467535865909,
    -0.9173023332875400, -1.1060770780029008, 0.8105708062681296,
    0.6985430696369063,  -0.4015827425012831, 1.2687512030669628,
    -0.7836083053674872, 0.2132664971465569,  0.7878984786088954,
    0.8966819356782295,  -0.1869172943544062, 1.0131816724341454,
    0.2484350696132857 };

float output[N] = {
    1.7491401329284098,  0.1325982188803279,  0.3252281811989881,
    -0.7938091410349637, 0.3149236145048914,  -0.5272704888029532,
    0.9322666565031119,  1.1646643544607362,  -2.0456694357357357,
    -0.6443728590041911, 1.7410657940825480,  0.4867684246821860,
    1.0488288293660140,  1.4885752747099299,  1.2705014969484090,
    -1.8561241921210170, 2.1343209047321410,  1.4358467535865909,
    -0.9173023332875400, -1.1060770780029008, 0.8105708062681296,
    0.6985430696369063,  -0.4015827425012831, 1.2687512030669628,
    -0.7836083053674872, 0.2132664971465569,  0.7878984786088954,
    0.8966819356782295,  -0.1869172943544062, 1.0131816724341454,
    0.2484350696132857 };

void saxpy_golden(size_t n, const float a, const float* x, float* y) {
    for (size_t i = 0; i < n; ++i) {
        y[i] = a * x[i] + y[i];
    }
}

// reference https://github.com/riscv/riscv-v-spec/blob/master/example/saxpy.s
void saxpy_vec(size_t n, const float a, const float* x, float* y) {
    for (size_t vl; n > 0; n -= vl, x += vl, y += vl) {
        vl = __riscv_vsetvl_e32m8(n);
        vfloat32m8_t vec_x = __riscv_vle32_v_f32m8(x, vl);
        vfloat32m8_t vec_y = __riscv_vle32_v_f32m8(y, vl);
        vec_x = __riscv_vfmul_vf_f32m8(vec_x, a, vl);
        vec_y = __riscv_vfadd_vv_f32m8(vec_x, vec_y, vl);
        __riscv_vse32_v_f32m8(y, vec_y, vl);
    }
}

int fp_eq(float reference, float actual, float relErr)
{
    // if near zero, do absolute error instead.
    float absErr = relErr * ((fabsf(reference) > relErr) ? fabsf(reference) : relErr);
    return fabsf(actual - reference) < absErr;
}


int main() {
    saxpy_golden(N, 55.66, input, output_golden);
    saxpy_vec(N, 55.66, input, output);
    int pass = 1;
    for (int i = 0; i < N; i++) {
        if (!fp_eq(output_golden[i], output[i], 1e-6)) {
            printf("fail, %f=!%f\n", output_golden[i], output[i]);
            pass = 0;
        }
    }
    if (pass)
        printf("pass\n");
    return (pass == 0);
}



