#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

//循环双链表，,其节点包含两个指针域，一个指向前驱节点（若存在），另一个指向后继节点（若存在）
//每一个节点之间都相当于建立了两个连接，所以在删除、添加等操作时要考虑去除
typedef struct DNode
{
    int data;
    struct DNode *prior, *next;
} DNode, *DLinkedList;

int InitList(DLinkedList *L)
{
    *L = (DNode *)malloc(sizeof(DNode));
    if (*L == NULL)
        return false;
    (*L)->prior = *L;
    (*L)->next = *L;
    return true;
}

int InsertNextDNode(DNode *p, DNode *s)
{
    if (p == NULL || s == NULL)
        return false;
    s->next = p->next;
    p->next->prior = s;
    s->prior = p;
    p->next = s;
    return true;
}

int InsertPriorDNode(DNode *p, DNode *s)
{
    if (p == NULL || s == NULL)
        return false;
    return InsertNextDNode(p->prior, s);
}

int DeleteNextNode(DNode *p)
{
    if (p == NULL || p->next == p)
        return false;
    DNode *q = p->next;
    p->next = q->next;
    q->next->prior = p;
    free(q);
    return true;
}

DLinkedList List_HeadInsert(DLinkedList *L)
{
    DNode *Head = *L;
    int x;
    scanf("%d", &x);
    while (x != 666)
    {
        DNode *s = (DNode *)malloc(sizeof(DNode));
        s->data = x;
        s->next = Head->next;
        s->prior = Head;
        Head->next->prior = s;
        Head->next = s;
        scanf("%d", &x);
    }
    //建立循环连接
    Head->prior = (*L)->prior;
    (*L)->prior->next = Head;
    return *L;
}


DLinkedList List_TailInsert(DLinkedList *L)
{
    int x;
    DNode *s, *t = *L;
    scanf("%d", &x);
    while (x != 666)
    {
        s = (DNode *)malloc(sizeof(DNode));
        s->data = x;
        s->next = t->next;
        s->prior = t;
        t->next->prior = s;
        t->next = s;
        t = s;
        scanf("%d", &x);
    }
    //建立循环连接
    t->next = *L;
    (*L)->prior = t;
    return *L;
}


void DestroyList(DLinkedList *L)
{
    DNode *p = (*L)->next;
    DNode *q;
    while (p != *L)
    {
        q = p->next;
        free(p);
        p = q;
    }
    free(*L);
    *L = NULL;
}

int isEmpty(DLinkedList L)
{
    return L->next == L;
}

DNode *LocateElement(DLinkedList L, int e)
{
    DNode *p = L->next;
    while (p != L && p->data != e)
    {
        p = p->next;
    }
    if (p == L)
        return NULL;
    return p;
}

int GetLength(DLinkedList L)
{
    DNode *p = L->next;
    int len = 0;
    while (p != L)
    {
        len++;
        p = p->next;
    }
    return len;
}

void printList(DLinkedList L)
{
    DNode *p = L->next;
    while (p != L)
    {
        printf("%d\n", p->data);
        p = p->next;
    }
}

int main()
{
    DLinkedList L = NULL;
    InitList(&L);

    printf("使用尾插法创建循环双链表：\n");
    List_TailInsert(&L);
    printf("循环双链表内容：\n");
    printList(L);

    printf("==========\n");

    printf("使用头插法创建循环双链表：\n");
    DLinkedList L2 = NULL;
    InitList(&L2);
    List_HeadInsert(&L2);
    printf("循环双链表内容：\n");
    printList(L2);

    DestroyList(&L);
    DestroyList(&L2);

    system("pause");
    return 0;
}
