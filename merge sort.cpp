#include<stdio.h>
#define N 50000
int L[N+1]={};
int Rt[N+1]={};
int count=0;
void Merge(int s,int m,int t){
	int i,j,k;
	for(i=s,j=m+1,k=i;i<=m&&j<=t;k++){
		if(L[i]<=L[j]) Rt[k]=L[i++];
		else {Rt[k]=L[j++];count+=(m-i+1);}
	}
	for(;i<=m;) Rt[k++]=L[i++];
	for(;j<=t;) Rt[k++]=L[j++];
	for(i=s;i<=t;i++) L[i]=Rt[i];
}
void MergeSort(int s,int t){
	int m;
	if(s==t) {Rt[s]=L[s];return;}
    m=(s+t)/2;
    MergeSort(s,m);
    MergeSort(m+1,t);
    Merge(s,m,t);
}
int main(){
	int n,i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&L[i]);
	MergeSort(1,n);
	for(i=1;i<=n;i++) printf("%d ",Rt[i]);
	printf("\n%d",count);
	return 0;
}
