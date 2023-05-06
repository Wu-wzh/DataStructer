#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

typedef struct {
    int data;
    int cur;  // 指向下一个元素的下标
} SLNode, *SList;

void InitSpace(SLNode *space) {
    // 初始化静态链表空间
    for (int i = 0; i < MAXSIZE - 1; i++) {
        space[i].cur = i + 1;  // 让每个节点的cur指向下一个可用空间
    }
    space[MAXSIZE - 1].cur = 0;  // 最后一个节点的cur指向0，表示静态链表为空
}

int Malloc(SLNode *space) {
    // 从静态链表中分配一个空间，返回该空间的下标。
    int i = space[0].cur;
    if (space[0].cur)
        space[0].cur = space[i].cur;
    return i;
}

void Free(SLNode *space, int k) {
    // 释放下标为k的空间，将其插入静态链表的空闲链表中
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

void InitList(SList S) {
    // 初始化静态链表
    for (int i = 0; i < MAXSIZE - 2; i++) {
        S[i].cur = i + 1;  // 让每个节点的cur指向下一个节点
    }
    S[MAXSIZE - 2].cur = 0;  // 最后一个节点的cur指向0，表示静态链表为空
}

void Insert(SList S, int i, int e, SLNode *space) {
    // 在下标为i的节点之后插入一个值为e的节点
    int j = Malloc(space);
    space[j].data = e;
    space[j].cur = S[i].cur;
    S[i].cur = j;
}

void Delete(SList S, int i, SLNode *space) {
    // 删除下标为i的节点
    int j = S[i].cur;
    S[i].cur = space[j].cur;
    Free(space, j);
}

int Locate(SList S, int e, SLNode *space) {
    // 查找值为e的节点的下标，返回下标值
    int i = S[MAXSIZE - 2].cur;
    while (i && space[i].data != e) {
        i = space[i].cur;
    }
    return i;
}

void DestroyList(SList S, SLNode *space) {
    // 销毁静态链表
    int i = S[MAXSIZE - 2].cur;
    while (i) {
        int j = S[i].cur;
        Free(space, i);
        i = j;
    }
    S[MAXSIZE - 2].cur = 0;  // 静态链表再次置空
}

int GetLength(SLNode *space) {
    // 获取静态链表的长度
    int i = space[MAXSIZE - 1].cur;
    int length = 0;
    while (i) {
        length++;
        i = space[i].cur;
    }
    return length;
}

void PrintList(SLNode *space) {
    // 输出静态链表的所有元素
    int i = space[MAXSIZE - 1].cur;
    while (i) {
        printf("%d ", space[i].data);
        i = space[i].cur;
    }
    printf("\n");
}

int main() {
    SLNode space[MAXSIZE];
    SList S = space;
    InitSpace(space);
    InitList(S);
    printf("静态链表初始状态：\n");
    PrintList(space);
    int k = Malloc(space);
    space[k].data = 10;
    Insert(S, 0, k, space);
    k = Malloc(space);
    space[k].data = 20;
    Insert(S, 1, k, space);
    k = Malloc(space);
    space[k].data = 30;
    Insert(S, 2, k, space);
    printf("插入三个元素后的静态链表状态：\n");
    PrintList(space);
    Delete(S, 1, space);
    printf("删除第二个元素后的静态链表状态：\n");
    PrintList(space);
    printf("元素20的位置：%d\n", Locate(S, 20, space));
    printf("元素50的位置：%d\n", Locate(S, 50, space));
    DestroyList(S, space);
    printf("销毁静态链表后的空间状态：\n");
    for (int i = 0; i < MAXSIZE; i++)
        printf("%d ", space[i].cur);
    printf("\n");
    system("pause");
    return 0;
}

