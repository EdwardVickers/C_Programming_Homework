//archimedes.c
//12.18
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define BITS_PER_DIGIT 3.32192809488736234789 //lb(10)

int main(int argc, char *argv[])
{
    int digits = 1000;
    if (argc == 2)
    {
        digits = atoi(argv[1]);
    }
    mpf_t n;
    mpf_t h, r, pi;
    mpf_t ht, rt, pit;
    unsigned long precision_bits = ((digits + 1) * BITS_PER_DIGIT) + 1;
    mpf_set_default_prec(precision_bits);
    mpf_inits(n, r, h, pi, rt, ht, pit, NULL);
    mpf_set_ui(n, 6UL);
    mpf_sqrt_ui(pi, 3);
    mpf_mul_ui(pi, pi, 3);
    mpf_div_ui(pi, pi, 2);
    mpf_set_ui(r, 1);
    //1665 -> 1000
    for (int cnt = 0; cnt < digits / 0.6; mpf_mul_ui(n, n, 2UL))
    {
        mpf_set(ht, r);
        mpf_mul(ht, ht, ht);
        mpf_div_ui(ht, ht, 4);
        mpf_ui_sub(ht, 1, ht);
        mpf_sqrt(h, ht);

        mpf_set(pit, pi);
        mpf_ui_sub(pit, 1, h);
        mpf_div_ui(pit, pit, 2);
        mpf_mul(pit, r, pit);
        mpf_mul(pit, pit, n);
        mpf_add(pi, pi, pit);

        mpf_set(rt, r);
        mpf_ui_sub(rt, 1, h);
        mpf_mul(rt, rt, rt);
        mpf_mul(r, r, r);
        mpf_div_ui(r, r, 4);
        mpf_add(r, r, rt);
        mpf_sqrt(r, r);
        cnt++;
    }
    mpf_out_str(stdout, 10, digits + 1, pi);
    fprintf(stdout, "\n");
    mpf_clears(n, h, r, pi, ht, rt, pit, NULL);
    return 0;
}
