//Name: 学生成绩管理系统
//Date: 2018-12-21
//Author: 1180300902代昆

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_NAMELEN 20             //姓名最大长度
#define MAX_COURSENUM 6            //最多课程数
#define LEN sizeof(struct Student) //结构体大小

typedef struct Student //定义链表节点
{
    long long num;              //学号
    char name[MAX_NAMELEN];     //姓名
    float score[MAX_COURSENUM]; //成绩
    float sum;                  //总分
    float aver;                 //平均分
    struct Student *next;
} STUDENT;

int DisplayMenu(void);
void DisplayNoRecord(void);
void ListRecord(STUDENT *head, int stunum, int coursenum);
STUDENT *CreateList(int stunum, int coursenum);
STUDENT *CreateEmptyList(int stunum, int coursenum);
void SumAverCourse(STUDENT *head, int stunum, int coursenum);
void SumAverStudent(STUDENT *head, int stunum);
STUDENT *Sort(STUDENT *head, int stunum, int (*cmp)(STUDENT *a, STUDENT *b));
int CmpScoreAsc(STUDENT *a, STUDENT *b);
int CmpSocreDes(STUDENT *a, STUDENT *b);
int CmpNum(STUDENT *a, STUDENT *b);
int CmpName(STUDENT *a, STUDENT *b);
void SearchNum(STUDENT *head, int stunum, int coursenum);
void SearchName(STUDENT *head, int stunum, int coursenum);
int IsMatch(char *s, char *p);
void Analysis(STUDENT *head, int stunum, int coursenum);
void WritetoFile(STUDENT *head, int stunum, int coursenum);
STUDENT *ClearRecord(STUDENT *head);
STUDENT *ReadfromFile(STUDENT *head, int *stunum, int *coursenum);

