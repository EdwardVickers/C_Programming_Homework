//输出小于x的所有超级素数
//定义从个位开始，依次去掉一位数字，得到的全是素数的素数成为超级素数

#include <stdio.h>
#define MAXX 100000000

//利用队列
int queue[100], head = 0, tail = 1, cnt;
int isprime(int n)
{
    if (n < 2)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int a, i, x;
    scanf("%d", &x);
    queue[head] = 0;
    while (head < tail)
    {
        a = queue[head];
        if (a > MAXX)
            break;
        for (i = 1; i < 10; i++)
        {
            if (isprime(a * 10 + i))
                queue[tail++] = a * 10 + i;
        }
        head++;
    }
    for (i = 1; i < tail; i++)
    {
        if (queue[i] <= x)
            cnt++;
    }
    printf("%d\n", cnt);
    for (i = 1; i <= cnt; i++)
        printf("%d\n", queue[i]);
    return 0;
}
