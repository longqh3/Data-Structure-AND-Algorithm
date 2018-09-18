//最大和前面有一段是0 仍报错 

/*求出最大子列和与相应对应的子列首位数字+末位数字*/ 
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int K;
	scanf("%d",&K);
	int list[K];
	for(int i=0;i<K;i++){
		int x;
		scanf("%d",&x);
		list[i]=x;
	}
	int left,right,maxleft,maxright;
	int nowsum=0;
	int maxsum=0;
	int cnt=0;
	if(K==1){
		maxsum=maxleft=right=list[0];
		printf("%d %d %d",maxsum,maxleft,right);
		return 0;
	}
	for(int i=0;i<K;i++){
		nowsum+=list[i];
		if(nowsum==0){
			left=list[i];
		}
		if(nowsum<0){
			nowsum=0;
			left=list[i+1];
			cnt++;
		}
		if(nowsum>maxsum){
			maxsum=nowsum;
			right=list[i];
			maxleft=left;
		}
	}
	if(cnt==K){
		maxsum=0;
		maxleft=list[0];
		right=list[K-1];
		printf("%d %d %d",maxsum,maxleft,right);
		return 0;
	}
	if(maxsum==0){
		maxsum=maxleft=right=0;
		printf("%d %d %d",maxsum,maxleft,right);
		return 0;
	}
	printf("%d %d %d",maxsum,maxleft,right);
	return 0;
}
