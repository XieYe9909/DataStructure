#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define N 800000
int bmm[N][5]={0};
typedef struct BiTNode{
	int data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef struct LNode{
	BiTree data;
	LNode *next;
}LNode,*LinkList;
typedef struct{
	LinkList front;
	LinkList rear;
}LinkQueue;
void InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(LinkList)malloc(sizeof(LNode));
	Q.front->next=NULL;
}
void EnQueue(LinkQueue &Q,BiTree e){
	LinkList p=(LinkList)malloc(sizeof(LNode));
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
int DeQueue(LinkQueue &Q,BiTree &e){
	if(Q.front==Q.rear) return 0;
	LinkList p=Q.front->next;
	Q.front->next=p->next;
	e=p->data;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return 1;
}
void DestroyQueue(LinkQueue &Q){
	while(Q.front){
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
}
BiTree TreeNode(int n){
	BiTree T=(BiTree)malloc(sizeof(BiTNode));
	T->data=n;
	T->lchild=T->rchild=NULL;
	return T;
}
int num(int a[],int len){
	int i=0;
	while(i<len-1&&a[i]<a[len-1]) i++;
	return i;
}
BiTree CreateTree(int a[],int len){
	if(len==0) return NULL;
	else{
		int n=num(a,len);
		BiTree p=TreeNode(*(a+len-1));
		p->lchild=CreateTree(a,n);
		p->rchild=CreateTree(a+n,len-n-1);
		return p;
	}
}
int PreOrder(BiTree T,int &i,int lev){
	int nl=0,nr=0;
	if(!T) return 0;
	else{
		lev++;
		if(T->lchild){
			bmm[T->lchild->data-1][0]=T->data;
			bmm[T->data-1][1]=T->lchild->data;
		}
		if(T->rchild){
			bmm[T->rchild->data-1][0]=T->data;
			bmm[T->data-1][2]=T->rchild->data;
		}
		printf("%d ",T->data);
		nl=PreOrder(T->lchild,i,lev);
		nr=PreOrder(T->rchild,i,lev);
		bmm[T->data-1][3]=lev;
		bmm[T->data-1][4]=1+nl+nr;
		return 1+nl+nr;
	}
}
void Layer(BiTree T){
	LinkQueue Q;
	InitQueue(Q);
	BiTree p;
	if(T) EnQueue(Q,T);
	while(Q.rear!=Q.front){
		DeQueue(Q,p);
		printf("%d ",p->data);
		if(p->lchild) EnQueue(Q,p->lchild);
		if(p->rchild) EnQueue(Q,p->rchild);
	}
	DestroyQueue(Q);
}
int main(){
	int i=0,j,m,n,lev=-1;
	int a[N]={0},b[N]={0};
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%d",&a[i]);
	scanf("%d",&m);
	for(i=0;i<m;i++) scanf("%d",&b[i]);
	BiTree p=CreateTree(a,n);
	PreOrder(p,i,lev);
	printf("\n");
	Layer(p);
	printf("\n");
	for(i=0;i<m;i++){
		for(j=0;j<5;j++)
		if(j!=4) printf("%d ",bmm[b[i]-1][j]);
		else printf("%d",bmm[b[i]-1][j]);
		printf("\n");
	}
	return 0; 
}
