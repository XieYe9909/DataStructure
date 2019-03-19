#include<stdio.h>
#define M 4096
#define T 0xffffffff
int i;
int m1=0,m2=0,n1=0,n2=0;
unsigned HT[M]={};
unsigned hash(unsigned x){
    return (long long)x*x>>26&0xFFF;
}
unsigned h(unsigned x){
	if(x%2) return x%M;
    else return (x+1)%M;
}
unsigned insert(unsigned x){
    i=1;
    unsigned a=hash(x);
    while(HT[a]&&HT[a]!=T) {
        a=(a+h(x))%M;
        i++;
    }
    HT[a]=x;
    return a;
}
unsigned search(unsigned x){
    i=1;
    int flag=1;
    unsigned a=hash(x);
    while(HT[a]!=0){
        if(HT[a]==x){
			flag=0;
			HT[a]=T;
			m1+=i;
			n1++;
			break;
		}
        a=(a+h(x))%M;
        i++;
    }
    if(flag){
		m2+=i;
		n2++;
		return T;
	}
    else return a;
}
int main(){
	unsigned a,m;
	int k,b;
	for(k=0;k<10000;k++){
		scanf("%u%d",&a,&b);
		if(b==1){
			m=insert(a);
			printf("%d %d\n",i,m);
		}
		else{
			m=search(a);
			printf("%d %d\n",i,m);
		}
	}
	printf("%d/%d\n",m1,n1);
	printf("%d/%d",m2,n2);
}
