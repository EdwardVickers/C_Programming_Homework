//2018.12.02
//归并排序
//时间复杂度：O(nlogn)

#include <stdio.h>
#include <string.h>

int s[1000]; //归并时的临时数组

void merge_sort(int a[], int left, int right)
{
    if (left == right)
        return;
    int mid = (left + right) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid + 1, right);

    //复制到临时数组s中
    memcpy(s + left, a + left, (right - left + 1) * sizeof(int));
    int p1 = 1, p2 = mid + 1, p = 1;
    while (p1 <= mid && p2 <= right)
    {
        if (s[p1] <= s[p2])
            a[p++] = s[p1++];
        else
            a[p++] = s[p2++];
    }
    while (p1 <= mid)
        a[p++] = s[p1++];
    while (p2 <= right)
        a[p++] = s[p2++];
}

int main()
{
    int a[7] = {49, 38, 65, 55, 76, 13, 27};
    merge_sort(a, 0, 6);
    for (int i = 0; i < 7; i++)
        printf("%d ", a[i]);
    return 0;
}