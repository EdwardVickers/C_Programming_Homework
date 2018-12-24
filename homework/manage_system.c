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
int CmpScoreAsc(struct Student *a, struct Student *b);
int CmpSocreDes(struct Student *a, struct Student *b);
int CmpNum(struct Student *a, struct Student *b);
int CmpName(struct Student *a, struct Student *b);
void SearchNum(STUDENT *head, int stunum, int coursenum);
void SearchName(STUDENT *head, int stunum, int coursenum);
void Analysis(STUDENT *head, int stunum, int coursenum);
void WritetoFile(STUDENT *head, int stunum, int coursenum);
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
            scanf("%d", &stunum);
            printf("\t\t\tNumber of courses:");
            scanf("%d", &coursenum);
            head = CreateList(stunum, coursenum);
            system("cls");
            if (head != NULL)
            {
                printf("\t\t\tInput successfully!");
            }
            else
            {
                printf("\t\t\tFailed!");
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
            printf("\t\t\tInput the number to search:\n");
            SearchNum(head, stunum, coursenum);
            break;
        case 9: //按姓名查找
            printf("\t\t\tInput the name to search:\n");
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
        default: //choice大于13或小于0时, 提示错误
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
    printf("\t\t\t╔════════════════════════════════════════════════════════════════════════════╗\n");
    printf("\t\t\t║            1.  Input record                                                ║\n");
    printf("\t\t\t║            2.  Caculate total and average score of every course            ║\n");
    printf("\t\t\t║            3.  Caculate total and average score of every student           ║\n");
    printf("\t\t\t║            4.  Sort in descending order by total score of every student    ║\n");
    printf("\t\t\t║            5.  Sort in ascending order by total score of every student     ║\n");
    printf("\t\t\t║            6.  Sort in ascending order by number                           ║\n");
    printf("\t\t\t║            7.  Sort in dictionary order by name                            ║\n");
    printf("\t\t\t║            8.  Search by number                                            ║\n");
    printf("\t\t\t║            9.  Search by name                                              ║\n");
    printf("\t\t\t║            10. Statistic analysis for every course                         ║\n");
    printf("\t\t\t║            11. List record                                                 ║\n");
    printf("\t\t\t║            12. Write to a file                                             ║\n");
    printf("\t\t\t║            13. Read from a file                                            ║\n");
    printf("\t\t\t║            0.  Exit                                                        ║\n");
    printf("\t\t\t╚════════════════════════════════════════════════════════════════════════════╝\n");
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
            printf("No enough memory!\n");
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
        scanf("%lld", &p->num);
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
        printf("\t\t\tStudent %d: Name: %s, Sum: %.1f, Average: %.1f\n", i + 1, p->name, p->sum, p->aver);
        p = p->next;
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 比较总分(顺序)
int CmpScoreAsc(struct Student *a, struct Student *b)
{
    return a->sum > b->sum;
}

//功能: 比较总分(降序)
int CmpSocreDes(struct Student *a, struct Student *b)
{
    return a->sum < b->sum;
}

//功能: 比较学号
int CmpNum(struct Student *a, struct Student *b)
{
    return a->num > b->num;
}

//功能: 比较姓名
int CmpName(struct Student *a, struct Student *b)
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
    p1->next = head; //注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址
    head = p1;       //让head指向p1节点，排序完成后，我们再把p1节点释放掉

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
    p1 = NULL;         //p1置为NULL，保证不产生“野指针”，即地址不确定的指针变量
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
        printf("\tCourse %d", i);
    }
    printf("\tSum\tAverage\n");
    for (int j = 0; j < stunum; j++)
    {
        printf("\t\t\t%lld\t%s\t", p->num, p->name);
        for (int i = 0; i < coursenum; i++)
        {
            printf("%.1f\t", p->score[i]);
        }
        printf("%.1f\t%.1f\n", p->sum, p->sum / coursenum);
        p = p->next; //移到下一个节点
    }
    printf("\t\t\t══════════════════════════════════════════════════════\n");
}

//功能: 通过学号查找
void SearchNum(STUDENT *head, int stunum, int coursenum)
{
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
}

//功能: 通过姓名查找
void SearchName(STUDENT *head, int stunum, int coursenum)
{
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
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
        fprintf(fp, "%12lld%19s", p->num, p->name);
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
        fscanf(fp, "%12lld%19s", &p->num, &p->name);
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
