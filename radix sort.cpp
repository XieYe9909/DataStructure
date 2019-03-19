#include<stdio.h>
#define N 10001
#define Ra 16
#define D 4
typedef struct{
    int keys[D+1];
}RcdType;
RcdType L[N];
void RadPass(RcdType R[],RcdType T[],int n,int k){
    int i,j,p;
    int count[Ra]={0};
    for(j=1;j<=n;j++) count[R[j].keys[k]]++;
	for(j=1;j<Ra;j++) count[j]=count[j-1]+count[j];
	for(j=n;j>=1;j--){
		p=R[j].keys[k];
		T[count[p]]=R[j];
		count[p]--;
	}
	for(i=1;i<=n;i++) printf("%d ",T[i].keys[D]);
	printf("\n");
}
void RadSort(int len){
    RcdType T[N];
    int i,j,k=D-1;
    while(k>=0){
		RadPass(L,T,len,k);
		k--;
		if(k>=0){
			RadPass(T,L,len,k);
			k--;
		}
		else for(j=1;j<=len;j++) L[j]=T[j];
	}
}
int main(){ 
    int i,j,n,m;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",&L[i].keys[D]);
    for(i=1;i<=n;i++){
        m=L[i].keys[D];
        for(j=D-1;j>=0;j--){
            L[i].keys[j]=m%Ra;
            m/=Ra;
        }
    }
    RadSort(n);
    for(i=1;i<=n;i++) printf("%d ",L[i].keys[D]);
    return 0;
} 
