//machin.c
//12.17
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define BITS_PER_DIGIT 3.32192809488736234789 //lb(10)
#define DIGITS_PER_ITERATION 1.39794 //2*lg(5)

int main(int argc, char *argv[])
{
    int digits = 1000;
    if (argc == 2)
    {
        digits = atoi(argv[1]);
    }
    unsigned long precision_bits = (digits + 1) * BITS_PER_DIGIT;
    unsigned long i = 1;
    mpf_set_default_prec(precision_bits);
    mpf_t pi, sum1, sum2, d5, d239, tmp;
    mpf_inits(pi, sum1, sum2, tmp, NULL);
    mpf_init_set_ui(d5, 5UL);
    mpf_init_set_ui(d239, 239UL);
    for (; i < digits / DIGITS_PER_ITERATION + 1; i++)
    {
        mpf_pow_ui(tmp, d5, (unsigned long)(2 * i - 1));
        mpf_mul_ui(tmp, tmp, (unsigned long)(2 * i - 1));
        mpf_ui_div(tmp, 1, tmp);
        if (i & 1)
            mpf_add(sum1, sum1, tmp);
        else
            mpf_sub(sum1, sum1, tmp);

        mpf_pow_ui(tmp, d239, (unsigned long)(2 * i - 1));
        mpf_mul_ui(tmp, tmp, (unsigned long)(2 * i - 1));
        mpf_ui_div(tmp, 1, tmp);
        if (i & 1)
            mpf_add(sum2, sum2, tmp);
        else
            mpf_sub(sum2, sum2, tmp);
    }
    mpf_mul_ui(sum1, sum1, 16UL);
    mpf_mul_ui(sum2, sum2, 4UL);
    mpf_sub(pi, sum1, sum2);
    mpf_out_str(stdout, 10, digits + 1, pi);
    fprintf(stdout, "\n");
    mpf_clears(pi, sum1, sum2, d5, d239, tmp, NULL);
    return 0;
}
