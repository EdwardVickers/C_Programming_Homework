//动态数组，给每一个元素赋值为下标*10
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arraysize = 0;
    int i = 0;
    printf("Enter array size:");
    scanf("%d", &arraysize);
    int *p = NULL;
    p = (int *)malloc(arraysize * sizeof(int));
    if (p == NULL)
    {
        exit(1);
    }
    for (i = 0; i < arraysize; i++)
    {
        p[i] = i * 10;
    }
    for (i = 0; i < arraysize; i++)
    {
        printf("array[%d]=%d\n", i, p[i]);
    }
    return 0;
}
