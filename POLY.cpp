#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 10
typedef struct node{
                     float A;
                     int K;
                     struct node *next;
                   }lnode,*link;
link P[N]={NULL};
    
link makenode(float c, int e){
         link p=(link)malloc(sizeof(lnode));
         p->A=c; p->K=e; p->next=NULL;
         return p;
}

void OrderInsert(link h, link s){
     link p,q;
     float x;
     p=h;
     while(p->next && p->next->K<s->K) p=p->next;
     if(p->next && p->next->K==s->K){
                x=p->next->A+s->A;
                if(x==0){q=p->next;p->next=q->next;free(q);}
                else p->next->A=x;
                free(s);
     }
     else{
          s->next=p->next;p->next=s;
          }
}

void Print(link h){
     link p;
     if(!h)printf("NULL\n");
     else if(!h->next)printf("0\n");
     else{
          p=h->next;
          while(p){
                    printf("%.4fx^%d",p->A,p->K);
                    if(p->next&&p->next->A>0)printf("+");
                    p=p->next;
                    }
          printf("\n");
          }
}

void Create(link &h){
     link p;
     float c;
     int e;
     h=makenode(0,-1);
     printf("Input A and K(0,0 exit):");
     while(1){
              scanf("%f%d",&c,&e);
              if(c==0)break;
              p=makenode(c,e);
              OrderInsert(h,p);
              }
}
              
              
void Copy(link &a,link b,link c){
     link pa=a->next,s;
     b=makenode(0,-1);
     while(pa){
              s=makenode(pa->A,pa->K);              
              OrderInsert(b,s);
              pa=pa->next;
     }
              
}



link Sum(link h,link j,link &k){
     link pa=h->next,pb=j->next,pc,Lc;
     Lc=makenode(0,-1);
     while(pa && pb){
              if(pa->K>=pb->K){
                   pc=makenode(pa->A,pa->K);OrderInsert(Lc,pc);pa=pa->next;
              }
              else {
                   pc=makenode(pb->A,pb->K);OrderInsert(Lc,pc);pb=pb->next;
              }
     }
     if(!pb&&pa){
                 while(pa){pc=makenode(pa->A,pa->K);OrderInsert(Lc,pc);pa=pa->next;         }           
     }
     else if(!pa&&pb){
                while(pb){ pc=makenode(pb->A,pb->K);OrderInsert(Lc,pc);pb=pb->next;   }               
     }
     return pc;      
}    

     
     
     

int main(){
     int i,j,k,i1,i2,i3,menu;
     while(1){
        printf("-------------------Menu-----------------\n");
        printf("0 --- Exit\n");
        printf("1 --- Create\n");
        printf("2 --- Print\n");
        printf("3 --- Copy\n");
        printf("4 --- Sum\n");
        printf("----------------------------------------\n");
        printf("Please choose:");
        scanf("%d",&menu);
        printf("----------------------------------------\n");
        switch(menu){
            case 0: return 0;
            case 1:
            	printf("Input ID:  ");
                scanf("%d",&k);
                Create(P[k]);break;
            case 2:
                for(i=0;i<N;i++){
                    printf("P[%d] = ",i);
                    Print(P[i]);
                }
                break;
            case 3:
                printf("Input ID1 and ID2:  ");
                scanf("%d%d",&i1,&i2);
                Copy(P[i1],P[i2]);
                break;
            case 4:
                printf("Input ID1  , ID2 and ID3:  ");
                scanf("%d%d%d",&i1,&i2,&i3);
                P[i3]=Sum(P[i1],P[i2],P[i3]);
                break;     
            default:;                   
        }
    }
    return 0;
}     
                                
                                
                           
                                
                                

             



               
    
