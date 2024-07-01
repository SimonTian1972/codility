#include "common.h"
#include <riscv_vector.h>
#include <string.h>

// reference https://github.com/riscv/riscv-v-spec/blob/master/example/strlen.s
size_t strlen_vec(char* source) {
    size_t vlmax = __riscv_vsetvlmax_e8m8();
    size_t vl;
    size_t count = 0;
    while (true) {
        vint8m8_t vec_src = __riscv_vle8ff_v_i8m8((int8_t*)source, &vl, vlmax);
        vbool1_t mask = __riscv_vmseq_vx_i8m8_b1(vec_src, 0, vl);
        int pos = __riscv_vfirst_m_b1(mask, vl);
        if (pos == -1) {
            count = count + vl;
            source = source + vl;
        }
        else {
            count = count + pos;
            break;
        }
    }
    return count;
}

int main() {
    const uint32_t seed = 0xdeadbeef;
    srand(seed);

    int N = rand() % 2000;

    // data gen
    char s0[N];
    gen_string(s0, N);

    // compute
    size_t golden, actual;
    golden = strlen(s0);
    actual = strlen_vec(s0);

    // compare
    puts(golden == actual ? "pass" : "fail");
}
