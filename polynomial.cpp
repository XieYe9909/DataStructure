#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define N 10 
typedef struct Polynomial{
	float coef;
	int expn;
	struct Polynomial *next;
}Polynomial,*Polyn;
Polyn P[N]={NULL};
Polyn MakeNode(float coef,int expn){
	Polyn p=(Polyn)malloc(sizeof(Polynomial));
	p->coef=coef;
	p->expn=expn;
	p->next=NULL;
	return p;
}
void Insert(Polyn L,Polyn s){
	Polyn p,q;
	p=L;
	while(p->next&&p->next->expn>=s->expn) p=p->next;
	if(p->expn==s->expn){
		p->coef+=s->coef;
		free(s);
	}
	else if(!p->next)	p->next=s;
	else{
		s->next=p->next;
		p->next=s;
	}
	p=L;
	while(p){
		if(fabs(p->coef)>1e-8){
			q=p;
			p=p->next;  
		}
		else{
			q->next=p->next;
			free(p);
			p=q->next;
		}              
	}
}
void Print(Polyn L){
	Polyn p;
	float c=0;
	if(!L) printf("NULL");
	else if(!L->next) printf("%.4f",c);
	else{
		p=L->next;
		while(p){
			switch(p->expn){
				case 0:printf("%.4f",p->coef);break;
				case 1:printf("%.4fx",p->coef);break;
		    	default:printf("%.4lfx^%d",p->coef,p->expn);break;
			}
			if(p->next&&p->next->coef>1e-8) printf("+");
		p=p->next;
		}
	}
	printf("\n");
}
void Create(Polyn &L){
	Polyn p;
	float c;
	int e;
	L=MakeNode(-1,-1);
	printf("Input coef and expn:(coef=0:exit)");
	while(1){
		scanf("%f%d",&c,&e);
		if(c==0) break;
		p=MakeNode(c,e);
		Insert(L,p);
	}
}
void Copy(Polyn L1,Polyn &L2){
	L2=MakeNode(-1,-1);
	Polyn p,q;
	p=L1->next;q=L2;
	while(p){
		q->next=MakeNode(p->coef,p->expn);
		q=q->next;
		p=p->next;
	}
}
void Add(Polyn L1,Polyn L2,Polyn &L3){
	L3=MakeNode(-1,-1);
	Polyn p,q,s;
	p=L1->next;q=L2->next;s=L3;
	while(p&&q){
		if(p->expn>q->expn){
			s->next=MakeNode(p->coef,p->expn);
			p=p->next;
			s=s->next;
		}
		else if(p->expn<q->expn){
			s->next=MakeNode(q->coef,q->expn);
			q=q->next;
			s=s->next;
		}
		else{
			if(p->coef+q->coef==0){
				p=p->next;
				q=q->next;
			}
			else{
				s->next=MakeNode(p->coef+q->coef,p->expn);
				p=p->next;
				q=q->next;
				s=s->next;
			}
		}
	}
	if(p){
		while(p){
			s->next=MakeNode(p->coef,p->expn);
			p=p->next;
			s=s->next;
		}
	}
	if(q){
		while(q){
			s->next=MakeNode(q->coef,q->expn);
			q=q->next;
			s=s->next;
		}
	}
}
void Sub(Polyn L1,Polyn L2,Polyn &L3){
	Polyn p=L2->next;
	while(p){
		p->coef*=-1;
		p=p->next;
	}
	Add(L1,L2,L3);
	p=L2->next;
	while(p){
		p->coef*=-1;
		p=p->next;
	}
}
float Value(Polyn L,float x){
	float sum=0;
	Polyn p=L->next;
	while(p){
		sum+=p->coef*pow(x,p->expn);
		p=p->next;
	}
	return sum;
}
void Destroy(Polyn &L){
	Polyn p=L,q;
	while(p){
		q=p;
		p=p->next;
		free(q);
	}
	L=NULL;
}
void Empty(Polyn &L){
	if(L->next) Destroy(L->next);
}
void Modify(Polyn &L,int t){
	float A;int K,flag=1;
	Polyn p,q;
	switch(t){
		case 1:printf("Input A and K:");
		       scanf("%f%d",&A,&K);
		       p=MakeNode(A,K);
		       Insert(L,p);
		       break;
		case 2:printf("Input K:");
		       scanf("%d",&K);
		       p=L->next;
		       q=L;
		       while(p){
		       	   if(p->expn==K){
		       	   	  q->next=p->next;
		       	   	  free(p);
		       	   	  flag=0;
		       	   	  break;
		       	   }
		       	   else {
		       	   	  q=p;
		       	   	  p=p->next;
		       	   }
		       }
		       if(flag==1) printf("Not Found\n");
		       break;
		case 3:printf("Input A and K:");
		       scanf("%f%d",&A,&K);
		       p=L->next;
		       q=L;
		       while(p){
		       	   if(p->expn==K){
		       	   	  p->coef=A;
		       	   	  if(fabs(A)<1e-8){
		       	   	  		q->next=p->next;
		       	   	  		free(p);
		       	   	  }
		       	   	  flag=0;
		       	   	  break;
		       	   }
		       	   else{
		       	   	  q=p;
		       	   	  p=p->next;
		       	   }
		       }
		       if(flag==1) printf("Not Found\n");
		       break;
		default:printf("FALSE\n");break;
	}
}
void Differential(Polyn L1,Polyn &L2){
	L2=MakeNode(-1,-1);
	Polyn p=L1->next,q=L2;
	while(p){
		if(p->expn==0) p=p->next;
		else{
			q->next=MakeNode(p->coef*p->expn,p->expn-1);
			p=p->next;
			q=q->next;
		}
	}
}
void In_integral(Polyn L1,Polyn &L2){
	L2=MakeNode(-1,-1);
	Polyn p=L1->next,q=L2;
	while(p){
		q->next=MakeNode(p->coef/(p->expn+1),p->expn+1);
		p=p->next;
		q=q->next;
	}
}
float De_integral(Polyn L,float x1,float x2){
	Polyn temp;
	float t;
	In_integral(L,temp);
	t=Value(temp,x2)-Value(temp,x1);
	Destroy(temp);
	return t;
}
void Multiply(Polyn L1,Polyn L2,Polyn &L3){
	L3=MakeNode(-1,-1);
	Polyn p=L1->next,q=L2->next,s;
	while(p){
		while(q){
			s=MakeNode(p->coef*q->coef,p->expn+q->expn);
			Insert(L3,s);
			q=q->next;
		}
		p=p->next;
		q=L2->next;
	}
}
void Divide(Polyn L1,Polyn L2,Polyn &L3){
	Polyn temp=MakeNode(-1,-1);
	Polyn temp1,temp2,temp3;
	Copy(L1,temp1);
	L3=MakeNode(-1,-1);
	Polyn p=temp1->next,q=L2->next,s;
	while(p&&p->expn>=q->expn){
		s=MakeNode(p->coef/q->coef,p->expn-q->expn);
		Insert(L3,s);
		temp->next=MakeNode(p->coef/q->coef,p->expn-q->expn);;
		Multiply(L2,temp,temp2);
		Empty(temp);
		Sub(temp1,temp2,temp3);
		Destroy(temp1);
		Destroy(temp2);
		Copy(temp3,temp1);
		Destroy(temp3);
		p=temp1->next;
	}
}
void Mod(Polyn L1,Polyn L2,Polyn &L3){
	Polyn temp1,temp2;
	Divide(L1,L2,temp1);
	Multiply(L2,temp1,temp2);
	Sub(L1,temp2,L3);
	Destroy(temp1);
	Destroy(temp2); 
}
void Power(Polyn L1,Polyn &L2,int x){
	Polyn temp1=MakeNode(-1,-1),temp2,temp3; 
	temp1->next=MakeNode(1,0);
	Copy(L1,temp2);;
    while(x!=0){
    if(x%2){
    	Multiply(temp1,temp2,temp3);
    	Destroy(temp1);
    	Copy(temp3,temp1);
    	Destroy(temp3);
    }
    Multiply(temp2,temp2,temp3);
    Destroy(temp2);
    Copy(temp3,temp2);
    Destroy(temp3);
    x/=2;
    }
    Copy(temp1,L2);
    Destroy(temp1);
}
void Gcd(Polyn L1,Polyn L2,Polyn &L3){
	Polyn temp1,temp2,temp3,p;
	float c;
	Copy(L1,temp1);
	Copy(L2,temp2);
	Mod(temp1,temp2,temp3);
	while(temp3->next){
		Destroy(temp1);
		Copy(temp2,temp1);
		Destroy(temp2);
		Copy(temp3,temp2);
		Destroy(temp3);
		Mod(temp1,temp2,temp3);
	}
	p=temp2->next;
	c=p->coef;
	while(p){
		p->coef/=c;
		p=p->next;
	}
	Copy(temp2,L3);
	Destroy(temp1);
	Destroy(temp2);
	Destroy(temp3);
}
void Lcm(Polyn L1,Polyn L2,Polyn &L3){
	Polyn temp1,temp2;
	Multiply(L1,L2,temp1);
	Gcd(L1,L2,temp2);
	Divide(temp1,temp2,L3);
}
int main(){
	int n,i,i1,i2,j1,j2,j3,t,menu;
	float x,x1,x2;
    printf("-------------------Menu-----------------\n");
    printf("0 --- 退出\n");
    printf("1 --- 创建\n");
    printf("2 --- 显示\n");
    printf("3 --- 复制\n");
    printf("4 --- 求和\n");
    printf("5 --- 求差\n");
    printf("6 --- 求值\n");
    printf("7 --- 销毁\n");
	printf("8 --- 清空\n");
    printf("9 --- 修改\n");
    printf("10 --- 求导\n");
    printf("11 --- 不定积分\n");
    printf("12 --- 定积分\n");
    printf("13 --- 求积\n");
    printf("14 --- 求商\n");
    printf("15 --- 求余\n");
    printf("16 --- 乘方\n");
    printf("17 --- 最大公约式\n");
    printf("18 --- 最小公倍式\n");
    while(1){
        printf("----------------------------------------\n");
		printf("Please choose(0~18):");
        scanf("%d",&menu);
        printf("----------------------------------------\n");
        switch(menu){
        	case 0:return 0;//退出
        	case 1:printf("Input number(0~9):");
        		   scanf("%d",&n);
        		   if(n<0||n>9) printf("FALSE\n");
        		   else Create(P[n]);
        		   break;//创建
        	case 2:for(i=0;i<N;i++){ 
        		       printf("P[%d]=",i);
        		       Print(P[i]);
				   }
				   break;//显示 
			case 3:printf("Input number 1 and number 2:");
			       scanf("%d%d",&i1,&i2);
			       if((i1<0||i1>9)||(i2<0||i2>9)||i1==i2||!P[i1]) printf("FALSE\n");
			       else Copy(P[i1],P[i2]);
			       break;//复制
			case 4:printf("Input number 1,number 2 and number 3:");
			       scanf("%d%d%d",&j1,&j2,&j3);
			       if((j1<0||j1>9)||(j2<0||j2>9)||(j3<0||j3>9)||j3==j1||j3==j2||!P[j1]||!P[j2]) printf("FALSE\n");
			       else Add(P[j1],P[j2],P[j3]);
			       break;//求和
			case 5:printf("Input number 1,number 2 and number 3:");
			       scanf("%d%d%d",&j1,&j2,&j3);
			       if((j1<0||j1>9)||(j2<0||j2>9)||(j3<0||j3>9)||j3==j1||j3==j2||!P[j1]||!P[j2]) printf("FALSE\n");
			       else Sub(P[j1],P[j2],P[j3]);
			       break;//求差
			case 6:printf("Input number and x:");
				   scanf("%d%f",&n,&x);
				   if(n<0||n>9||!P[n]) printf("FALSE\n");
				   else printf("value=%.4f\n",Value(P[n],x));
				   break;//求值
			case 7:printf("Input number:");
			       scanf("%d",&n);
			       if(n<0||n>9) printf("FALSE\n");
			       else Destroy(P[n]);
			       break;//销毁
			case 8:printf("Input number:"); 
				   scanf("%d",&n);
			       if(n<0||n>9||!P[n]) printf("False\n");
			       else Empty(P[n]);
			       break;//清空
			case 9:printf("Input number and t:");
			       scanf("%d%d",&n,&t);
			       if(n<0||n>9||!P[n]||t<1||t>3) printf("False\n");
			       else Modify(P[n],t);
			       break;//修改
			case 10:printf("Input number 1 and number 2:");
			        scanf("%d%d",&i1,&i2);
			        if((i1<0||i1>9)||(i2<0||i2>9)||i1==i2||!P[i1]) printf("False\n");
			        else Differential(P[i1],P[i2]);
			        break;//求导
			case 11:printf("Input number 1 and number 2:");
			        scanf("%d%d",&i1,&i2);
			        if((i1<0||i1>9)||(i2<0||i2>9)||i1==i2||!P[i1]) printf("False\n"); 
			        else In_integral(P[i1],P[i2]);
			        break;//不定积分
			case 12:printf("Input number and x1,x2:");
			        scanf("%d%f%f",&n,&x1,&x2);
			        if(n<0||n>9||!P[n]) printf("False\n");
			        else printf("integral=%.4f\n",De_integral(P[n],x1,x2));
			        break;//定积分
			case 13:printf("Input number 1,number 2 and number 3:");
			        scanf("%d%d%d",&j1,&j2,&j3);
			        if((j1<0||j1>9)||(j2<0||j2>9)||(j3<0||j3>9)||j3==j1||j3==j2||!P[j1]||!P[j2]) printf("False\n"); 
			        else Multiply(P[j1],P[j2],P[j3]);
			        break;//求积
			case 14:printf("Input number 1,number 2 and number 3:");
			        scanf("%d%d%d",&j1,&j2,&j3);
			        if((j1<0||j1>9)||(j2<0||j2>9)||(j3<0||j3>9)||j3==j1||j3==j2||!P[j1]||!P[j2]||!P[j2]->next) printf("False\n"); 
			        else Divide(P[j1],P[j2],P[j3]);
			        break;//求商
			case 15:printf("Input number 1,number 2 and number 3:");
			        scanf("%d%d%d",&j1,&j2,&j3);
			        if((j1<0||j1>9)||(j2<0||j2>9)||(j3<0||j3>9)||j3==j1||j3==j2||!P[j1]||!P[j2]||!P[j2]->next) printf("False\n"); 
			        else Mod(P[j1],P[j2],P[j3]);
			        break;//求余
			case 16:printf("Input number 1,number 2 and x:");
			        scanf("%d%d%d",&i1,&i2,&t);
			        if((i1<0||i1>9)||(i2<0||i2>9)||i1==i2||!P[i1]||t>20) printf("False\n"); 
			        else Power(P[i1],P[i2],t);
			        break;//乘方 
			case 17:printf("Input number 1,number 2 and number 3:");
			        scanf("%d%d%d",&j1,&j2,&j3);
			        if((j1<0||j1>9)||(j2<0||j2>9)||(j3<0||j3>9)||j3==j1||j3==j2||!P[j1]||!P[j2]||!P[j1]->next||!P[j2]->next)
					printf("False\n"); 
			        else Gcd(P[j1],P[j2],P[j3]);
			        break;//最大公约式
			case 18:printf("Input number 1,number 2 and number 3:");
			        scanf("%d%d%d",&j1,&j2,&j3);
			        if((j1<0||j1>9)||(j2<0||j2>9)||(j3<0||j3>9)||j3==j1||j3==j2||!P[j1]||!P[j2]||!P[j1]->next||!P[j2]->next)
					printf("False\n"); 
			        else Lcm(P[j1],P[j2],P[j3]);
			        break;//最小公倍式  
			default:printf("False\n");break;
		}
	}
	return 0;
}
