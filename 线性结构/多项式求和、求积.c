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
	P=(Poly)malloc(sizeof(struct PolyNode));//��������ͷ�ս�� 
	P->Next=NULL;
	Rear=P;//����β���ڵ���ʱ������ݣ��Ƿ����������⣿���߿������ɳ�ʼ�������룿 
	for(;N;N--){
		scanf(" %d %d",&c,&e);
		Attach(c,e,&Rear);//����ǰ��������ʽβ��(Rear) 
	}
	t=P;P=P->Next;free(t);//ɾ����ʱ���ɵ�ͷ��㣬������һ����Ϊͷ���(��������β���ѱ�ͷ�ս��ת������һ�������ݵĽ�㣿) 
	return P; 
} 

void Attach(int c,int e,Poly *pRear)//*pRearΪָ���ָ�� 
{
	Poly P;
	
	P=(Poly)malloc(sizeof(struct PolyNode));
	P->coef=c;
	P->expo=e;
	P->Next=NULL;
	(*pRear)->Next=P;
	*pRear=P;//�޸�pRearֵ����ʵ���ǰѴ�ʱ��rear�޸ĳ�P�����ڽ������ļ��� 
}

Poly AddPoly(Poly P1,Poly P2)
{
	Poly Ps,Rear,temp;//�����֮ǰ��ReadPoly�����е�Poly P,Rear,tһ�� 
	int sum;
	Ps=(Poly)malloc(sizeof(struct PolyNode));
	Ps->Next=NULL;
	Rear=Ps;//��front��¼�������ʽ����ͷ��㣬��ʵ������front��ʱָ���ľ���rear������˵Ҫ�뽨��һ���µ�����ͱ���Ҫ��Rear�Ĵ�����ȷ��λ�ã����ں����ѭ����ͨ��Attach������malloc�ռ��P��ʵ������ 
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
	//��δ���������һ������ʽ�����н��һ�θ��Ƶ��������ʽ��ȥ���䱾��ֻ��ͨ��ѭ����ʵ�����ݵ�ת�� 
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
	t2=P2;
	Pm=(Poly)malloc(sizeof(struct PolyNode));
	Pm->Next=NULL;
	Rear=Pm;
	for(;t2;t2=t2->Next){
		Attach(P1->coef*t2->coef,P1->expo+t2->expo,&Rear);
	}
	P1=P1->Next;temp=Pm;Pm=Pm->Next;free(temp);//�õ���һ��Pm
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
