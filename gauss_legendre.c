//gauss_legendre.c
//12.16
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

#define BITS_PER_DIGIT 3.32192809488736234789

int main(int argc, char *argv[])
{
    int digits = 1000;
    if (argc == 2)
    {
        digits = atoi(argv[1]);
    }
    mpf_set_default_prec(digits * BITS_PER_DIGIT + 1);
    mpf_t a0, b, t, p, a1;
    mpf_inits(a0, b, t, p, a1, NULL);

    mpf_set_ui(a0, 1);
    mpf_set_d(t, 1.0 / 4.0);
    mpf_set_ui(p, 1);

    mpf_sqrt_ui(b, 2);
    mpf_ui_div(b, 1, b);

    for (int i = 0; i < 26; i++)
    {
        mpf_add(a1, a0, b);
        mpf_div_ui(a1, a1, 2);

        mpf_mul(b, b, a0);
        mpf_sqrt(b, b);

        mpf_sub(a0, a0, a1);
        mpf_mul(a0, a0, a0);
        mpf_mul(a0, a0, p);
        mpf_sub(t, t, a0);
        mpf_set(a0, a1);

        mpf_mul_ui(p, p, 2);
    }

    mpf_add(a0, a0, b);
    mpf_mul(a0, a0, a0);
    mpf_mul_ui(t, t, 4);
    mpf_div(a0, a0, t);
    mpf_out_str(stdout, 10, digits + 1, a0);
    return 0;
}
