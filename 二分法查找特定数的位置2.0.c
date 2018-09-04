//发现存在很多问题，如对于位于奇数数列中间的数则无法返回位置，在随后的函数中予以修正...真的很迷，原来还有这种思路...

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


/*L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且题目保证传入的数据是递增有序的。
函数BinarySearch要查找X在Data中的位置，即数组下标（注意：元素从下标1开始存储）。找到则返回下标，否则返回一个特殊的失败标记NotFound。*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}
/* 你的代码将被嵌在这里 */
Position BinarySearch( List L, ElementType X )
{
	int res=0;
	int mid;
	int a=1,b=L->Last;
	while(a<=b){
		mid = (a+b)/2;
		if(X==L->Data[mid]){
			res=mid;
			return res;
		}else if(X>L->Data[mid]){
			a=mid+1;				//注意此时mid对应的数组值肯定不会是X的值，所以需要向上增加，即+1
		}else{
			b=mid-1;				//注意此时mid对应的数组值肯定不会是X的值，所以需要向下减少，即+1
		}
	}
	return NotFound;
}