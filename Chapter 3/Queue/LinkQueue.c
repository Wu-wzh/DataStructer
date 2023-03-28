#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0

//链式存储中队列一般不会满
typedef struct LinkNode{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct LinkQueue{
    LinkNode *front, *tail;
}LinkQueue;

int InitQueue(LinkQueue *Q){
    Q->front = Q->tail = (LinkNode*)malloc(sizeof(LinkNode));
    Q->front->next = NULL;
    return true;
}
int InitQueue_NoHead(LinkQueue *Q){
    Q->front = Q->tail = NULL;
    return true;
}

//入队操作，从链表尾部进行插入 只对队尾进行操作
void EnQueue(LinkQueue *Q, int e){
    LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = e;
    p->next =NULL;
    Q->tail->next = p;
    Q->tail = p;
}
void EnQueue_NoHead(LinkQueue *Q, int e){
    LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = e;
    p->next =NULL;
    if (Q->front == Q->tail){
        Q->front == p;
        Q->tail == p;
    }
    else{
        Q->tail->next = p;
        Q->tail = p;    
    }
}

//出队操作，只对头节点进行操作，但是要注意，当出队后队列变为空，此时需要修改tail尾指针使其与front指向同一位置
int DeQueue(LinkQueue *Q, int *x){
    if (Q->front == Q->tail) return false;
    LinkNode *p = Q->front->next;
    *x = p->data;
    Q->front->next = p->next;
    if (p == Q->tail) Q->front = Q->tail;
    free(p);
    return true;
}
int DeQueue_NoHead(LinkQueue *Q, int *x){
    if (Q->front == NULL) return false;
    LinkNode *p = Q->front;
    *x = p->data;
    Q->front = p->next;
    if (p == Q->tail){
        Q->front = NULL;
        Q->tail = NULL;
    }
    free(p);
    return true;
}

int isEmpty(LinkQueue Q){
    if (Q.front == Q.tail) return true;
    else return false;
}

void printQueue(LinkQueue Q){
    LinkNode *p = Q.front->next;
    while (p->next != NULL){
        printf("%d<-", p->data);
        p = p->next;
    }
    printf("end\n");
}
int main(){
    LinkQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 3);
    EnQueue(&Q, 4);
    printQueue(Q);
    int x;
    DeQueue(&Q, &x);
    printQueue(Q);
    system("pause");
    return 0;
}
//