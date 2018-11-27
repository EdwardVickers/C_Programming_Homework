//stdlib里qsort的使用方法

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

//整型数排序
int compareInt(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

//字符串排序
// int compareString(const void *a, const void *b)
// {
//     return strcmp((char *)a, (char *)b);
// }

int main()
{
    int a[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    qsort(a, 10, sizeof(int), compareInt);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}