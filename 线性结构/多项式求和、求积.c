#include <stdio.h>

typedef struct PolyNode *Poly;
typedef int ElementType; 
struct PolyNode{
	ElementType coef;
	ElementType expo;
	Poly Next;
};

Poly ReadPoly();
Poly AddPoly(Poly P1,Poly P2);
Poly MultiPoly(Poly P1,Poly P2);
void Output(Poly P);
void Attach(int c,int e,Poly *pRear);
int Compare(int p1,int p2);

int main()
{
	Poly P1,P2,Ps,Pm;
	P1=ReadPoly();
	P2=ReadPoly();
	Ps=AddPoly(P1,P2);
	Output(Ps);
	Pm=MultiPoly(P1,P2);
	Output(Pm);
	return 0;
}

Poly ReadPoly()
{
	int c,e,N;
	Poly P,Rear,t;
	scanf("%d",&N);
	P=(Poly)malloc(sizeof(struct PolyNode));//构建链表头空结点 
	P->Next=NULL;
	Rear=P;//构建尾部节点临时存放数据？是否可以这样理解？ 
	while(N--){
		scanf(" %d %d",&c,&e);
		Attach(c,e,&Rear);//将当前项插入多项式尾部 
	}
	t=P;P=P->Next;free(t);//删除临时生成的头结点，并将第一箱作为头结点
	return P; 
} 

void Attach(int c,int e,Poly *pRear)
{
	Poly P;
	
	P=(Poly)malloc(sizeof(struct PolyNode));
	P->coef=c;
	P->expo=e;
	P->Next=NULL;
	(*pRear)->Next=P;
	*pRear=P;//修改pRear值，其实就是把此时的rear修改成P，便于接下来的计算 
}

Poly AddPoly(Poly P1,Poly P2)
{
	Poly front,rear,temp;
	int sum;
	rear=(Poly)malloc(sizeof(struct PolyNode));
	front=rear;//由front记录结果多项式链表头结点，其实本质上front此时指代的就是rear？而在后面的循环中通过Attach函数中malloc空间给P来实现链表 
	while(P1 && P2){
		switch(Compare(P1->expo,P2->expo)){
			case 1:
				Attach(P1->coef,P1->expo,&rear);
				P1=P1->Next;
				break;
			case -1:
				Attach(P2->coef,P2->expo,&rear);
				P2=P2->Next;
				break;
			case 0:
				sum = P1->coef+P2->coef;
				if(sum)Attach(sum,P1->expo,&rear);
				P1=P1->Next;
				P2=P2->Next;
				break;
		}
	}
	//将未处理完的另一个多项式的所有结点一次复制到结果多项式中去
	for(;P1;P1=P1->Next)Attach(P1->coef,P1->expo,&rear);
	for(;P2;P2=P2->Next)Attach(P2->coef,P2->expo,&rear);
	rear->Next=NULL;
	temp=front;
	front=front->Next;
	free(temp);
	return front;
}

int Compare(int p1,int p2)
{
	if(p1>p2) return 1;
	if(p1=p2) return 0;
	if(p1<p2) return -1;
}

Poly MultiPoly(Poly P1,Poly P2)
{
	Poly Pm,rear,t1,t2,temp,P;
	t1=P1;t2=P2;
	Pm = (Poly)malloc(sizeof(struct PolyNode));
	Pm->Next=NULL;
	rear=Pm;
	Attach(t1->coef*t2->coef,t1->expo+t2->expo,&rear);
	t2=t2->Next;
	rear->Next=NULL;
	temp=Pm; Pm=Pm->Next; free(temp);
	while(t2){
		P = (Poly)malloc(sizeof(struct PolyNode));
		P->Next=NULL;
		rear=P;
		Attach(t1->coef*t2->coef,t1->expo+t2->expo,&rear);
		t2=t2->Next;
		rear->Next=NULL;
		temp=P; P=P->Next; free(temp);
		Pm=AddPoly(P,Pm);
	}	
	return Pm;
}

void Output(Poly P)
{
	int flag=0;
	for(;P;P=P->Next){
		if(!flag){
			printf("%d %d",P->coef,P->expo);
		}if(flag){
			printf(" %d %d\n",P->coef,P->expo);
		}
	}
}
