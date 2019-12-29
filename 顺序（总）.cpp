#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXSIDE 10000

typedef struct{
    int num;
    char name[30];
    double pri;
}Book;

typedef struct LNode *List;
struct LNode{
	Book bookdate[MAXSIDE];
	int Last;
};

//��ʼ��
List MakeEmptry();
//����
void Print(List L);
//����
List sorting(List L);
//����
List Insert(List L,int num,char* name,double pri);
//��λɾ��
List Delete(List L,int x);
//ȡ����
void Length(List L);

//�޸ļ۸� 
void adjust_price(List L);
//����
void inverse_order(List L); 
//������ 
void Print_therich(List L);
//�������
void Print_thefavour(List L);
//��λ���
void Print_thebest(List L); 
//��λ���� 
List BitInsert(List L);
//ȥ�� 
List Delete_re(List L);

//���� 
List Operation(int n,List L);
//�˵�
void Menu();
 
int main()
{
	int n=1;
	List L;
	while(n)
	{
		Menu();
		scanf("%d",&n);
		L=Operation(n,L);
	}
	if(L!=NULL)
	free(L);
	return 0;
}

void Menu()
{
	printf("��ѡ��Ҫ���еĲ�����\n");
	printf("1.�������\n2.����\n3.�۸���Ϣ����\n4.����\n5.������ͼ��\n");
	printf("6.��������\n7.��λ����\n8.�������\n9.�������\n10.ȥ���ظ�ͼ��\n");
	printf("0.�˳�\n");
}

List Operation(int n,List L)
{
	int x;
	switch(n){
		case 0:
		break;
		case 1:
			L=MakeEmptry();
			Print(L);
		break;
		case 2:
			L=sorting(L);
			Print(L);
		break;
		case 3:
			adjust_price(L);
			Print(L);
		break;
		case 4:
			inverse_order(L);
			Print(L);
		break;
		case 5:
			Print_therich(L);
		break;
		case 6:
			Print_thefavour(L);
		break;
		case 7:
			Print_thebest(L);
		break;
		case 8:
			L=BitInsert(L);
    		Print(L);
		break;
		case 9:
			printf("������ɾ��ͼ��λ�ã�");
			scanf("%d",&x);
			L=Delete(L,x);
			Print(L);
		break;
		case 10:
			Delete_re(L);
    		Print(L);
		break;
	}
	return L;
}

List MakeEmptry()//����˳�����ͼ����Ϣ������˳����ַ
{
    int num,n;
    char name[30];
    double pri;
	List L;
	L=(List)malloc(sizeof(struct LNode));
	L->Last=0;
	printf("���������ͼ����Ŀ��");
	scanf("%d",&n);
	printf("�����������ͼ����Ϣ��\n");
	while(n&&scanf("%d%s%lf",&num,&name,&pri))
    {
        if(num==0&&name[0]=='0'&&pri==0)
            break;
        L=Insert(L,num,name,pri);//���ò��뺯�� 
        n--;
    }

	return L;
}

void Print(List L)
{
	int i;
	Length(L);
	for(i=0;i<=L->Last-1;i++)
	{
		printf("%d %s %.2lf\n",L->bookdate[i].num,L->bookdate[i].name,L->bookdate[i].pri);
	}
	putchar('\n');
	putchar('\n');
}

List Insert(List L,int num,char* name,double pri)
{
	if(L->Last==MAXSIDE-1)
	{
		printf("������");
		putchar('\n');
		return L;
	}
	else
		L->bookdate[L->Last].num=num;
		L->bookdate[L->Last].pri=pri;
		strcpy(L->bookdate[L->Last].name,name);
		L->Last++;
	return L;
}


//���� 
List sorting(List L)
{
    int i,j,flag=1;
    double tem;
    for(i=0;i<L->Last&&flag==1;i++)
    {
    	flag=0;
        for(j=0;j<L->Last-1;j++)
        {
            if(L->bookdate[j].pri<L->bookdate[j+1].pri)
            {
                tem=L->bookdate[j+1].pri;
                L->bookdate[j+1].pri=L->bookdate[j].pri;
                L->bookdate[j].pri=tem;
                flag=1;
            }
        }
    }
    return L;
}

void Length(List L)
{
	printf("%d\n",L->Last);
}

//���߼۸� 
void adjust_price(List L)
{
	int i;
	double average=0;
	for(i=0;i<=L->Last-1;i++)
	average=L->bookdate[i].pri+average;
	average=average/L->Last;
	for(i=0;i<=L->Last-1;i++)
	if(L->bookdate[i].pri<average)
	L->bookdate[i].pri*=1.2;
	else
	L->bookdate[i].pri*=1.1;
	printf("ԭƽ���۸�Ϊ��");
	printf("%.2lf\n",average);
}

