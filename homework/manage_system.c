#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define MAX_NAMELEN 20
#define MAX_COURSENUM 6
#define LEN sizeof(struct Student)
#define ASCENDING 1
#define DESCENDING 0

typedef struct Student
{
    long long num;
    char name[MAX_NAMELEN];
    float score[MAX_COURSENUM];
    float sum;
    float aver;
    struct Student *next;
} STUDENT;

int DisplayMenu(void);
void ListRecord(STUDENT *head, int stunum, int coursenum);
STUDENT *CreateList(int stunum, int coursenum);
STUDENT *CreateEmptyList(int stunum, int coursenum);
void SumAverCourse(STUDENT *head, int stunum, int coursenum);
void SumAverStudent(STUDENT *head, int stunum, int coursenum);
STUDENT *SortbyScore(STUDENT *head, int stunum, int order);
STUDENT *SortbyNumber(STUDENT *head);                              //按学号由小到大排出成绩表
STUDENT *SortbyName(STUDENT *head, int stunum);                    //按姓名的字典顺序排出成绩表
void SearchNum(STUDENT *head, int stunum, int coursenum);          //按学号查询学生排名及其考试成绩
void SearchName(STUDENT *head, int stunum, int coursenum);         //按姓名查询学生排名及其考试成绩
void Analysis(STUDENT *head, int stunum, int coursenum);           //按类别及比例输出
void WritetoFile(STUDENT *head, int stunum, int coursenum);        //将每个学生的纪录信息写入文件
STUDENT *ReadfromFile(STUDENT *head, int *stunum, int *coursenum); //从文件中读出每个学生的纪录信息并显示

int main(int argc, char const *argv[])
{
    int choice;
    int stunum = 0, coursenum = 0;
    STUDENT *head = NULL; //定义头节点
    // head = (STUDENT *)malloc(LEN);
    system("color E0");
    system("title Manage System for Students' Grades V6.0");
    while (TRUE)
    {
        choice = DisplayMenu();
        system("cls");
        switch (choice)
        {
        case 0:
            exit(0);
        case 1:
            system("cls");
            printf("\t\t\tNumber of students:");
            scanf("%d", &stunum);
            printf("\t\t\tNumber of courses:");
            scanf("%d", &coursenum);
            head = CreateList(stunum, coursenum);
            system("cls");
            if (head != NULL)
            {
                printf("\t\t\tInput successfully!");
            }
            break;
        case 2:
            system("cls");
            SumAverCourse(head, stunum, coursenum);
            break;
        case 3:
            system("cls");
            SumAverStudent(head, stunum, coursenum);
            break;
        case 4:
            printf("\t\t\tSort in descending order by total score:\n");
            head = SortbyScore(head, stunum, DESCENDING);
            ListRecord(head, stunum, coursenum);
            break;
        case 5:
            printf("\t\t\tSort in ascending order by total score:\n");
            head = SortbyScore(head, stunum, ASCENDING);
            ListRecord(head, stunum, coursenum);
            break;
        case 6:
            system("cls");
            printf("\t\t\tSort in ascending order by number:\n");
            head = SortbyNumber(head);
            ListRecord(head, stunum, coursenum);
            break;
        case 7:
            system("cls");
            printf("\t\t\tSort in dictionary order by name\n");
            head = SortbyName(head,stunum);
            ListRecord(head, stunum, coursenum);
            break;
        case 8:
            system("cls");
            printf("\t\t\tInput the number to search:\n");
            SearchNum(head, stunum, coursenum);
            break;
        case 9:
            system("cls");
            printf("\t\t\tInput the name to search:\n");
            SearchName(head, stunum, coursenum);
            break;
        case 10:
            system("cls");
            Analysis(head, stunum, coursenum);
            break;
        case 11:
            system("cls");
            ListRecord(head, stunum, coursenum);
            break;
        case 12:
            system("cls");
            WritetoFile(head, stunum, coursenum);
            break;
        case 13:
            system("cls");
            head = ReadfromFile(head, &stunum, &coursenum);
            break;
        default:
            system("cls");
            printf("\t\t\tInput error! Try again.\n\a");
            break;
        }
    }
    return 0;
}

int DisplayMenu(void)
{
    int choice = -1;
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
        getchar();
    }
    return choice;
}

