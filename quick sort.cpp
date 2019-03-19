#include<stdio.h>
#define N 10000
int L[N+1]={};
void swap(int &a,int &b){
	int t;
	t=a;
	a=b;
	b=t;
}
int Partition(int low,int high){
	int pivotkey=L[low];
	int i=low,j=high;
	L[0]=L[low];
    while(i<j){
    	while(j>i&&L[j]>=pivotkey) j--;
        L[i]=L[j];
        while(i<j&&L[i]<=pivotkey) i++;
        L[j]=L[i];
    }
    L[i]=L[0];
    return  i;
}
void QuiSort(int i,int j){
	int k;
	if(i<j){
		printf("%d %d\n",i,j);
		k=Partition(i,j);
		QuiSort(i,k-1);
		QuiSort(k+1,j);
	}
}
int main(){
	int n,i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&L[i]);
	QuiSort(1,n);
	for(i=1;i<=n;i++) printf("%d ",L[i]);
	return 0;
}
