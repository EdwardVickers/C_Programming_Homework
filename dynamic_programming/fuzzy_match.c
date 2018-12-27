#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int IsMatch(char *s, char *p)
{
    int len1 = strlen(s), len2 = strlen(p);
    //辅助数组dp，dp[i][j]表示s(0~i-1)与p(0~j-1)子串是否完全匹配
    int dp[20][20];
    dp[0][0] = 1; //s为空字符串 && p为空字符串
    for (int i = 1; i <= len1; i++)
        dp[i][0] = 0; //s不为空，p为空字符串
    for (int j = 1; j <= len2; j++)
        dp[0][j] = (p[j - 1] == '*' && dp[0][j - 1]); //s为空字符串，p不为空

    //需s和p完全匹配，外层循环对p进行遍历
    for (int j = 1; j <= len2; j++)
        for (int i = 1; i <= len1; i++)
        {
            if (p[j - 1] != '*')
                //若p[j-1]不为*，需判断s(0~i-2)与p(0~j-2)是否匹配（即dp[i-1][j-1]），并且s[i-1]与p[j-1]匹配
                dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '?' == p[j - 1]);
            else
                //若p[j-1]为*,需判断s(0~i-2)与p(0~j-1)是否匹配（当前*匹配s[i-1]及之前部分字符）
                //或者判断s(0~i-1)与p(0~j-2)是否匹配(当前*匹配空字符串)
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
        }

    return dp[len1][len2];
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
