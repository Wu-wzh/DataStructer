#include <stdio.h>
#include <windows.h>
#define MaxSize 10

typedef struct {
    int data[MaxSize];
    int top1;  // Stack 1 top pointer
    int top2;  // Stack 2 top pointer
} SharedSeqStack;

void InitStack(SharedSeqStack *S) {
    S->top1 = -1;
    S->top2 = MaxSize;
}

// Push element x onto Stack 1
int Push1(SharedSeqStack *S, int x) {
    if (S->top1 == S->top2 - 1) return 0;  // Stack overflow
    S->data[++S->top1] = x;
    return 1;
}

// Push element x onto Stack 2
int Push2(SharedSeqStack *S, int x) {
    if (S->top1 == S->top2 - 1) return 0;  // Stack overflow
    S->data[--S->top2] = x;
    return 1;
}

// Pop the top element from Stack 1
int Pop1(SharedSeqStack *S, int *x) {
    if (S->top1 == -1) return 0;  // Stack underflow
    *x = S->data[S->top1--];
    return 1;
}

// Pop the top element from Stack 2
int Pop2(SharedSeqStack *S, int *x) {
    if (S->top2 == MaxSize) return 0;  // Stack underflow
    *x = S->data[S->top2++];
    return 1;
}

// Get the top element of Stack 1
int GetTop1(SharedSeqStack *S, int *x) {
    if (S->top1 == -1) return 0;
    *x = S->data[S->top1];
    return 1;
}

// Get the top element of Stack 2
int GetTop2(SharedSeqStack *S, int *x) {
    if (S->top2 == MaxSize) return 0;
    *x = S->data[S->top2];
    return 1;
}

void PrintStack(SharedSeqStack S) {
    printf("Stack 1:\n");
    for (int i = S.top1; i >= 0; i--) {
        printf("%d\n", S.data[i]);
    }
    printf("Stack 2:\n");
    for (int i = S.top2; i < MaxSize; i++) {
        printf("%d\n", S.data[i]);
    }
}

int main() {
    SharedSeqStack S;

    InitStack(&S);
    Push1(&S, 2);
    Push1(&S, 3);
    Push2(&S, 5);
    Push2(&S, 6);
    int x;
    Pop1(&S, &x);
    Pop2(&S, &x);
    PrintStack(S);
    system("pause");
    return 0;
}
