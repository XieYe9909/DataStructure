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
	else if(!L->next) printf("%.4lf",c);
	else{
		p=L->next;
		while(p){
			switch(p->expn){
				case 0:printf("%.4lf",p->coef);break;
				case 1:printf("%.4lfx",p->coef);break;
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
	while(1){
		scanf("%lf%d",&c,&e);
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
	float A;int K;
	Polyn p,q;
	switch(t){
		case 1: scanf("%lf%d",&A,&K);
		       p=MakeNode(A,K);
		       Insert(L,p);
		       break;
		case 2:scanf("%d",&K);
		       p=L->next;
		       q=L;
		       while(p){
		       	   if(p->expn==K){
		       	   	  q->next=p->next;
		       	   	  free(p);
		       	   	  break;
		       	   }
		       	   else {
		       	   	  q=p;
		       	   	  p=p->next;
		       	   }
		       }
		       break;
		case 3:scanf("%lf%d",&A,&K);
		       p=L->next;
		       q=L;
		       while(p){
		       	   if(p->expn==K){
		       	   	  p->coef=A;
		       	   	  if(fabs(A)<1e-8){
		       	   	  		q->next=p->next;
		       	   	  		free(p);
		       	   	  }
		       	   	  break;
		       	   }
		       	   else{
		       	   	  q=p;
		       	   	  p=p->next;
		       	   }
		       }
		       break;
		default:break;
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
	Polyn temp1,temp2,p;
	float c;
	Multiply(L1,L2,temp1);
	Gcd(L1,L2,temp2);
	Divide(temp1,temp2,L3);
	p=L3->next;
	c=p->coef;
	while(p){
		p->coef/=c;
		p=p->next;
	}
}
int main(){
	int n,i,i1,i2,j1,j2,j3,t,menu;
	float x,x1,x2;
    while(1){
        scanf("%d",&menu);
        switch(menu){
        	case 0:return 0;//???
        	case 1:scanf("%d",&n);
        		   Create(P[n]);
        		   break;//????
        	case 2:scanf("%d",&n);
        		   Print(P[n]);
				   break;//??? 
			case 3:scanf("%d%d",&i1,&i2);
			       Copy(P[i1],P[i2]);
			       break;//????
			case 4:scanf("%d%d%d",&j1,&j2,&j3);
			       Add(P[j1],P[j2],P[j3]);
			       break;//???
			case 5:scanf("%d%d%d",&j1,&j2,&j3);
			       Sub(P[j1],P[j2],P[j3]);
			       break;//???
			case 6:scanf("%d%lf",&n,&x);
				   printf("%.4lf\n",Value(P[n],x));
				   break;//???
			case 7:scanf("%d",&n);
			       Destroy(P[n]);
			       break;//????
			case 8:scanf("%d",&n);
			       Empty(P[n]);
			       break;//???
			case 9:scanf("%d%d",&n,&t);
			       Modify(P[n],t);
			       break;//???
			case 10:scanf("%d%d",&i1,&i2);
			        Differential(P[i1],P[i2]);
			        break;//??
			case 11:scanf("%d%d",&i1,&i2);
			        In_integral(P[i1],P[i2]);
			        break;//????????
			case 12:scanf("%d%lf%lf",&n,&x1,&x2);
			        printf("%.4lf\n",De_integral(P[n],x1,x2));
			        break;//??????
			case 13:scanf("%d%d%d",&j1,&j2,&j3);
			        Multiply(P[j1],P[j2],P[j3]);
			        break;//???
			case 14:scanf("%d%d%d",&j1,&j2,&j3);
			        Divide(P[j1],P[j2],P[j3]);
			        break;//????
			case 15:scanf("%d%d%d",&j1,&j2,&j3);
			        Mod(P[j1],P[j2],P[j3]);
			        break;//????
			case 16:scanf("%d%d%d",&i1,&i2,&t);
			        Power(P[i1],P[i2],t);
			        break;//??? 
			case 17:scanf("%d%d%d",&j1,&j2,&j3);
			        Gcd(P[j1],P[j2],P[j3]);
			        break;//????? 
			case 18:scanf("%d%d%d",&j1,&j2,&j3);
			        Lcm(P[j1],P[j2],P[j3]);
			        break;//??§³?????  
			default:break;
		}
	}
}

