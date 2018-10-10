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
Poly MultiPoly2(Poly P1,Poly P2); 

int main()
{
	Poly P1,P2,Ps,Pm;
	P1=ReadPoly();
	P2=ReadPoly();
	Pm=MultiPoly(P1,P2);
	Output(Pm);
	printf("\n");
	Ps=AddPoly(P1,P2);
	Output(Ps);
	return 0;
}

Poly ReadPoly()
{
	int c,e,N;
	Poly P,Rear,t;
	scanf("%d",&N);
	P=(Poly)malloc(sizeof(struct PolyNode));//构建链表头空结点 
	P->Next=NULL;
	Rear=P;//构建尾部节点临时存放数据？是否可以这样理解？或者可以理解成初始化所必须？ 
	for(;N;N--){
		scanf(" %d %d",&c,&e);
		Attach(c,e,&Rear);//将当前项插入多项式尾部(Rear) 
	}
	t=P;P=P->Next;free(t);//删除临时生成的头结点，并将第一项作为头结点(即进行收尾，把表头空结点转移至第一个有数据的结点？) 
	return P; 
} 

void Attach(int c,int e,Poly *pRear)//*pRear为指针的指针 
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
	Poly Ps,Rear,temp;//意义和之前的ReadPoly函数中的Poly P,Rear,t一致
	if(!P1 || !P2) return NULL; 
	int sum;
	Ps=(Poly)malloc(sizeof(struct PolyNode));
	Ps->Next=NULL;
	Rear=Ps;//由front记录结果多项式链表头结点，其实本质上front此时指代的就是rear？或者说要想建立一个新的链表就必须要有Rear的存在以确定位置？而在后面的循环中通过Attach函数中malloc空间给P来实现链表 
	while(P1 && P2){
		switch(Compare(P1->expo,P2->expo)){
			case 1:
				Attach(P1->coef,P1->expo,&Rear);
				P1=P1->Next;
				break;
			case -1:
				Attach(P2->coef,P2->expo,&Rear);
				P2=P2->Next;
				break;
			case 0:
				sum = P1->coef+P2->coef;
				if(sum){
					Attach(sum,P1->expo,&Rear);
				}
				P1=P1->Next;
				P2=P2->Next;
				break;
		}
	}
	//将未处理完的另一个多项式的所有结点一次复制到结果多项式中去，其本质只是通过循环来实现数据的转移 
	for(;P1;P1=P1->Next){
		Attach(P1->coef,P1->expo,&Rear);
	}
	for(;P2;P2=P2->Next){
		Attach(P2->coef,P2->expo,&Rear);
	}
	Rear->Next=NULL;
	temp=Ps;
	Ps=Ps->Next;
	free(temp);
	return Ps;
}

int Compare(int a,int b)
{
	if(a>b){
		return 1;
	}
	if(a<b){
		return -1;
	}
	if(a=b){
		return 0;
	}
}

Poly MultiPoly(Poly P1,Poly P2)
{
	Poly Pm,Rear,Rear2,temp,temp2,P,t1,t2;
	if(!P1 || !P2) return NULL;
	t2=P2;
	Pm=(Poly)malloc(sizeof(struct PolyNode));
	Pm->Next=NULL;
	Rear=Pm;
	for(;t2;t2=t2->Next){
		Attach(P1->coef*t2->coef,P1->expo+t2->expo,&Rear);
	}
	P1=P1->Next;temp=Pm;Pm=Pm->Next;free(temp);//得到第一个Pm
	while(P1){
		P=(Poly)malloc(sizeof(struct PolyNode));
		P->Next=NULL;
		Rear2=P;
		t2=P2;
		while(t2){
			Attach(P1->coef*t2->coef,P1->expo+t2->expo,&Rear2);
			t2=t2->Next;
		}
		temp2=P;P=P->Next;free(temp2);
		Pm=AddPoly(Pm,P);
		P1=P1->Next;
	}
	return Pm;
}

Poly MultiPoly2(Poly P1,Poly P2)
{
	if(!P1 || !P2) return NULL;
	Poly Pm,Rear,temp,t1,t2,Rear2,t;
	t1=P1;t2=P2;
	Pm=(Poly)malloc(sizeof(struct PolyNode));
	Rear=Pm;
	Pm->Next=NULL;
	for(;t2;t2=t2->Next){
		Attach(t1->coef*t2->coef,t1->expo+t2->expo,&Rear);
	}
	t1=t1->Next;
	int c,e,sum;
	for(;t1;t1=t1->Next){
		t2=P2;Rear2=Pm;
		for(;t2;t2=t2->Next){
			c=t1->coef*t2->coef;
			e=t1->expo+t2->expo;
			while(Rear2->Next&&Rear2->Next->expo>e) Rear2=Rear2->Next;
			if(Rear2->Next&&Rear2->Next->expo==e){
				if(Rear2->Next->coef+c){
					Rear2->Next->coef+=c;
				}else{
					t=Rear2->Next;
					Rear2->Next=t->Next;
					free(t);
				}
			}else{
				t=(Poly)malloc(sizeof(struct PolyNode));
				t->coef=c;
				t->expo=e;
				t->Next=Rear2->Next;
				Rear2->Next=t;
				Rear2->Next=Rear2;//不知道何用意 
			}
		}
	}
	temp=Pm;Pm=Pm->Next;free(temp);
	return Pm;
}

void Output(Poly P)
{
	int flag=0;
	while(P){
		if(!flag){
			printf("%d %d",P->coef,P->expo);
		}if(flag){
			printf(" %d %d",P->coef,P->expo);
		}
		P=P->Next;
		flag++;
	}
}
