#include <stdio.h>
#include <windows.h>
#define true 1;
#define false 0;

//重要：在定义结构体时，struct后面的LinkNode不能省略，否则将会导致编译器无法识别LinkNode类型，因此不能使用LStatic来定义LinkNode的指针
//所以在执行S->next的下一步操作时，系统不能把他看作LinkNode*类型，所以就会报错
typedef struct LinkNode{
    int data;
    struct LinkNode* next;
}LinkNode, *LStatic;

//带头结点
int InitStack(LStatic* S){
    *S = (LinkNode*) malloc(sizeof(LinkNode));
    if (*S == NULL) return false;
    (*S)->next = NULL;
    return true;
}
int InitStack_NoHead(LStatic* S){
    *S = (LinkNode*) malloc(sizeof(LinkNode));
    if (*S == NULL) return false;
    (*S) = NULL;
    return true;
}

int Push(LStatic* S, int x){ 
    if (*S == NULL) return false;
    LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
    t->data = x;
    t->next = (*S)->next;
    (*S)->next = t;
    return true;
}
int Push_NoHead(LStatic* S, int x){ 
    LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
    t->data = x;
    // if ((*S)->next = NULL) {
    //     t->next = NULL;
    //     *S = t;   
    // }
    // else{
    //     t->next = *S;
    //     *S = t;
    //     return true;
    // }
    t->next = *S;
    *S = t;
    return true;

    
}

int Pop(LStatic* S, int *x){
    if ((*S)->next == NULL) return false;

    LinkNode* p = (*S)->next;
    *x = p->data;
    (*S)->next = p->next;
    free(p);
    return true;
}
int Pop_NoHead(LStatic* S, int *x){
    if ((*S) == NULL) return false; //链栈为空
    LinkNode* p = *S;
    *x = p->data;
    // if (p->next == NULL){
    //     (*S) = NULL;
    //     return true;
    // }
    *S = p->next;
    free(p);
    return true;
}

int GetTop(LStatic S, int *x){
    if (S->next == NULL) return false;
    *x = S->next->data;
    return true;
}
int GetTop_NoHead(LStatic S, int *x){
    if (S == NULL) return false;
    *x = S->data;
    return false;
}

void printList(LStatic S){
    LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
    t = S->next;
    while (t != NULL)
    {
        printf("%d\n",t->data);
        t = t->next;
    }
    
}
void printList_NoHead(LStatic S){
    LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
    t = S;
    while (t != NULL)
    {
        printf("%d\n",t->data);
        t = t->next;
    }
    
}

int main(){
    LStatic S;
    int x;

    // 初始化一个空栈
    InitStack_NoHead(&S);

    // 压入第一个元素并打印栈中元素
    Push_NoHead(&S, 1);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 压入第二个元素并打印栈中元素
    Push_NoHead(&S, 2);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 弹出一个元素并打印栈中元素和弹出的元素
    Pop_NoHead(&S, &x);
    printf("弹出的元素：%d\n", x);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 压入第三个元素并打印栈中元素
    Push_NoHead(&S, 3);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 弹出一个元素并打印栈中元素和弹出的元素
    Pop_NoHead(&S, &x);
    printf("弹出的元素：%d\n", x);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 压入第四个元素并打印栈中元素
    Push_NoHead(&S, 4);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 弹出一个元素并打印栈中元素和弹出的元素
    Pop_NoHead(&S, &x);
    printf("弹出的元素：%d\n", x);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 压入第五个元素并打印栈中元素
    Push_NoHead(&S, 5);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 依次弹出两个元素并打印栈中元素和弹出的元素
    Pop_NoHead(&S, &x);
    printf("弹出的元素：%d\n", x);
    Pop_NoHead(&S, &x);
    printf("弹出的元素：%d\n", x);
    printf("栈中元素：\n");
    printList_NoHead(S);
    printf("-----------\n");

    // 测试当链栈为空时无法继续弹出元素的情况
    if (!Pop_NoHead(&S, &x))
    {
        printf("链栈为空，无法继续弹出元素\n");
    }

    system("pause");
    return 0;
}


