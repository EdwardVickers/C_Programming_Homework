//Name: ѧ���ɼ�����ϵͳ
//Date: 2018-12-21
//Author: 1180300902����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_NAMELEN 20             //������󳤶�
#define MAX_COURSENUM 6            //���γ���
#define LEN sizeof(struct Student) //�ṹ���С

typedef struct Student //��������ڵ�
{
    long long num;              //ѧ��
    char name[MAX_NAMELEN];     //����
    float score[MAX_COURSENUM]; //�ɼ�
    float sum;                  //�ܷ�
    float aver;                 //ƽ����
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
    STUDENT *head = NULL; //����ͷ�ڵ�
    system("color E0");   //���������ɫ
    system("title Manage System for Students' Grades V6.0");
    while (TRUE)
    {
        choice = DisplayMenu();
        system("cls");
        switch (choice)
        {
        case 0: //�˳�
            exit(0);
        case 1:                                  //¼��ɼ�
            printf("\t\t\tNumber of students:"); //��ȡѧ�����Ϳγ���
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
        case 2: //����γ��ܷ�ƽ����
            SumAverCourse(head, stunum, coursenum);
            break;
        case 3: //����ѧ���ܷ�ƽ����
            SumAverStudent(head, stunum);
            break;
        case 4: //���ֽܷ�������
            if ((head = Sort(head, stunum, CmpSocreDes)) != NULL)
            {
                printf("\t\t\tSort in descending order by total score:\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 5: //���ܷ�˳������
            if ((head = Sort(head, stunum, CmpScoreAsc)) != NULL)
            {
                printf("\t\t\tSort in ascending order by total score:\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 6: //��ѧ������
            if ((head = Sort(head, stunum, CmpNum)) != NULL)
            {
                printf("\t\t\tSort in ascending order by number:\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 7: //����������
            if ((head = Sort(head, stunum, CmpName)) != NULL)
            {
                printf("\t\t\tSort in dictionary order by name\n");
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 8: //��ѧ�Ų���
            SearchNum(head, stunum, coursenum);
            break;
        case 9: //����������
            SearchName(head, stunum, coursenum);
            break;
        case 10: //�ɼ�����
            Analysis(head, stunum, coursenum);
            break;
        case 11: //�г���¼
            ListRecord(head, stunum, coursenum);
            break;
        case 12: //д���ļ�
            WritetoFile(head, stunum, coursenum);
            break;
        case 13: //�����ļ�
            if ((head = ReadfromFile(head, &stunum, &coursenum)) != NULL)
            {
                ListRecord(head, stunum, coursenum);
            }
            break;
        case 14: //�����¼
            head = ClearRecord(head);
            break;
        default: //choice����14��С��0ʱ, ��ʾ����
            printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
            printf("\t\t\tInput error! Try again.\n\a");
            printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
        }
        system("pause"); //��ͣ
    }
    return 0;
}

//����: ��ӡ�˵�
//����ֵ: �û���ѡ��, Ϊint����(û�м�鷶Χ)
int DisplayMenu(void)
{
    int choice = -1; //��ʼ��choiceΪ-1
    system("cls");   //����
    printf("\n\n");
    printf("\t\t\t               Manage System for Students' Grades V6.0\n");
    printf("\t\t\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
    printf("\t\t\t�U          1.  Input record                                                �U\n");
    printf("\t\t\t�U          2.  Caculate total and average score of every course            �U\n");
    printf("\t\t\t�U          3.  Caculate total and average score of every student           �U\n");
    printf("\t\t\t�U          4.  Sort in descending order by total score of every student    �U\n");
    printf("\t\t\t�U          5.  Sort in ascending order by total score of every student     �U\n");
    printf("\t\t\t�U          6.  Sort in ascending order by number                           �U\n");
    printf("\t\t\t�U          7.  Sort in dictionary order by name                            �U\n");
    printf("\t\t\t�U          8.  Search by number                                            �U\n");
    printf("\t\t\t�U          9.  Search by name                                              �U\n");
    printf("\t\t\t�U          10. Statistic analysis for every course                         �U\n");
    printf("\t\t\t�U          11. List record                                                 �U\n");
    printf("\t\t\t�U          12. Write to a file                                             �U\n");
    printf("\t\t\t�U          13. Read from a file                                            �U\n");
    printf("\t\t\t�U          14. Clear record                                                �U\n");
    printf("\t\t\t�U          0.  Exit                                                        �U\n");
    printf("\t\t\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
    printf("\n\n");
    printf("\t\t\t Please input your choice:");
    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n') //���������
            ;                     //��Ϊfflush()����C��׼��,���Բ�ʹ��
    }
    return choice;
}

//����: ��CreateList��ReadfromFile����,����������
//����ֵ: �����ͷָ��, NULL��ʾ����ʧ��
STUDENT *CreateEmptyList(int stunum, int coursenum)
{
    STUDENT *head; //����ͷָ��
    STUDENT *p1, *p2;
    for (int i = 0; i < stunum; i++)
    {
        p1 = (STUDENT *)malloc(LEN);
        if (p1 == NULL) //���벻���ڴ��򷵻�
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

//����: ͨ���û����봴������
//����ֵ: �����ͷָ��, NULL��ʾ����ʧ��
STUDENT *CreateList(int stunum, int coursenum)
{
    STUDENT *head = CreateEmptyList(stunum, coursenum);
    if (head == NULL) //���������ʧ���򷵻ؿ�
    {
        return NULL;
    }
    STUDENT *p = head; //ָ��p���ڱ༭������
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    for (int i = 0; i < stunum; i++)
    {
        p->sum = 0;
        p->aver = 0.0;
        printf("\t\t\tInput student number: ");
        scanf("%I64d", &p->num);
        printf("\t\t\tInput student name: ");
        scanf("%19s", p->name);                  //%19s��ʾ�����ַ���������19,��ֹ���
        printf("\t\t\tInput scores in order: "); //���տγ�˳������ɼ�
        for (int j = 0; j < coursenum; j++)
        {
            scanf("%f", &p->score[j]);
            p->sum += p->score[j];
        }
        p->aver = p->sum / coursenum;
        printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
        p = p->next;
    }
    return head;
}

//����: ��ʾ�û�û�гɼ���¼
void DisplayNoRecord(void)
{
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    printf("\t\t\tThere's no record! Input or read from a file first.\n");
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

//����: ��ʾÿ�ſ��ܷ�ƽ����
void SumAverCourse(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    float sum;
    if (head == NULL) //û�м�¼�ͷ���
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
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
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

//����: ��ʾÿλѧ���ܷ�ƽ����
void SumAverStudent(STUDENT *head, int stunum)
{
    STUDENT *p = head;
    if (head == NULL) //û�м�¼�ͷ���
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    for (int i = 0; i < stunum; i++)
    {
        printf("\t\t\tStudent %d: Name: %s,", i + 1, p->name);
        printf(" Sum: %.1f, Average: %.1f\n", p->sum, p->aver);
        p = p->next;
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

//����: �Ƚ��ܷ�(˳��)
int CmpScoreAsc(STUDENT *a, STUDENT *b)
{
    return a->sum > b->sum;
}

//����: �Ƚ��ܷ�(����)
int CmpSocreDes(STUDENT *a, STUDENT *b)
{
    return a->sum < b->sum;
}

//����: �Ƚ�ѧ��
int CmpNum(STUDENT *a, STUDENT *b)
{
    return a->num > b->num;
}

//����: �Ƚ�����
int CmpName(STUDENT *a, STUDENT *b)
{
    return strcmp(a->name, b->name) > 0;
}

//����: ͨ�õ�������, ��������ĺ���ָ��cmp�����Ƚϴ�С
//����ֵ: �����ͷָ��, NULL��ʾ����Ϊ��
STUDENT *Sort(STUDENT *head, int stunum, int (*cmp)(STUDENT *a, STUDENT *b))
{
    STUDENT *endpt; //����ѭ���Ƚ�
    STUDENT *p;     //��ʱָ�����
    STUDENT *p1, *p2;
    if (head == NULL)
    {
        DisplayNoRecord();
        return NULL;
    }
    p1 = (STUDENT *)malloc(LEN);
    p1->next = head; //����һ���ڵ㣬���ڵ�һ���ڵ��ǰ��
    head = p1;       //��headָ��p1�ڵ㣬������ɺ��ٰ�p1�ͷŵ�
    for (endpt = NULL; endpt != head; endpt = p)
    {
        for (p = p1 = head; p1->next->next != endpt; p1 = p1->next)
        {
            if ((*cmp)(p1->next, p1->next->next)) //���ǰ��Ľڵ��ֵ�Ⱥ���ڵ�ļ�ֵ���򽻻�
            {
                p2 = p1->next->next;
                p1->next->next = p2->next;
                p2->next = p1->next;
                p1->next = p2;
                p = p1->next->next;
            }
        }
    }
    p1 = head;         //��p1����Ϣȥ��
    head = head->next; //��headָ�������ĵ�һ���ڵ�
    free(p1);          //�ͷ�p1
    p1 = NULL;         //p1��ΪNULL
    return head;
}

//����: �г���¼��ѧ���ɼ�
void ListRecord(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head;
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    printf("\t\t\tNo.\tName"); //��ӡÿ�еı���
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
        p = p->next; //�Ƶ���һ���ڵ�
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

//����: ͨ��ѧ��(��ѧ�ŵ�һ����)����
void SearchNum(STUDENT *head, int stunum, int coursenum)
{
    char query[20];    //��ѯ���
    char tmp[20];      //��ѧ��ת��Ϊ�ַ�����ʱ�洢
    int found = 0;     //���ҵ����
    STUDENT *p = head; //ָ��p���ڷ�������Ԫ��
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    printf("\t\t\tInput the number to search:");
    scanf("%20s", query); //%20s��ֹ���
    for (int i = 0; i < stunum; i++)
    {
        ltoa(p->num, tmp, 10);
        if (strstr(tmp, query)) //�ж�query�Ƿ���tmp�ִ�
        {
            found = 1; //������ҵ�
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
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

//����: ͨ����������
void SearchName(STUDENT *head, int stunum, int coursenum)
{
    char query[20];    //��ѯ���
    int found = 0;     //���ҵ����
    STUDENT *p = head; //ָ��p���ڷ�������Ԫ��
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    printf("\t\t\t\"?\" for 1 character, \"*\" for 0-N character(s):\n");
    printf("\t\t\tInput the name to search:");
    scanf("%20s", query); //%20s��ֹ���
    for (int i = 0; i < stunum; i++)
    {
        if (IsMatch(p->name, query)) //�ж�query�Ƿ���name�ִ�
        {
            found = 1; //������ҵ�
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
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

//����: ͨ��ͨ�������ģ��ƥ��
//���� "?" ��ʾ1���ַ�, "*" ��ʾ�����ַ���(�������ַ���)
//����ֵ: 1��ʾƥ��, 0��ʾ��ƥ��
//˼��: ��̬�滮, ����״̬ת�Ʒ�����:
//p ��ǰ�ַ���*:
//      dp[i+1][j+1] = dp[i][j+1] || dp[i+1][j]
//p ��ǰ�ַ�����*:
//      dp[i+1][j+1] = dp[i][j] && s[i] == p[j]
int IsMatch(char *s, char *p)
{
    int slen = strlen(s), plen = strlen(p);
    //��������dp��dp[i][j]��ʾs(0~i-1)��p(0~j-1)�Ӵ��Ƿ���ȫƥ��
    int dp[20][20];
    dp[0][0] = 1; //sΪ���ַ��� && pΪ���ַ���
    for (int i = 1; i <= slen; i++)
    {
        dp[i][0] = 0; //s��Ϊ�գ�pΪ���ַ���
    }
    for (int j = 1; j <= plen; j++)
    {
        dp[0][j] = (p[j - 1] == '*' && dp[0][j - 1]); //sΪ���ַ�����p��Ϊ��
    }
    //��s��p��ȫƥ�䣬���ѭ����p���б���
    for (int j = 1; j <= plen; j++)
    {
        for (int i = 1; i <= slen; i++)
        {
            if (p[j - 1] != '*')
                //��p[j-1]��Ϊ*�����ж�dp[i-1][j-1])������s[i-1]��p[j-1]ƥ��
                dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '?' == p[j - 1]);
            else
                //��p[j-1]Ϊ*,���ж�s(0~i-2)��p(0~j-1)�Ƿ�ƥ��(��ǰ*ƥ��s[i-1]��֮ǰ�����ַ�)
                //�����ж�s(0~i-1)��p(0~j-2)�Ƿ�ƥ��(��ǰ*ƥ����ַ���)
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
        }
    }
    return dp[slen][plen];
}

//����: ��ÿ�ſγ̽��гɼ�����
void Analysis(STUDENT *head, int stunum, int coursenum)
{
    int a[5] = {0}; //���� a[5] �洢���ɼ���ѧ������
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    STUDENT *p = head;
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    for (int i = 0; i < coursenum; i++)
    {
        memset(a, 0, sizeof(a)); //ÿ��ѭ����ʼ��a����
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
        printf("\t\t\tCourse %d:\n", i + 1); //��ӡ�ÿγ̳ɼ�����
        printf("\t\t\t  0-59: %d\t%.2f%%\n", a[0], 100 * a[0] / (float)stunum);
        printf("\t\t\t 60-69: %d\t%.2f%%\n", a[1], 100 * a[1] / (float)stunum);
        printf("\t\t\t 70-79: %d\t%.2f%%\n", a[2], 100 * a[2] / (float)stunum);
        printf("\t\t\t 80-89: %d\t%.2f%%\n", a[3], 100 * a[3] / (float)stunum);
        printf("\t\t\t90-100: %d\t%.2f%%\n", a[4], 100 * a[4] / (float)stunum);
        printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    }
}

//����: ���ɼ���¼д���ļ�score_record.txt��
void WritetoFile(STUDENT *head, int stunum, int coursenum)
{
    STUDENT *p = head; //ָ��p���ڷ�������Ԫ��
    FILE *fp;
    if (head == NULL)
    {
        DisplayNoRecord();
        return;
    }
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
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
    printf("\t\t\t�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
}

//����: ͨ����ȡ�ļ���������
//����ֵ: �����ͷָ��, NULL��ʾ����ʧ��
STUDENT *ReadfromFile(STUDENT *head, int *stunum, int *coursenum)
{
    STUDENT *p; //ָ��p�������ʴ����Ŀ�����Ԫ��
    FILE *fp;
    if ((fp = fopen("score_record.txt", "r")) == NULL)
    {
        printf("\t\t\tFail to open score_record.txt\n");
        return NULL;
    }
    fscanf(fp, "%d\t%d\n", stunum, coursenum); //��ȡѧ�����Ϳγ���
    if ((head = CreateEmptyList(*stunum, *coursenum)) == NULL)
    {
        fclose(fp); //����ڴ治�㣬�ر��ļ������˳�
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

//����: �������
//����ֵ: ָ��STUDENT��ָ��, ΪNULL��ɹ�
STUDENT *ClearRecord(STUDENT *head)
{
    if (head == NULL)
    {
        DisplayNoRecord();
        return head;
    }
    STUDENT *p = head, *pr = NULL;
    char choice = '0';
    while (getchar() != '\n') //���������
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
