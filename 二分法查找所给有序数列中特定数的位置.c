/*伪码如下所示
int binarySplit(int list[],int x,int n)
{
初始条件：整数序列list存在
操作结果：若有List[i]=X，则返回i；否则返回-1表示没有找到	
}*/
#include <stdio.h>
int binarySplit(int list[],int x,int n);

int main()
{
	int a[100];
	printf("请输入相应的有序正整数组成数组，以0代表结束：");
	int t,n=0;										//给定相应的数组元素并确定元素个数 
	do{
		scanf("%d",&t);
		if(t){
			a[n]=t;
			n++;
		}
	}while(t);
	int x;
	printf("\n请输入需要查找的正整数x：");
	scanf("%d",&x);
	int i;
	i=binarySplit(a,x,n-1);
	printf("查找元素位置为%d",i); 
}

int binarySplit(int list[],int x,int n)
{
	int res=-1;
	int a=0,b=n;
	int low=list[a],high=list[b],mid=list[(a+b)/2];
	while(low<=high){
		if(x==mid){
			res=(a+b)/2;
			return res;
		}else if(x>mid){
			a=(a+b)/2;
			mid=list[(a+b)/2];
		}else{
			b=(a+b)/2;
			mid=list[(a+b)/2];
		}
	}
	return res;
}