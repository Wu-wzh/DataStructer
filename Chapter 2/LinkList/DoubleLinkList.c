#include <stdio.h>
#include <windows.h>
#define true 1;
#define false 0;

//双向链表，其节点包含两个指针域，一个指向前驱节点（若存在），另一个指向后继节点（若存在）
//每一个节点之间都相当于建立了两个连接，所以在删除、添加等操作时要考虑去除.

typedef struct DNode
{
    int data;
    struct DNode *prior,*next;
} DNode, *LinkList;

//同样传入的参数L是一个指针，函数内部使用*操作，所以* L就表示传入参数的地址，通过修改这个地址中的内容，从而实现对L的修改
//参数singal表示是否有头节点
int InitList(LinkList *L, int sinal){
    *L = (DNode*)malloc(sizeof(DNode));
    if (*L == NULL) return false;
    if (sinal){
        (*L)->prior = NULL;
        (*L)->next = NULL;
    }
    else *L = NULL;
    return true;
}

//以下操作的前插和后插操作封装起来，提高代码的可读性。

//后插操作
int InsertNextDNode(DNode *p, DNode *s){
    if (p == NULL || s == NULL) return false;
    s->next = p->next;
    if (p->next != NULL)
        p->next->prior = s;
    s->prior = p;
    p->next = s;
    return true;
}

//前插操作
//由于有prior指针域，前插操作就变得相对简单了
int InsertPriorDNode(DNode *p, DNode *s){
    if (p == NULL || s == NULL) return false;
    s->prior = p->prior;
    if (p == NULL)
        p->prior->next = s;
    p->prior = s;
    s->next = p;
}

//双链表的删除操作
//需要将双链表的prior和next指针域同时修改
//删除p的后继节点
int DeleteNextNode(DNode* p){
    if (p == NULL) return false;
    DNode* q = p->next;
    if (q == NULL) return false;
    p->next = q->next;
    if (q->next != NULL)
        q->next->prior = p;
    free(q);

    return true;
}

//头插法
/*头插法有两种实现方法
第一种是通过不断地向头节点后面插入
或者再保证第一个节点存在时，不断地向第一个节点前面插入
下面仅实现了第一种方法
*/
LinkList List_HeadInsert(LinkList* L){
    DNode* Head = *L;
    int x;
    scanf("%d", &x);
    while (x != 666)
    {
        DNode* p = (DNode*)malloc(sizeof(DNode));
        p->data = x;
        InsertNextDNode(Head, p);
        scanf("%d", &x);
    }
    return *L;
}

//尾插法
LinkList List_TailInsert(LinkList* L){
    int x;
    DNode *s, *t = *L;
    scanf("%d",&x);
    while (x != 666)
    {
        s = (DNode*)malloc(sizeof(DNode));
        s->data = x;
        t->next = s;
        t = s; //关键，t尾指针始终指向s最后一个节点
        scanf("%d",&x);
    }
    t->next = NULL;
    return *L;
}




//销毁整个双链表
void DestoryList(LinkList* L){
    while ((*L)->next != NULL)
        DeleteNextNode(*L);
    free(*L);
    L=NULL;
}

int isEmpty(LinkList L, int signal){
    if (signal) return L->next == NULL;
    else return L == NULL;
}

DNode *LocateElement(LinkList L, int e) {
    DNode *p = L->next;
    while (p != NULL && p->data != e) {
        p = p->next;
    }
    return p;
}

int GetLength(LinkList L) {
    DNode *p = L;
    int len = 0;
    while (p->next != NULL) {
        len++;
        p = p->next;
    }
    return len;
}

void printList(LinkList L, int signal){
    DNode *p = L;
    if (signal == 1) p = p->next;
    while (p != NULL){
        printf("%d\n", p->data);
        p = p->next;
    }
}


int main() {
    LinkList L = NULL;
    InitList(&L, 1);

    // 使用尾插法创建双链表
    printf("使用尾插法创建双链表：\n");
    List_TailInsert(&L);
    printf("双链表内容：\n");
    printList(L, 1);

    printf("==========\n");

    // 使用头插法创建双链表
    printf("使用头插法创建双链表：\n");
    LinkList L2 = NULL;
    InitList(&L2, 1);
    List_HeadInsert(&L2);
    printf("双链表内容：\n");
    printList(L2, 1);

    printf("==========\n");

    // 按值查找元素
    printf("按值查找元素：\n");
    int target = 3;
    DNode *foundNode = LocateElement(L, target);
    if (foundNode) {
        printf("找到元素：%d\n", foundNode->data);
    } else {
        printf("未找到元素\n");
    }

    printf("==========\n");

    // 计算链表长度
    printf("计算链表长度：\n");
    int len = GetLength(L);
    printf("链表长度：%d\n", len);

    printf("==========\n");

    // 在指定位置插入节点
    printf("在指定位置插入节点：\n");
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->data = 99;
    DNode *posNode = LocateElement(L, 2);
    if (posNode) {
        InsertNextDNode(posNode, newNode);
    }
    printf("插入新节点后的链表内容：\n");
    printList(L, 1);

    printf("==========\n");


    // 销毁链表
    printf("销毁链表：\n");
    DestoryList(&L);
    printf("链表已销毁\n");

    system("pause");
    return 0;
}