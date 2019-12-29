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

//初始化
List MakeEmptry();
//遍历
void Print(List L);
//排序
List sorting(List L);
//插入
List Insert(List L,int num,char* name,double pri);
//按位删除
List Delete(List L,int x);
//取长度
void Length(List L);

//修改价格 
void adjust_price(List L);
//逆序
void inverse_order(List L); 
//输出最贵 
void Print_therich(List L);
//按名输出
void Print_thefavour(List L);
//按位输出
void Print_thebest(List L); 
//按位插入 
List BitInsert(List L);
//去重 
List Delete_re(List L);

//操作 
List Operation(int n,List L);
//菜单
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
	printf("请选择要进行的操作：\n");
	printf("1.建表并输出\n2.排序\n3.价格信息调整\n4.逆序\n5.输出最贵图书\n");
	printf("6.按名查找\n7.按位查找\n8.新书入库\n9.旧书出库\n10.去除重复图书\n");
	printf("0.退出\n");
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
			printf("请输入删除图书位置：");
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

List MakeEmptry()//创建顺序表储存图书信息，返回顺序表地址
{
    int num,n;
    char name[30];
    double pri;
	List L;
	L=(List)malloc(sizeof(struct LNode));
	L->Last=0;
	printf("请输入入库图书数目：");
	scanf("%d",&n);
	printf("请依次输入各图书信息：\n");
	while(n&&scanf("%d%s%lf",&num,&name,&pri))
    {
        if(num==0&&name[0]=='0'&&pri==0)
            break;
        L=Insert(L,num,name,pri);//调用插入函数 
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
		printf("表满！");
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


//排序 
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

//调高价格 
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
	printf("原平均价格为：");
	printf("%.2lf\n",average);
}

//逆序 
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

//输出最贵 
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
	printf("最贵图书数目为：");
	printf("%d\n",k);
	for(i=0;i<=L->Last-1;i++)
	{
		if(L->bookdate[i].pri==therich)
		printf("%d %s %.2lf\n",L->bookdate[i].num,L->bookdate[i].name,L->bookdate[i].pri);
	}
	putchar('\n');
	putchar('\n');
}

//按名输出
void Print_thefavour(List L)
{
	int i,n;
	char thefavour[30];
	printf("请输入要找的书本数目：");
	scanf("%d",&n);
	while(n--)
	{
		printf("请输入要找的图书名字：\n");
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
			printf("抱歉，没有你的最爱！\n");
			putchar('\n');
		} 
	}
	putchar('\n');
	putchar('\n');
}

//按位输出
void Print_thebest(List L)
{
	int i,n,m;
	printf("请输入要找的书本数目：");
	scanf("%d",&n);
	while(n--)
	{
		printf("请输入要找图书的位置：");
		scanf("%d",&m);
		if(m>=L->Last||m<1)
		{	printf("抱歉，此位置上的图书不存在！\n");
			putchar('\n');
		} 
		else 
			printf("%d %s %.2lf\n",L->bookdate[m-1].num,L->bookdate[m-1].name,L->bookdate[m-1].pri);
	}
	putchar('\n');
}

//按位插入 
List BitInsert(List L)
{
	int n;
    int num;
    char name[30];
    double pri;
    if(L->Last==MAXSIDE-1)
    {
    	printf("表满！");
    	putchar('\n');
		return L;
	}
	printf("请输入插入位置：");
	scanf("%d",&n);
	if(n<=0||n>L->Last+1)
	{ 
		printf("插入位置非法！\n"); 
		putchar('\n');
		return L;
	}
	printf("请输入插入图书信息：\n");
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
	printf("入库成功！");
	putchar('\n');
	return L;
}

//按位删除 
List Delete(List L,int x)
{
	if(L->Last<x||x<=0)
	{
		printf("删除位置非法！\n");
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

//去重 
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
	Printf(“去重成功！\n”);
	return L;
}


