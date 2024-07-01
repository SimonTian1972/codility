#include "common.h"
#include <assert.h>
#include <riscv_vector.h>
#include <string.h>

// reference https://github.com/riscv/riscv-v-spec/blob/master/example/strcpy.s
char* strcpy_vec(char* destination, const char* source) {
    signed char* src = source, * dst = destination;
    size_t vlmax = __riscv_vsetvlmax_e8m8();
    size_t vl;
    while (true) {
        vint8m8_t vec_src = __riscv_vle8ff_v_i8m8(src, &vl, vlmax);
        vbool1_t mask = __riscv_vmseq_vx_i8m8_b1(vec_src, 0, vl);
        int pos = __riscv_vfirst_m_b1(mask, vl);
        if (pos == -1) {
            __riscv_vse8_v_i8m8(dst, vec_src, vl);
            src += vl;
            dst += vl;
        }
        else {
            __riscv_vse8_v_i8m8(dst, vec_src, pos + 1);
            break;
        }
    }
    return destination;
}

int main() {
    const int N = 2000;
    const uint32_t seed = 0xdeadbeef;
    srand(seed);

    // data gen
    char s0[N];
    gen_string(s0, N);

    // compute
    char golden[N], actual[N];
    strcpy(golden, s0);
    strcpy_vec(actual, s0);

    // compare
    puts(strcmp(golden, actual) == 0 ? "pass" : "fail");
}
