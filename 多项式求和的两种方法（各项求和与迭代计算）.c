#include <stdio.h>
#include <math.h>
#include <time.h>
clock_t start1,end1,start2,end2;
double time1,time2;
#define MAXN 100
double poly1(double x,double a[]);
double poly2(double x,double a[]);
int main()
{
	double x;
	scanf("%lf",&x);
	double a[MAXN];//将系数存入相应数组，避免即时运算的困扰 
	for(int i=1;i<=MAXN;i++){
		a[i] = 1/i;
	} 
	double p1,p2;
		start1=clock();
	for(int i=1000;i>0;i--){
		p1=poly1(x,a);
	}
		end1=clock();
	printf("%lf\n",p1);
		start2=clock();
	for(int i=1000;i>0;i--){
		p2=poly2(x,a);
	}
		end2=clock();
	printf("%lf\n",p2);
	
	time1=(double)(end1-start1)/CLK_TCK;
	time2=(double)(end2-start2)/CLK_TCK;
	printf("所经过的ticks=%f\n",(double)(end1-start1)); 
	printf("第一种方法所需时间为%6.3es，第二种方法所需时间为%6.3es",time1,time2);
	return 0;
}

double poly1(double x,double a[])
{
	double p1=1.0;
	int n;
	for(n=1;n<=MAXN;n++){
		p1+=a[n]*pow(x,n);
	} 
	return p1;
}

double poly2(double x,double a[])
{
	int n=MAXN;
	double p2=a[n];
	for(n;n>1;n--){
		p2=a[n-1]+x*p2;
	}
	p2 = 1+x*p2;
	return p2;
}