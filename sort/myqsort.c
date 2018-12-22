#include <stdio.h>

void qsort(int a[], int left, int right)
{
    int tmp;
    int cmp = a[(left + right) / 2];
    int i = left, j = right;
    while (i <= j)
    {
        while (a[i] < cmp)
            i++;
        while (a[j] > cmp)
            j--;
        if (i <= j)
        {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
        qsort(a, left, j);
    if (i < right)
        qsort(a, i, right);
}
int main()
{
    int a[10] = {7, 6, 3, 48, 29, 1, 3, 20, 2, 9};
    qsort(a, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}