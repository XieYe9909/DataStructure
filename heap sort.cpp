#include<stdio.h>
#define N 10000
int L[N+1]={};
void swap(int &a,int &b){
	int t;
	t=a;
	a=b;
	b=t;
}
void HeapAdjust(int s,int t){
	int w,i;
	w=L[s];
	for(i=2*s;i<=t;i*=2){
		if(i<t) i=(L[i]>=L[i+1])?i:i+1;
		if(w>=L[i]) break;
		L[s]=L[i];
		s=i;
	}
	L[s]=w;
}
void HeapSort(int len,int m){
	int i,j;
	for(i=len/2;i>=1;i--) HeapAdjust(i,len);
	for(i=1;i<=len;i++) printf("%d ",L[i]);
	printf("\n");
	for(i=len;i>1;i--){
		swap(L[1],L[i]);
		HeapAdjust(1,i-1);
		if(i-1==m){
			for(j=1;j<=len;j++) printf("%d ",L[j]);
			printf("\n");
		}
	}
}
int main(){
	int i,n,m;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&L[i]);
	HeapSort(n,m);
	for(i=1;i<=n;i++) printf("%d ",L[i]);
	return 0;
}
