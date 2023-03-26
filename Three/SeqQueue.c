#include <stdio.h>
#include <windows.h>
#define MaxSize 10
#define true 1
#define false 0
////
//
//使用循环数组存储队列，其与静态数组不同的是包含了队头和队尾指针 
//因此顺序队列其实是环状的，需要进行取模的运算

//若想充分利用顺序表中的所有元素，则需要在Queue结构添加辅助变量，size或者tag，这样在判断队列为满的时候，就不用牺牲一个存储空间
//只需要判断size或者tag的值，来判断头指针=尾指针时到底是队空还是队满
typedef struct Queue{
    int data[MaxSize];
    int front, tail;
}SqQueue;

int InitQueue(SqQueue *Q){
    Q->front = Q->tail = 0;
    return true;
}

//队尾指针是指向队尾的下一个位置，在具体题目中可能会改变为指向队尾，需要仔细审题
int EnQueue(SqQueue *Q, int e){
    if ((Q->tail + 1) % MaxSize == Q->front) return false;
    Q->data[Q->tail] = e;
    Q->tail = (Q->tail + 1) % MaxSize;
    return true;
}

int DeQueue(SqQueue *Q, int *x){
    if (Q->front == Q->tail) return false;
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MaxSize;
    return true;
}

int GetHead(SqQueue Q,int *x){
    if (Q.front == Q.tail) return false;
    *x = Q.data[Q.front];
    return true;
}
int isEmpty(SqQueue Q){ //当队尾指针等于队头指针时，队列为空
    return Q.front == Q.tail;
}

int GetLength(SqQueue Q){
    return (Q.tail + MaxSize - Q.front) % MaxSize;
}

void printQueue(SqQueue Q){
    while (Q.front != Q.tail){
        printf("%d<-",Q.data[Q.front]);
        Q.front = (Q.front + 1) % MaxSize;
    }
    printf("end\n");
}
    
int main(){
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 4);
    printQueue(Q);
    int x;
    DeQueue(&Q, &x);
    printQueue(Q);
    printf("%d\n", GetLength(Q));
    system("pause");
    return 0;
}