int main(int argc, char const *argv[])
{
    int choice;
    int stunum = 0, coursenum = 0;
    STUDENT *head = NULL; //定义头节点
    system("color E0");   //调整程序底色
    system("title Manage System for Students' Grades V6.0");
    while (TRUE)
    {
        choice = DisplayMenu();
        system("cls");
        switch (choice)
        {
        case 0: //退出
            exit(0);
        case 1:                                  //录入成绩
            printf("\t\t\tNumber of students:"); //读取学生数和课程数
            do
            {
                scanf("%d", &stunum);
                if (stunum < 1)
                {
                    printf("\t\t\tNumber of students must be bigger than 1!\n");
                    printf("\t\t\tInput again:");
                }
            } while (stunum < 1);
            printf("\t\t\tNumber of courses:");
            do
            {
                scanf("%d", &coursenum);
                if (coursenum < 1 || coursenum > MAX_COURSENUM)
                {
                    printf("\t\t\tNumber of courses must be between 1 and %d !\n", MAX_COURSENUM);
                    printf("\t\t\tInput again:");
                }
            } while (coursenum < 1 || coursenum > MAX_COURSENUM);
            head = CreateList(stunum, coursenum);
            system("cls");
            if (head != NULL)
            {
                printf("\t\t\tInput successfully!\n");
            }
            else
            {
                printf("\t\t\tFailed!\n");
            }
            break;
        case 2: //计算课程总分平均分
            SumAverCourse(head, stunum, coursenum);
            break;
        case 3: //计算学生总分平均分
            SumAverStudent(head, stunum);
            break;
        case 4: //按总分降序排序
            if ((head = Sort(head, stunum, CmpSocreDes)) != NULL)
            {
                printf("\t\t\tSort in descending order by total score:\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 5: //按总分顺序排序
            if ((head = Sort(head, stunum, CmpScoreAsc)) != NULL)
            {
                printf("\t\t\tSort in ascending order by total score:\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 6: //按学号排序
            if ((head = Sort(head, stunum, CmpNum)) != NULL)
            {
                printf("\t\t\tSort in ascending order by number:\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 7: //按姓名排序
            if ((head = Sort(head, stunum, CmpName)) != NULL)
            {
                printf("\t\t\tSort in dictionary order by name\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 8: //按学号查找
            SearchNum(head, stunum, coursenum);
            break;
        case 9: //按姓名查找
            SearchName(head, stunum, coursenum);
            break;
        case 10: //成绩分析
            Analysis(head, stunum, coursenum);
            break;
        case 11: //列出记录
            ListRecord(head, stunum, coursenum);
            break;
        case 12: //写入文件
            WritetoFile(head, stunum, coursenum);
            break;
        case 13: //读出文件
            if ((head = ReadfromFile(head, &stunum, &coursenum)) != NULL)
            {
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 14: //清除记录
            head = ClearRecord(head);
            break;
        default: //choice大于14或小于0时, 提示错误
            printf("\t\t\t══════════════════════════════════════════════════════\n");
            printf("\t\t\tInput error! Try again.\n\a");
            printf("\t\t\t══════════════════════════════════════════════════════\n");
        }
        system("pause"); //暂停
    }
    return 0;
}

//功能: 打印菜单
//返回值: 用户的选择, 为int类型(没有检查范围)
int DisplayMenu(void)
{
    int choice = -1; //初始化choice为-1
    system("cls");   //清屏
    printf("\n\n");
    printf("\t\t\t               Manage System for Students' Grades V6.0\n");
    printf("\t\t\t╔══════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║          1.  Input record                                                ║\n");
    printf("\t\t\t║          2.  Caculate total and average score of every course            ║\n");
    printf("\t\t\t║          3.  Caculate total and average score of every student           ║\n");
    printf("\t\t\t║          4.  Sort in descending order by total score of every student    ║\n");
    printf("\t\t\t║          5.  Sort in ascending order by total score of every student     ║\n");
    printf("\t\t\t║          6.  Sort in ascending order by number                           ║\n");
    printf("\t\t\t║          7.  Sort in dictionary order by name                            ║\n");
    printf("\t\t\t║          8.  Search by number                                            ║\n");
    printf("\t\t\t║          9.  Search by name                                              ║\n");
    printf("\t\t\t║          10. Statistic analysis for every course                         ║\n");
    printf("\t\t\t║          11. List record                                                 ║\n");
    printf("\t\t\t║          12. Write to a file                                             ║\n");
    printf("\t\t\t║          13. Read from a file                                            ║\n");
    printf("\t\t\t║          14. Clear record                                                ║\n");
    printf("\t\t\t║          0.  Exit                                                        ║\n");
    printf("\t\t\t╚══════════════════════════════════════════════════════════════════════════╝\n");
    printf("\n\n");
    printf("\t\t\t Please input your choice:");
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n') //清除缓冲区
            ;                     //因为fflush()不在C标准里,所以不使用
    }
    return choice;
}

//功能: 被CreateList和ReadfromFile调用,创建空链表
//返回值: 链表的头指针, NULL表示创建失败
STUDENT *CreateEmptyList(int stunum, int coursenum)
{
    STUDENT *head; //链表头指针
    STUDENT *p1, *p2;
    for (int i = 0; i < stunum; i++)
    {
        p1 = (STUDENT *)malloc(LEN);
        if (p1 == NULL) //申请不到内存则返回
        {
            printf("\t\t\tNo enough memory!\n");
            return NULL;
        }
        p1->next = NULL;
        if (i == 0)
        {
            head = p2 = p1;
        }
        else
        {
            p2->next = p1;
            p2 = p1;
        }
    }
    return head;
}

//功能: 通过用户输入创建链表
//返回值: 链表的头指针, NULL表示创建失败
STUDENT *CreateList(int stunum, int coursenum)
{
    STUDENT *head = CreateEmptyList(stunum, coursenum);
    if (head == NULL) //如果链表创建失败则返回空
    {
        return NULL;
    }
    STUDENT *p = head; //指针p用于编辑空链表
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    for (int i = 0; i < stunum; i++)
    {
        p->sum = 0;
        p->aver = 0.0;
        printf("\t\t\tInput student number: ");
        scanf("%I64d", &p->num);
        printf("\t\t\tInput student name: ");
        scanf("%19s", p->name);                  //%19s表示输入字符串不大于19,防止溢出
        printf("\t\t\tInput scores in order: "); //按照课程顺序输入成绩
        for (int j = 0; j < coursenum; j++)
        {
            scanf("%f", &p->score[j]);
            p->sum += p->score[j];
        }
        p->aver = p->sum / coursenum;
        printf("\t\t\t══════════════════════════════════════════════════════\n");
        p = p->next;
    }
    return head;
}

//功能: 提示用户没有成绩记录
void DisplayNoRecord(void)
{
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    printf("\t\t\tThere's no record! Input or read from a file first.\n");
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 显示每门课总分平均分
void SumAverCourse(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    float sum;
    if (head == NULL) //没有记录就返回
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    for (int i = 0; i < coursenum; i++)
    {
        p = head;
        sum = 0.0;
        do
        {
            sum += p->score[i];
            p = p->next;
        } while (p != NULL);
        printf("\t\t\tCourse %d: Sum: %.1f, Average: %.1f\n", i + 1, sum, sum / stunum);
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 显示每位学生总分平均分
void SumAverStudent(STUDENT *head, int stunum)
{
    STUDENT *p = head;
    if (head == NULL) //没有记录就返回
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    for (int i = 0; i < stunum; i++)
    {
        printf("\t\t\tStudent %d: Name: %s,", i + 1, p->name);
        printf(" Sum: %.1f, Average: %.1f\n", p->sum, p->aver);
        p = p->next;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 比较总分(顺序)
int CmpScoreAsc(STUDENT *a, STUDENT *b)
{
    return a->sum > b->sum;
}

//功能: 比较总分(降序)
int CmpSocreDes(STUDENT *a, STUDENT *b)
{
    return a->sum < b->sum;
}

//功能: 比较学号
int CmpNum(STUDENT *a, STUDENT *b)
{
    return a->num > b->num;
}

//功能: 比较姓名
int CmpName(STUDENT *a, STUDENT *b)
{
    return strcmp(a->name, b->name) > 0;
}

//功能: 通用的排序函数, 参数里面的函数指针cmp用来比较大小
//返回值: 链表的头指针, NULL表示链表为空
STUDENT *Sort(STUDENT *head, int stunum, int (*cmp)(STUDENT *a, STUDENT *b))
{
    STUDENT *endpt; //控制循环比较
    STUDENT *p;     //临时指针变量
    STUDENT *p1, *p2;
    if (head == NULL)
    {
        DisplayNoRecord();
        return NULL;
    }
    p1 = (STUDENT *)malloc(LEN);
    p1->next = head; //增加一个节点，放在第一个节点的前面
    head = p1;       //让head指向p1节点，排序完成后，再把p1释放掉
    for (endpt = NULL; endpt != head; endpt = p)
    {
        for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
        {
            if ((*cmp)(p1->next, p1->next->next)) //如果前面的节点键值比后面节点的键值大，则交换
            {
                p2 = p1->next->next;
                p1->next->next = p2->next;
                p2->next = p1->next;
                p1->next = p2;
                p = p1->next->next;
            }
        }
    }
    p1 = head;         //把p1的信息去掉
    head = head->next; //让head指向排序后的第一个节点
    free(p1);          //释放p1
    p1 = NULL;         //p1置为NULL
    return head;
}

//功能: 列出记录的学生成绩
void ListRecord(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    printf("\t\t\tNo.\tName"); //打印每列的标题
    for (int i = 1; i <= coursenum; i++)
    {
        printf("\tC.%d", i);
    }
    printf("\tSum\tAverage\n");
    for (int j = 0; j < stunum; j++)
    {
        printf("\t\t\t%I64d\t%s\t", p->num, p->name);
        for (int i = 0; i < coursenum; i++)
        {
            printf("%.1f\t", p->score[i]);
        }
        printf("%.1f\t%.1f\n", p->sum, p->sum / coursenum);
        p = p->next; //移到下一个节点
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 通过学号(或学号的一部分)查找
void SearchNum(STUDENT *head, int stunum, int coursenum)
{
    char query[20];    //查询语句
    char tmp[20];      //将学号转化为字符串临时存储
    int found = 0;     //查找到标记
    STUDENT *p = head; //指针p用于访问链表元素
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    printf("\t\t\tInput the number to search:");
    scanf("%20s", query); //%20s防止溢出
    for (int i = 0; i < stunum; i++)
    {
        ltoa(p->num, tmp, 10);
        if (strstr(tmp, query)) //判断query是否是tmp字串
        {
            found = 1; //标记已找到
            printf("\t\t\t%I64d\t%s\t", p->num, p->name);
            for (int j = 0; j < coursenum; j++)
            {
                printf("%.1f\t", p->score[j]);
            }
            printf("%.1f\t%.1f\n", p->sum, p->aver);
        }
        p = p->next;
    }
    if (!found)
    {
        printf("\t\t\tNot found!\n");
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 通过姓名查找
void SearchName(STUDENT *head, int stunum, int coursenum)
{
    char query[20];    //查询语句
    int found = 0;     //查找到标记
    STUDENT *p = head; //指针p用于访问链表元素
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    printf("\t\t\t\"?\" for 1 character, \"*\" for 0-N character(s):\n");
    printf("\t\t\tInput the name to search:");
    scanf("%20s", query); //%20s防止溢出
    for (int i = 0; i < stunum; i++)
    {
        if (IsMatch(p->name, query)) //判断query是否是name字串
        {
            found = 1; //标记已找到
            printf("\t\t\t%I64d\t%s\t", p->num, p->name);
            for (int j = 0; j < coursenum; j++)
            {
                printf("%.1f\t", p->score[j]);
            }
            printf("%.1f\t%.1f\n", p->sum, p->aver);
        }
        p = p->next;
    }
    if (!found)
    {
        printf("\t\t\tNot found!\n");
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 通过通配符进行模糊匹配
//其中 "?" 表示1个字符, "*" 表示任意字符串(包括空字符串)
//返回值: 1表示匹配, 0表示不匹配
//思想: 动态规划, 其中状态转移方程是:
//p 当前字符是*:
//      dp[i+1][j+1] = dp[i][j+1] || dp[i+1][j]
//p 当前字符不是*:
//      dp[i+1][j+1] = dp[i][j] && s[i] == p[j]
int IsMatch(char *s, char *p)
{
    int slen = strlen(s), plen = strlen(p);
    //辅助数组dp，dp[i][j]表示s(0~i-1)与p(0~j-1)子串是否完全匹配
    int dp[20][20];
    dp[0][0] = 1; //s为空字符串 && p为空字符串
    for (int i = 1; i <= slen; i++)
    {
        dp[i][0] = 0; //s不为空，p为空字符串
    }
    for (int j = 1; j <= plen; j++)
    {
        dp[0][j] = (p[j - 1] == '*' && dp[0][j - 1]); //s为空字符串，p不为空
    }
    //需s和p完全匹配，外层循环对p进行遍历
    for (int j = 1; j <= plen; j++)
    {
        for (int i = 1; i <= slen; i++)
        {
            if (p[j - 1] != '*')
                //若p[j-1]不为*，需判断dp[i-1][j-1])，并且s[i-1]与p[j-1]匹配
                dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '?' == p[j - 1]);
            else
                //若p[j-1]为*,需判断s(0~i-2)与p(0~j-1)是否匹配(当前*匹配s[i-1]及之前部分字符)
                //或者判断s(0~i-1)与p(0~j-2)是否匹配(当前*匹配空字符串)
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
        }
    }
    return dp[slen][plen];
}

//功能: 对每门课程进行成绩分析
void Analysis(STUDENT *head, int stunum, int coursenum)
{
    int a[5] = {0}; //数组 a[5] 存储各成绩段学生人数
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    STUDENT *p = head;
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    for (int i = 0; i < coursenum; i++)
    {
        memset(a, 0, sizeof(a)); //每次循环开始将a清零
        p = head;
        for (int j = 0; j < stunum; j++)
        {
            if (p->score[i] < 60)
            {
                a[0]++;
            }
            else if (p->score[i] < 70)
            {
                a[1]++;
            }
            else if (p->score[i] < 80)
            {
                a[2]++;
            }
            else if (p->score[i] < 90)
            {
                a[3]++;
            }
            else if (p->score[i] <= 100)
            {
                a[4]++;
            }
            p = p->next;
        }
        printf("\t\t\tCourse %d:\n", i + 1); //打印该课程成绩分析
        printf("\t\t\t  0-59: %d\t%.2f%%\n", a[0], 100 * a[0] / (float)stunum);
        printf("\t\t\t 60-69: %d\t%.2f%%\n", a[1], 100 * a[1] / (float)stunum);
        printf("\t\t\t 70-79: %d\t%.2f%%\n", a[2], 100 * a[2] / (float)stunum);
        printf("\t\t\t 80-89: %d\t%.2f%%\n", a[3], 100 * a[3] / (float)stunum);
        printf("\t\t\t90-100: %d\t%.2f%%\n", a[4], 100 * a[4] / (float)stunum);
        printf("\t\t\t══════════════════════════════════════════════════════\n");
    }
}

//功能: 将成绩记录写入文件score_record.txt中
void WritetoFile(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head; //指针p用于访问链表元素
    FILE *fp;
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    if ((fp = fopen("score_record.txt", "w")) == NULL)
    {
        printf("\t\t\tFailed to open score_record.txt\n\a");
        return;
    }
    fprintf(fp, "%d\t%d\n", stunum, coursenum);
    for (int i = 0; i < stunum; i++)
    {
        fprintf(fp, "%12I64d%19s", p->num, p->name);
        for (int j = 0; j < coursenum; j++)
        {
            fprintf(fp, "%12.0f", p->score[j]);
        }
        fprintf(fp, "%12.0f%12.0f\n", p->sum, p->aver);
        p = p->next;
    }
    fclose(fp);
    printf("\t\t\tWrite Successfully!\n");
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 通过读取文件创建链表
//返回值: 链表的头指针, NULL表示创建失败
STUDENT *ReadfromFile(STUDENT *head, int *stunum, int *coursenum)
{
    STUDENT *p; //指针p用来访问创建的空链表元素
    FILE *fp;
    if ((fp = fopen("score_record.txt", "r")) == NULL)
    {
        printf("\t\t\tFail to open score_record.txt\n");
        return NULL;
    }
    fscanf(fp, "%d\t%d\n", stunum, coursenum); //读取学生数和课程数
    if ((head = CreateEmptyList(*stunum, *coursenum)) == NULL)
    {
        fclose(fp); //如果内存不足，关闭文件后再退出
        return NULL;
    }
    p = head;
    for (int i = 0; i < *stunum; i++)
    {
        fscanf(fp, "%12I64d%19s", &p->num, p->name);
        for (int j = 0; j < *coursenum; j++)
        {
            fscanf(fp, "%12f", &p->score[j]);
        }
        fscanf(fp, "%12f%12f", &p->sum, &p->aver);
        p = p->next;
    }
    printf("\t\t\tRead Successfully!\n");
    fclose(fp);
    return head;
}

//功能: 清空链表
//返回值: 指向STUDENT的指针, 为NULL则成功
STUDENT *ClearRecord(STUDENT *head)
{
    if (head == NULL)
    {
        DisplayNoRecord();
        return head;
    }
    STUDENT *p = head, *pr = NULL;
    char choice = '0';
    while (getchar() != '\n') //清除缓冲区
        ;
    printf("\t\t\tAre you sure? (Y/N)");
    scanf("%c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
        while (p != NULL)
        {
            pr = p;
            p = p->next;
            free(pr);
        }
        printf("\t\t\tCleared successfully!\n");
        return NULL;
    }
    else
    {
        printf("\t\t\tCanceled!\n");
        return head;
    }
}
