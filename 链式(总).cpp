#include"stdio.h"
#include"string.h"
#include<stdlib.h>

typedef struct{
    int num;
    char name[30];
    double pri;
}Book;

typedef struct LNode{
	Book bookdata;
	struct LNode *next;
}LNode, *LinkList;

//初始化
LinkList MakeEmptry();
//遍历
void Print(LinkList L);
//插入
void Insert(LinkList *L,int num,char* name,double pri);
//取长度
int Length(LinkList L);
//删除链表
void FREE(LinkList L);
//排序
LinkList sorting(LinkList L);
//调价 
void adjust_price(LinkList L);
//逆序
LinkList inverse_order(LinkList L); 
//输出最贵 
void Print_therich(LinkList L);
//按名输出 
void Print_thefavour(LinkList L);
//按位输出 
void Print_thebest(LinkList L);
//按位插入
LinkList BitInsert(LinkList L);
//按位删除
LinkList Delete(LinkList L);
//去重
LinkList Delete_re(LinkList L);

//操作 
LinkList Operation(int n,LinkList L);
//菜单
void Menu();

int main()
{
	int n=1;
	LinkList L;
	while(n)
	{
		Menu();
		scanf("%d",&n);
		L=Operation(n,L);
	}
	if(L!=NULL)
	FREE(L);
	return 0;
}

void Menu()
{
	printf("请选择要进行的操作：\n");
	printf("1.建表并输出\n2.排序\n3.价格信息调整\n4.逆序\n5.输出最贵图书\n");
	printf("6.按名查找\n7.按位查找\n8.新书入库\n9.旧书出库\n10.去除重复图书\n");
	printf("0.退出\n");
}

LinkList Operation(int n,LinkList L)
{
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
			L=inverse_order(L);
			Print(L);
		break;
		case 5:
			Print_therich(L);
			putchar('\n');
		break;
		case 6:
			Print_thefavour(L);
			putchar('\n');
		break;
		case 7:
			Print_thebest(L);
			putchar('\n');
		break;
		case 8:
			L=BitInsert(L);
			Print(L);
		break;
		case 9:
			L=Delete(L);
			Print(L);
		break;
		case 10:
			L=Delete_re(L);
    		Print(L);
		break;
	}
	return L;
}

LinkList MakeEmptry()
{//创建图书库，返回头结点地址 
	int num,n;
    char name[30];
    double pri;
	LinkList L,Rear,t;
	L=(LinkList)malloc(sizeof(struct LNode));
	L->next=NULL;
	Rear=L;
	printf("请输入入库图书数目：");
	scanf("%d",&n);
	printf("请依次输入各图书信息：\n"); 
	while(n&&scanf("%d%s%lf",&num,&name,&pri))
    {
        if(num==0&&name[0]=='0'&&pri==0)
            break;
        Insert(&Rear,num,name,pri);//调用插入函数 
        n--;
    }
    Rear->next=NULL;
	t=L;
	L=L->next;
	free(t);
    return L;
}

void Insert(LinkList *lRear,int num,char* name,double pri)
{
	LinkList L;
	L=(LinkList)malloc(sizeof(struct LNode));
	L->next=NULL;
	L->bookdata.num=num;
	L->bookdata.pri=pri;
	strcpy(L->bookdata.name,name);
	(*lRear)->next=L;
	*lRear=L;
}

void Print(LinkList L)//输出函数 
{
	int i,len;
	len=Length(L);
	printf("%d\n",len);
	while(L)
	{
		printf("%d %s %.2lf\n",L->bookdata.num,L->bookdata.name,L->bookdata.pri);
		L=L->next;
	}
	putchar('\n');
	putchar('\n');
}

int Length(LinkList L)
{
	int count=0;
	while(L)
	{
		count++;
		L=L->next;
	}
	return count;
}

//删除链表
void FREE(LinkList L)
{
	while(L)
	{
		LinkList t=L;
		L=L->next;
		free(t);
	}
}

//排序
LinkList sorting(LinkList L)
{
	if(L==NULL||L->next==NULL)
		return L;
	int i,len,flag;
	len=Length(L);
	LinkList t1,t2;
	
	for(i=0;i<len;i++)
	{
		flag=0;
		t1=L;
		t2=L->next;
		while(t2)
		{
			if(t1->bookdata.pri<t2->bookdata.pri)
			{
				int num;
				char name[30];
				double pri;
				num=t1->bookdata.num;
				strcpy(name,t1->bookdata.name);
				pri=t1->bookdata.pri;
				t1->bookdata.num=t2->bookdata.num;
				strcpy(t1->bookdata.name,t2->bookdata.name);
				t1->bookdata.pri=t2->bookdata.pri;
				t2->bookdata.num=num;
				strcpy(t2->bookdata.name,name);
				t2->bookdata.pri=pri;
				flag=1;
			}
			t1=t2;
			t2=t2->next;
		}
		if(flag==0)
			return L;
	}
	return L;
}

