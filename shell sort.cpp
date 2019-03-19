#include<stdio.h>
#include<stdlib.h>
#define N 10000
int r[N]={};
int incr[1000]={};
void ShlInsert(int len,int incr){
	int i,j;
	for(i=incr+1;i<=len;i++)
	   if(r[i]<r[i-incr]){
		   r[0]=r[i];
		   for(j=i-incr;j>0&&r[0]<r[j];j-=incr) r[j+incr]=r[j];
		   r[j+incr]=r[0];
		}
}
void ShlSort(int len,int m){
	int i,j;
	for(i=0;i<m;i++) {
		ShlInsert(len,incr[i]);
		for(j=1;j<=len;j++) printf("%d ",r[j]);
		printf("\n");
	}
}
int main(){
	int n,m,i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&r[i]);
	for(i=0;i<m;i++) scanf("%d",&incr[i]);
	ShlSort(n,m);
	return 0; 
}
