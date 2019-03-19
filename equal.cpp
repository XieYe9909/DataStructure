#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define N 1000
typedef struct Polynomial{
	long long coef;
	int expn;
	struct Polynomial *next;
}Polynomial,*Polyn;
typedef struct OpeNode{
	char data;
	struct OpeNode *next;
}*OpeStack;
typedef struct ValNode{
	Polyn data;
	struct ValNode *next;
}*ValStack;
void InitOpeStack(OpeStack &S){
	S=NULL;
} 
void InitValStack(ValStack &S){
	S=NULL;
}
Polyn MakeNode(long long coef,int expn){
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
		if(p->coef!=0){
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
void Create(Polyn &L){
	Polyn p;
	long long c;
	int e;
	L=MakeNode(-1,-1);
	while(1){
		scanf("%lld%d",&c,&e);
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
void Destroy(Polyn &L){
	Polyn p=L,q;
	while(p){
		q=p;
		p=p->next;
		free(q);
	}
	L=NULL;
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
void Power(Polyn L1,Polyn &L2,int x){
	Polyn temp1=MakeNode(-1,-1),temp2,temp3; 
	temp1->next=MakeNode(1,0);
	Copy(L1,temp2);
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
void PushOpe(OpeStack &S,char e){
	OpeStack p=(OpeStack)malloc(sizeof(OpeNode));
	p->data=e;
	p->next=S;
	S=p;
}
void PushVal(ValStack &S,Polyn e){
	ValStack p=(ValStack)malloc(sizeof(ValNode));
	p->data=e;
	p->next=S;
	S=p;
}
int PopOpe(OpeStack &S,char &e){
	if(S){
		OpeStack p=S;
		S=S->next;
		e=p->data;
		free(p);
		return 1;
	}
	else return 0;
}
int PopVal(ValStack &S,Polyn &e){
	if(S){
		ValStack p=S;
		S=S->next;
		e=p->data;
		free(p);
		return 1;
	}
	else return 0;
}
int GetOpeTop(OpeStack S,char &c){
	if(!S) return 0;
	else{
		c=S->data;
		return 1;
	}
}
int GetValTop(ValStack S,Polyn &c){
	if(!S) return 0;
	else{
		c=S->data;
		return 1;
	}
}
void DestroyOpeStack(OpeStack &S){
    OpeStack p;
	while(S){
    	p=S;
    	S=S->next;
    	free(p);
    } 
}
void DestroyValStack(ValStack &S){
    ValStack p;
	while(S){
    	p=S;
    	S=S->next;
    	free(p);
    } 
}
int isope(char c){
	if(c=='#'||c=='+'|| c == '-'|| c == '*'|| c == '^'|| c == '('|| c == ')') return 1;
	else return 0;
}
int match(char exp[]){
	int m=0,n=0;
	char *p=exp,*q=exp;
	while(*p){
		if(*p=='(') m++;
		p++;
	}
	while(*q){
		if(*q==')') n++;
		q++;
	}
	if(m==n) return 1;
	else return 0;
} 
int Preop(char a,char b){
	int x,y;
	switch(a){
		case '#':x=-1;break;
		case '(':x=0;break;
		case '+':
		case '-':x=1;break;
		case '*':x=2;break;
		case '^':x=3;break; 
	}
	switch(b){
		case '#':y=-1;break;
		case '(':y=0;break;
		case '+':
		case '-':y=1;break;
		case '*':y=2;break;
		case '^':y=3;break; 
	}
	return x>=y?1:0;
}
Polyn Operate(Polyn L1,Polyn L2,char ch){
	Polyn L3=NULL;
	switch(ch){
		case '+':Add(L1,L2,L3);break;
		case '-':Sub(L1,L2,L3);break;
		case '*':Multiply(L1,L2,L3);break;
		case '^':Power(L1,L3,L2->next->coef);break;
		default:break;
	}
	return L3;
}
Polyn EvaluateExp(char exp[]){
	if(match(exp)==0) return NULL;
	else{
	OpeStack SOP;
	ValStack SVAL;
	InitOpeStack(SOP);PushOpe(SOP,'#');
	InitValStack(SVAL);
	char *p=exp,ch,j,c,d;
	int i;
	Polyn L,a,b,M;
	while(p&&SOP){
		ch=*p++;
		if(ch==' ') continue;
		else if(!isope(ch)){
			if(ch=='x'){
				L=MakeNode(-1,-1);
				L->next=MakeNode(1,1);
				PushVal(SVAL,L);
				continue;
			}
			else{
				i=ch-48;
				while(!isope(j=*p)){
					p++;
					if(j=='x') break;
					else if(j==' ') continue;
			    	else{
			    		i*=10;
						i+=(j-48);
						i%=11;
					}
				}
				L=MakeNode(-1,-1);
				L->next=MakeNode(i,0);
				PushVal(SVAL,L);
				continue;
			}
		}
		else{
			switch(ch){
				case '(':PushOpe(SOP,ch);break;
				case ')':while(PopOpe(SOP,c)&&c!='('){
				     		if(PopVal(SVAL,b)&&PopVal(SVAL,a)){
				     			PushVal(SVAL,Operate(a,b,c));
				     			Destroy(a);
				     			Destroy(b);
				     		}
				     		else{
				     			DestroyOpeStack(SOP);
				     			DestroyValStack(SVAL);
				     			return NULL;
				     		}
			         	}break;
			default:while(GetOpeTop(SOP,c)&&Preop(c,ch)&&!(c=='#'&&ch=='#')){
				    	PopOpe(SOP,c);
				    	if(PopVal(SVAL,b)&&PopVal(SVAL,a)){
				     		PushVal(SVAL,Operate(a,b,c));
				     		Destroy(a);
				     		Destroy(b);
				     	}
				     	else{
				     		DestroyOpeStack(SOP);
				     		DestroyValStack(SVAL);
				     		return NULL;
				     	}	
			        }
					if(GetOpeTop(SOP,c)&&c=='#'&&ch=='#') PopOpe(SOP,d);
					if(ch!='#') PushOpe(SOP,ch);
					break;
			}
		}
	}
	GetValTop(SVAL,M);
	return M;
	}
}
int Compare(Polyn L1,Polyn L2){
	int a=1;
	Polyn p,q;
	if(!L1||!L2) a=0;
	else{
		p=L1->next,q=L2->next;
		while(p){
			if(!q||p->coef!=q->coef||p->expn!=q->expn) {
				a=0;
				break;
			}
			else{
				p=p->next;
				q=q->next;
			}
		}
		if(q) a=0;
	}
	return a;
}
int main(){
	int n,i=1;
    char exp[N],*p=exp;
	Polyn L1,L2;;
	scanf("%d",&n);
	scanf("%*c%[^\n]",exp);
	while(*p!='\0') p++;
	*p++='#';
	*p='\0';
	L1=EvaluateExp(exp);
	for(;i<=n;i++){
		scanf("%*c%[^\n]",exp);
	  	p=exp;
	  	while(*p) p++;
	  	*p++='#';
	 	*p='\0';
	  	L2=EvaluateExp(exp);
	  	if(Compare(L1,L2)) printf("%c",'A'+i-1);
	  	Destroy(L2);
	}
	Destroy(L1);
	return 0; 
}
