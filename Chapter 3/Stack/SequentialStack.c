/*
栈是限制插入和删除操作的线性表
n个不同元素进栈，出战元素不同排列个数为1/(n+1)*C(2/2n)(排列数)，又叫做卡特兰数
*/
#include <stdio.h>
#include <windows.h>
#define MaxSize 10
#define true 1;
#define false 0;

typedef struct{
    int data[MaxSize];
    int top; //栈顶
} SeqStack;

void InitStack(SeqStack* S){
    S->top = -1;
    // else *S->top = 0;
}

//进栈
int Push(SeqStack* S, int x){
    if (S->top == MaxSize - 1) return false;
    // S->top += 1; //先执行栈顶加一操作
    // S->data[S->top] = 1; //再进行赋值
    //这两句等价于下行
    S->data[++S->top] = x;
    return true;
}
// int Push0(SeqStack* S, int x){
//     if (S->top == MaxSize) return false;
//     // S->top += 1; //先执行栈顶加一操作
//     // S->data[S->top] = 1; //再进行赋值
//     //这两句等价于下行
//     S->data[S->top++] = x;
//     return true;
// }
//出栈(弹出)
int Pop(SeqStack* S, int *x){
    if (S->top == -1) return false;
    *x = S->data[S->top--];
    return true;
}
// int Pop0(SeqStack* S, int &x){
//     if (S->top == -1) return false;
//     x = S->data[--S->top];
//     return false;
// }
//读取栈顶元素(不弹出)
int GetTop(SeqStack* S, int* x){
    if (S->top == -1) return false;
    *x = S->data[S->top];
    return false;
}
// int GetTop0(SeqStack* S, int &x){
//     if (S->top == -1) return false;
//     x = S->data[S->top - 1];
//     return false;
// }

void printStack(SeqStack S){
    while (S.top != -1)
    {
       printf("%d\n", S.data[S.top--]); 
    }
}

int main(){
    SeqStack S;
    int x;

    // 初始化一个空栈
    InitStack(&S);

    // 将元素依次压入栈中
    Push(&S, 2);
    Push(&S, 3);
    Push(&S, 5);
    Push(&S, 6);
    Push(&S, 7);
    Push(&S, 9);

    // 打印栈中元素
    printf("栈中元素：\n");
    printStack(S);
    printf("\n");

    // 依次将元素弹出并打印
    printf("弹出元素：\n");
    int a = 1;
    while (Pop(&S, &x))
    {
        printf("第%d次弹出的元素为：%d\n", a++, x);
    }
    printf("\n");
    system("pause");
    return 0;
}