STUDENT *CreateEmptyList(int stunum, int coursenum)
{
    STUDENT *head;
    STUDENT *p1, *p2;
    for (int i = 0; i < stunum; i++)
    {
        p1 = (STUDENT *)malloc(LEN);
        if (p1 == NULL)
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

STUDENT *CreateList(int stunum, int coursenum)
{
    STUDENT *head = CreateEmptyList(stunum, coursenum);
    STUDENT *p = head;
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    for (int i = 0; i < stunum; i++)
    {
        p->sum = 0;
        p->aver = 0.0;
        printf("\t\t\tInput student number: ");
        scanf("%lld", &p->num);
        printf("\t\t\tInput student name: ");
        scanf("%s", p->name);
        printf("\t\t\tInput scores in order: ");
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

void SumAverCourse(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    float sum;
    if (head != NULL)
    {
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
    else
    {
        printf("\t\t\t══════════════════════════════════════════════════════\n");
        printf("\t\t\tThere's no record! Input or read from a file first.\n");
        printf("\t\t\t══════════════════════════════════════════════════════\n");
    }
}

void SumAverStudent(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    if (head != NULL)
    {
        printf("\t\t\t══════════════════════════════════════════════════════\n");
        for (int i = 0; i < stunum; i++)
        {
            printf("\t\t\tStudent %d: Name: %s, Sum: %.1f, Average: %.1f\n", i + 1, p->name, p->sum, p->aver);
            p = p->next;
        }
        printf("\t\t\t══════════════════════════════════════════════════════\n");
    }
    else
    {
        printf("\t\t\t══════════════════════════════════════════════════════\n");
        printf("\t\t\tThere's no record! Input or read from a file first.\n");
        printf("\t\t\t══════════════════════════════════════════════════════\n");
    }
}

STUDENT *SortbyScore(STUDENT *head, int stunum, int order)
{
    STUDENT *endpt; //控制循环比较
    STUDENT *p;     //临时指针变量
    STUDENT *p1, *p2;

    p1 = (STUDENT *)malloc(LEN);
    p1->next = head; //注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址
    head = p1;       //让head指向p1节点，排序完成后，我们再把p1节点释放掉

    for (endpt = NULL; endpt != head; endpt = p)
    {
        for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
        {
            if (order == ASCENDING ? p1->next->sum > p1->next->next->sum : p1->next->sum < p1->next->next->sum) //如果前面的节点键值比后面节点的键值大，则交换
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

void ListRecord(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    if (head != NULL) //只要不是空链表，就输出链表中所有节点
    {
        printf("\t\t\t══════════════════════════════════════════════════════\n");
        printf("\t\t\tNo.\tName\tCourses\tSum\tAverage\n");
        do
        {
            printf("\t\t\t%lld\t%s\t", p->num, p->name);
            for (int i = 0; i < coursenum; i++)
            {
                printf("%.0f\t", p->score[i]);
            }
            printf("%.0f\t%.0f\n", p->sum, p->sum / coursenum);
            p = p->next; //移到下一个节点
        } while (p != NULL);
        printf("\t\t\t══════════════════════════════════════════════════════\n");
    }
}

STUDENT *SortbyNumber(STUDENT *head)
{
    STUDENT *endpt; //控制循环比较
    STUDENT *p;     //临时指针变量
    STUDENT *p1, *p2;

    p1 = (STUDENT *)malloc(LEN);
    p1->next = head; //注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址
    head = p1;       //让head指向p1节点，排序完成后，我们再把p1节点释放掉

    for (endpt = NULL; endpt != head; endpt = p)
    {
        for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
        {
            if (p1->next->num > p1->next->next->num) //如果前面的节点键值比后面节点的键值大，则交换
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

STUDENT *SortbyName(STUDENT *head, int stunum)
{
    STUDENT *endpt; //控制循环比较
    STUDENT *p;     //临时指针变量
    STUDENT *p1, *p2;

    p1 = (STUDENT *)malloc(LEN);
    p1->next = head; //注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址
    head = p1;       //让head指向p1节点，排序完成后，我们再把p1节点释放掉

    for (endpt = NULL; endpt != head; endpt = p)
    {
        for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
        {
            if (strcmp(p1->next->name, p1->next->next->name) > 0) //如果前面的节点键值比后面节点的键值大，则交换
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

void SearchNum(STUDENT *head, int stunum, int coursenum)
{
}

void SearchName(STUDENT *head, int stunum, int coursenum)
{
}

void Analysis(STUDENT *head, int stunum, int coursenum)
{
    int a[5] = {0};
    STUDENT *p = head;
    for (int i = 0; i < coursenum; i++)
    {
        p = head;
        do
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

        } while (p != NULL);
        printf("\t\t\tCourse %d:\n", i + 1);
        printf("\t\t\t  0-59: %d\t%.2f%%\n", a[0], 100 * a[0] / (double)stunum);
        printf("\t\t\t 60-69: %d\t%.2f%%\n", a[1], 100 * a[1] / (double)stunum);
        printf("\t\t\t 70-79: %d\t%.2f%%\n", a[2], 100 * a[2] / (double)stunum);
        printf("\t\t\t 80-89: %d\t%.2f%%\n", a[3], 100 * a[3] / (double)stunum);
        printf("\t\t\t90-100: %d\t%.2f%%\n", a[4], 100 * a[4] / (double)stunum);
        printf("\t\t\t══════════════════════════════════════════════════════\n");
    }
}

void WritetoFile(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    FILE *fp;
    printf("\t\t\t══════════════════════════════════════════════════════\n");
    if ((fp = fopen("score_record.txt", "w")) == NULL)
    {
        printf("\t\t\tFail to open score_record.txt\n\a");
        return;
    }
    fprintf(fp, "%d\t%d\n", stunum, coursenum);
    for (int i = 0; i < stunum; i++)
    {
        fprintf(fp, "%12lld%15s", p->num, p->name);
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

STUDENT *ReadfromFile(STUDENT *head, int *stunum, int *coursenum)
{
    STUDENT *p;
    FILE *fp;
    if ((fp = fopen("score_record.txt", "r")) == NULL)
    {
        printf("\t\t\tFail to open score_record.txt\n");
        return NULL;
    }
    fscanf(fp, "%d\t%d\n", stunum, coursenum);
    head = CreateEmptyList(*stunum, *coursenum);
    p = head;
    for (int i = 0; i < *stunum; i++)
    {
        fscanf(fp, "%12lld%15s", &p->num, &p->name);
        for (int j = 0; j < *coursenum; j++)
        {
            fscanf(fp, "%12f", &p->score[j]);
        }
        fscanf(fp, "%12f%12f", &p->sum, &p->aver);
        p = p->next;
    }
    printf("\t\t\tRead Successfully!\n");
    fclose(fp);
    ListRecord(head, *stunum, *coursenum);
    return head;
}
