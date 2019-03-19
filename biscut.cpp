#include<stdio.h>
#include<stdlib.h> 
#define N 15000
#define M 20000000
long D[N];
int S[N];
typedef struct ArcNode{
        int adjvex;
        long weight;
        struct ArcNode *next; 
}ArcNode;
typedef struct VertexNode{
        int data;
        ArcNode *firstarc; 
}VertexNode,AdjList[N];
typedef struct{
        AdjList vertices;
        AdjList revertic;
        int vexnum,arcnum; 
} ALGraph;
void CreateGraph(ALGraph &G){
     int vi,vj,k;
     long weight;
     scanf("%d%d",&G.vexnum,&G.arcnum);
     for(k=0;k<G.vexnum;k++){
         G.vertices[k].data=k+1;
         G.revertic[k].data=k+1;
         G.vertices[k].firstarc=NULL;
         G.revertic[k].firstarc=NULL;
     }
     for(k=0;k<G.arcnum;k++){
         scanf("%d%d%d",&vi,&vj,&weight);
         if(vi!=vj){
         	ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode)),*q=(ArcNode *)malloc(sizeof(ArcNode));
         	p->adjvex=vj-1;q->adjvex=vi-1;
         	p->weight=q->weight=weight; 
         	p->next=G.vertices[vi-1].firstarc;
         	q->next=G.revertic[vj-1].firstarc;
         	G.vertices[vi-1].firstarc=p;
         	G.revertic[vj-1].firstarc=q;
    	 }
     } 
}
void DFS(ALGraph &G,int v){
	ArcNode *p;
	S[v-1]=0;
	for(p=G.revertic[v-1].firstarc;p;p=p->next)
		if(S[p->adjvex]) DFS(G,p->adjvex+1);
}
void ClearTrap(ALGraph G){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(S[i]==1){
			ArcNode *p=G.revertic[i].firstarc;
			while(p){
				S[p->adjvex]=2;
				p=p->next;
			}
		}
	}
	/*for(i=0;i<G.vexnum;i++){
		if(S[i]==2){
			ArcNode *p=G.revertic[i].firstarc,*s=G.vertices[i].firstarc;
			while(p){
				ArcNode *q=G.vertices[p->adjvex].firstarc;
				while(q){
					if(q->adjvex==i) {q->weight=M;break;}
					q=q->next;
				}
				p=p->next;
			}
			while(s){
				s->weight=M;
				s=s->next;
			}
		}
	}
	for(i=0;i<G.vexnum;i++) S[i]=0;*/
}
void Dijkstra(ALGraph G,int v0){
     int i,j,k,w,flag;
     long weight=M,h,min;
     ArcNode *p=G.vertices[v0-1].firstarc;
     while(p){
         if(p->weight<D[p->adjvex]) D[p->adjvex]=p->weight;
         p=p->next;
     }
     S[v0-1]=1;
     D[v0-1]=0;
     for(i=1;i<G.vexnum;i++){
         min=M;
         for(j=0;j<G.vexnum;j++)
             if(!S[j]&&D[j]<min) {min=D[j];k=j;}
         S[k]=1;
         for(j=0;j<G.vexnum;j++){
         	flag=1;
         	ArcNode *q=G.vertices[k].firstarc;
         	while(q){
             	if(q->adjvex==j&&q->weight<weight) {weight=q->weight;flag=0;}
             	q=q->next;
	     	}
	     	if(flag==1) weight=M;
	     	h=(D[k]+weight>M?M:D[k]+weight);
         	if(!S[j]&&h<D[j]) D[j]=h;
         }
     }
}
int main(){
    int s,t,i,j;
    ALGraph G;
    CreateGraph(G);
    for(i=0;i<N;i++) S[i]=1;
    for(i=0;i<G.vexnum;i++) D[i]=M;
    scanf("%d%d",&s,&t);
    DFS(G,t);
    ClearTrap(G);
    Dijkstra(G,s);
    if(D[t-1]==M) printf("-1");
    else printf("%d",D[t-1]);
    return 0; 
}