//调价
void adjust_price(LinkList L)
{
	double average=0;
	int i,len;
	LinkList t;
	
	len=Length(L);
	t=L;
	while(t)
	{
		average=average+t->bookdata.pri;
		t=t->next;
	}
	average=average/len;
	printf("原平均价格为：");
	printf("%.2lf\n",average);
	t=L;
	while(t)
	{
		if(t->bookdata.pri<average)
		t->bookdata.pri*=1.2;
		else
		t->bookdata.pri*=1.1;
		t=t->next;
	}
	return;
}

//逆序
LinkList inverse_order(LinkList L)
{
	if(L->next==NULL)
	{	
		printf("逆序成功！\n");
		return L;
	} 
	LinkList t1,t2,t3;
	t1=L;
	t2=t1->next;
	t3=t2->next;
	
	while(1)
	{
		if(t1==L)
		{
			t1->next=NULL;
		}
		t2->next=t1;
		t1=t2;
		t2=t3;
		if(t2==NULL)
		break;
		t3=t3->next;
	}
	L=t1;
	printf("逆序成功！\n");
	return L;
}

//输出最贵 
void Print_therich(LinkList L)
{
	double therich;
	int k=0;
	therich=L->bookdata.pri;
	LinkList t=L->next;
	while(t)
	{
		if(t->bookdata.pri>therich)
		{
			therich=t->bookdata.pri;
		}
		t=t->next;
	}
	t=L;
	while(t)
	{
		if(t->bookdata.pri==therich)
		k++;
		t=t->next;
	}
	printf("最贵图书数目为：");
	printf("%d\n",k);
	t=L;
	while(t)
	{
		if(t->bookdata.pri==therich)
		printf("%d %s %.2lf\n",t->bookdata.num,t->bookdata.name,t->bookdata.pri);
		t=t->next;
	}
	return;
}

//按名输出
void Print_thefavour(LinkList L)
{
	char favour[30];
	int n;
	printf("请输入要找的图书数目：");
	scanf("%d",&n);
	while(n--)
	{
		LinkList t;
		t=L;
		printf("请输入要找的图书名字：\n");
		scanf("%s",&favour);
		while(t)
		{
			if(strcmp(favour,t->bookdata.name)==0)
			break;
			t=t->next;
		}
		if(t!=NULL)
		{
			printf("%d %s %.2lf\n",t->bookdata.num,t->bookdata.name,t->bookdata.pri);
		}
		else
			printf("抱歉，没有你的最爱！\n");
	} 
	return;
}

//按位输出 
void Print_thebest(LinkList L)
{
	int n,m,len;
	
	len=Length(L);
	printf("请输入要找的图书数目：");
	scanf("%d",&n);
	while(n--)
	{
		printf("请输入要找图书的位置：");
		scanf("%d",&m);
		if(m>0&&m<=len)
		{
			LinkList t=L;
			while(--m)
			{
				t=t->next;
			}
			printf("%d %s %.2lf\n",t->bookdata.num,t->bookdata.name,t->bookdata.pri);
		}
		else
			printf("抱歉，此位置上的图书不存在！\n");
	}

	return;
}

//按位插入
LinkList BitInsert(LinkList L)
{
	int n,len;
	printf("请输入插入图书的位置：");
	scanf("%d",&n);
	len=Length(L);
	if(n<1||n>len+1)
	{
		printf("插入位置非法！\n");
		return L;
	}
	else
	{
		LinkList t1,t2;
		t1=L;
		t2=(LinkList)malloc(sizeof(struct LNode));
		scanf("%d%s%lf",&t2->bookdata.num,&t2->bookdata.name,&t2->bookdata.pri);
		for(int i=n-2;i>0;i--)
		{
			t1=t1->next;
		}
		if(n==1)
		{
			t2->next=t1; 
			L=t2;
		} 
		else
		{
			t2->next=t1->next;
			t1->next=t2;
		}
		printf("入库成功！\n");
	}
	
	return L;
}

//按位删除
LinkList Delete(LinkList L)
{
	int n,len;
	LinkList t1,t2;
	printf("请输入删除图书位置：");
	scanf("%d",&n);
	len=Length(L);
	if(n<1||n>len)
	{ 
		printf("删除位置非法！\n");
		return L;
	} 
	t1=L;
	
	for(int i=2;i<n;i++)
	{
		t1=t1->next;
	}
	if(n==1)
	{
		L=L->next;
		free(t1);
		return L;
	}
	t2=t1->next;
	t1->next=t2->next;
	free(t2);
	printf("删除成功！\n");
	
	return L;
}

//去重 
LinkList Delete_re(LinkList L)
{
	LinkList t1,t2,t3;
	t1=L;
	
	while(t1)
	{
		t2=t1->next;
		t3=t1;
		while(t2)
		{
			if(strcmp(t1->bookdata.name,t2->bookdata.name)==0)
			{
				LinkList t=t2;
				t2=t2->next;
				t3->next=t2;
				free(t);
			}
			else
				{
					t2=t2->next;
					t3=t3->next;
				}
		}
		t1=t1->next;
	}
	printf("去重成功！\n");
	return L;
}






