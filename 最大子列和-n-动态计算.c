/*给定K个整数组成的序列{ N​1​​, N​2​​, ..., N​K​​ }，“连续子列”被定义为{ N​i​​, N​i+1​​, ..., N​j​​ }，其中 1≤i≤j≤K。
“最大子列和”则被定义为所有连续子列元素的和中最大者。
例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。
现要求你编写程序，计算给定整数序列的最大子列和。 */

/*L是用户传入的一个线性表，其中ElementType元素可以通过>、==、<进行比较，并且题目保证传入的数据是递增有序的。
函数BinarySearch要查找X在Data中的位置，即数组下标（注意：元素从下标1开始存储）。找到则返回下标，否则返回一个特殊的失败标记NotFound。*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100000
typedef int ElementType;
typedef int Sum;
typedef struct LNode List;

struct LNode {
    ElementType Data[MAXSIZE];
    Sum sum; /* 记录传入的数据总数 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */

int main()
{
    List L;
    ElementType X;
    L = ReadInput();
    int subsum=0;
    int tempsum=0;
	for(int i=0;i<L.sum;i++){
		//printf("%d ",L.Data[i]);
		tempsum+=L.Data[i];
		if(tempsum>subsum){
			subsum=tempsum;
		}else if(tempsum<0){
			tempsum=0;
		}
	}
	printf("%d",subsum);
    return 0;
}

List ReadInput()
{
	int k;
	List L;
	scanf("%d",&k);
	L.sum=k;
	int x;
	for(int i=0;i<k;i++){
		scanf("%d",&x);
		L.Data[i]=x;
	}
	return L;
}