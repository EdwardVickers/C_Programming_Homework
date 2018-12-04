//IOI94 The Triangle
//             7
//           3   8
//         8   1   0
//       2   7   4   4
//     4   5   2   6   5   (Figure 1)
// Figure 1 shows a number triangle. Write a program that calculates the highest sum of numbers passed on a route that starts at the top and ends somewhere on the base.
// Each step can go either diagonally down to the left or diagonally down to the right.
// The number of rows in the triangle is >1 but <=100.
// The numbers in the triangle, all integers, are between 0 and 99.
//
// Input Data
// Data about the number of rows in the triangle are first read from the INPUT.TXT file. In our example, INPUT.TXT appears as follows:
// 5
// 7
// 3 8
// 8 1 0
// 2 7 4 4
// 4 5 2 6 5
//
// Output Data
// The highest sum is written as an integer in the OUTPUT.TXT file. In our example:
// 30

#include <stdio.h>
#define Max(a, b) (a) > (b) ? (a) : (b)

int opt[102][102];
int a[102][102];

int main()
{
    int level;
    scanf("%d", &level);
    for (int i = 1; i <= level; i++)
    {
        for (int j = 1; j <= i; j++)
            scanf("%d", &a[i][j]);
    }
    for (int i = level; i >= 1; i--)
        for (int j = 1; j <= i; j++)
        {
            opt[i][j] = (Max(opt[i + 1][j], opt[i + 1][j + 1])) + a[i][j];
        }
    printf("%d", opt[1][1]);
    return 0;
}
