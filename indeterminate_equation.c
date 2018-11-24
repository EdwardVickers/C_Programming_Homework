//求不定方程的正整数解
//输入m和n（20≥m≥n≥0），求出满足以下方程式的正整数数列i1,i2,…,in，使得i1+i2+…+in=m，且i1≥i2≥…≥in

#include <stdio.h>
#define NUM 20
int a[NUM];                                             //定义数组a,维度为NUM

int main()
{
    int sum, number, total, k, flag, count = 0;         //total 表示总和
    printf("Please enter requried terms(<=10):");
    scanf("%d", &number);
    printf("their sum:");
    scanf("%d", &total);
    sum = 0;                                            //初始化当前总和为0
    k = number;
    a[number] = 1;                                      //将最后的未知数赋值1，从最后一位开始排
    printf("There are following possible series:\n");
    while (1)
    {
        if (sum + a[k] < total)                         //如果还没有排完
        {
            if (k <= 1)
            {
                a[1] = total - sum;
                flag = 1;
            }
            else
            {
                sum += a[k--];
                a[k] = a[k + 1];
                continue;
            }
        }
        else if (sum + a[k] > total || k != 1)
        {
            sum -= a[++k];
            flag = 0;
        }
        else
            flag = 1;
        if (flag)
        {
            printf("[%.2d]:", ++count);
            for (flag = 1; flag <= number; ++flag)
                printf("%.2d ", a[flag]);
            printf("\n");
        }
        if (++k > number)
            break;
        sum -= a[k];
        a[k]++;
    }
    return 0;
}
