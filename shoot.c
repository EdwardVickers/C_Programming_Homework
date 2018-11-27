//射击运动员
//求出当打出子弹数为n时，使得满足平均环数大于等于9的所有情况

#include <stdio.h>
#define MAXN 20

int n, r[MAXN];

void print()
{
    for (int i = n; i > 1; i--)
        printf("%.2d", r[i]);
    printf("\n");
}

void shoot(int x, int s)
{
    int i;
    if (x * 10 >= s)
    {
        if (x == 1)
        {
            for (i = 10; i >= 0; --i)
            {
                r[x] = i;
                if (i >= s)
                    print();
            }
        }
        else
        {
            for (i = 10; i >= 0;--i)
            {
                r[x] = i;
                shoot(x - 1, s - i);
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    shoot(n, 9 * n);
    return 0;
}