//���� 
void inverse_order(List L)
{
	int num,i,j;
    char name[30];
    double pri;
    for(i=0,j=L->Last-1;i<=(L->Last-1)/2;i++,j--)
    {
    	num=L->bookdate[i].num;
    	strcpy(name,L->bookdate[i].name);
    	pri=L->bookdate[i].pri;
    	L->bookdate[i].num=L->bookdate[j].num;
    	strcpy(L->bookdate[i].name,L->bookdate[j].name);
    	L->bookdate[i].pri=L->bookdate[j].pri;
    	L->bookdate[j].num=num;
    	strcpy(L->bookdate[j].name,name);
    	L->bookdate[j].pri=pri;
	}
}

//������ 
void Print_therich(List L)
{
	int i=-1,k=0;
	double therich=L->bookdate[0].pri;
	
	for(i=0;i<=L->Last-1;i++)
	{
		if(L->bookdate[i].pri>therich)
		{
			therich=L->bookdate[i].pri;
		}
	}
	for(i=0;i<=L->Last-1;i++)
	{
		if(L->bookdate[i].pri==therich)
			k++;
	}
	printf("���ͼ����ĿΪ��");
	printf("%d\n",k);
	for(i=0;i<=L->Last-1;i++)
	{
		if(L->bookdate[i].pri==therich)
		printf("%d %s %.2lf\n",L->bookdate[i].num,L->bookdate[i].name,L->bookdate[i].pri);
	}
	putchar('\n');
	putchar('\n');
}

//�������
void Print_thefavour(List L)
{
	int i,n;
	char thefavour[30];
	printf("������Ҫ�ҵ��鱾��Ŀ��");
	scanf("%d",&n);
	while(n--)
	{
		printf("������Ҫ�ҵ�ͼ�����֣�\n");
		scanf("%s",thefavour);
		for(i=0;i<=L->Last-1;i++)
		{
			if(strcmp(L->bookdate[i].name,thefavour)==0)
			{
				printf("%d %s %.2lf\n",L->bookdate[i].num,L->bookdate[i].name,L->bookdate[i].pri);
				break;
			}
		}
		if(i==L->Last)
		{
			printf("��Ǹ��û��������\n");
			putchar('\n');
		} 
	}
	putchar('\n');
	putchar('\n');
}

//��λ���
void Print_thebest(List L)
{
	int i,n,m;
	printf("������Ҫ�ҵ��鱾��Ŀ��");
	scanf("%d",&n);
	while(n--)
	{
		printf("������Ҫ��ͼ���λ�ã�");
		scanf("%d",&m);
		if(m>=L->Last||m<1)
		{	printf("��Ǹ����λ���ϵ�ͼ�鲻���ڣ�\n");
			putchar('\n');
		} 
		else 
			printf("%d %s %.2lf\n",L->bookdate[m-1].num,L->bookdate[m-1].name,L->bookdate[m-1].pri);
	}
	putchar('\n');
}

//��λ���� 
List BitInsert(List L)
{
	int n;
    int num;
    char name[30];
    double pri;
    if(L->Last==MAXSIDE-1)
    {
    	printf("������");
    	putchar('\n');
		return L;
	}
	printf("���������λ�ã�");
	scanf("%d",&n);
	if(n<=0||n>L->Last+1)
	{ 
		printf("����λ�÷Ƿ���\n"); 
		putchar('\n');
		return L;
	}
	printf("���������ͼ����Ϣ��\n");
	scanf("%d%s%lf",&num,name,&pri);
	for(int i=L->Last-1;i>=n-1;i--)
	{
		L->bookdate[i+1].num=L->bookdate[i].num;
		strcpy(L->bookdate[i+1].name,L->bookdate[i].name);
		L->bookdate[i+1].pri=L->bookdate[i].pri;
	}
	L->Last++;
	L->bookdate[n-1].num=num;
	strcpy(L->bookdate[n-1].name,name);
	L->bookdate[n-1].pri=pri;
	printf("���ɹ���");
	putchar('\n');
	return L;
}

//��λɾ�� 
List Delete(List L,int x)
{
	if(L->Last<x||x<=0)
	{
		printf("ɾ��λ�÷Ƿ���\n");
		putchar('\n');
		return L;
	}
	for(int i=x-1;i<L->Last-1;i++)
	{
		L->bookdate[i].num=L->bookdate[i+1].num;
		strcpy(L->bookdate[i].name,L->bookdate[i+1].name);
		L->bookdate[i].pri=L->bookdate[i+1].pri;
	}
	L->Last--;
	putchar('\n');
	return L;
}

//ȥ�� 
List Delete_re(List L)
{
	int i,j;
	for(i=0;i<=L->Last-1;i++)
	{
		for(j=i+1;j<=L->Last-1;j++)
		if(L->bookdate[i].num==L->bookdate[j].num&&strcmp(L->bookdate[i].name,L->bookdate[i].name)==0&&L->bookdate[i].pri==L->bookdate[i].pri)
		{
			L=Delete(L,j+1);
			j--;
		}
	}
	Printf(��ȥ�سɹ���\n��);
	return L;
}


