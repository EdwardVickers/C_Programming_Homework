#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int IsMatch(char *str, char *pat)
{
    if (str == NULL || pat == NULL) //字符串为空直接返回0
        return 0;
    int slen = strlen(str);
    int plen = strlen(pat);
    int pstar = 0;                 //用于标记'*'分隔的字符串
    int p1 = 0, p2 = 0;            //p1用于做str的下标, p2用于做pat的下标
    while (p1 < slen && p2 < plen) //如果str和pat至少一个没有匹配完
    {
        if (pat[p2] == '?') //如果是?号, 则继续匹配
        {
            p1++;
            p2++;
            continue;
        }
        if (pat[p2] == '*') //如果是*号，则标记*号后继续匹配
        {
            p2++;
            pstar = p2;
            continue;
        }
        if (str[p1] != pat[p2]) //如果字符不匹配
        {
            if (p1 == 0 && p2 == 0)
            {
                return 0; //如果首字符不相同则匹配失败
            }
            //p1到下一个位置
            p1 -= (p2 - pstar - 1);
            p2 = pstar; //p2指向'*'后一个字符
            continue;
        }
        p1++; //相等则继续匹配
        p2++;
    }
    if ((p1 == plen && p2 == plen) || (p2 == plen && pat[p2 - 1] == '*'))
    {
        return 1; //如果两个字符串都结束或pat的最后一个字符是*, 则匹配成功
    }
    while (p2 < plen) //如果pat没有结束
    {
        if (pat[p2] != '*') //pat多出的字符有一个不是'*'就匹配失败
            return 0;
        p2++;
    }
    return 1;
}

int main()
{
    char a[20];
    char b[20];
    for (int i = 0; i < 20; i++)
    {
        gets(a);
        gets(b);
        printf("%d\n", IsMatch(a, b));
    }
    return 0;
}
