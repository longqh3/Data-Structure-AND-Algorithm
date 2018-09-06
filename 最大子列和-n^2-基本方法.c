#include <stdio.h>

int main()
{
	int k,x;
	scanf("%d",&k);
	int l[k];
	for(int i=0;i<k;i++){
		scanf("%d",&x);
		l[i]=x;
	}
	int maxsum=0;
	for(int i=0;i<k;i++){
		int tempsum=0;
		for(int j=i;j<k;j++){
			tempsum+=l[j];
			if(tempsum>maxsum){
				maxsum = tempsum;
			}
		}
	}
	printf("%d",maxsum);
	return 0;
}