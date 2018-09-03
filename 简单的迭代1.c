#include <stdio.h>

void printN(int n);
int main()
{
	int n;
	scanf("%d",&n);
	printN(n);
	return 0;
}

void printN(int n)
{
	if(n){
		printN(n-1);
		printf("%d ",n);
	}
}