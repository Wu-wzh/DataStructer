//单链表虽然在插入、删除等操作比顺序表时间复杂度更低，但由于单链表只有往后指的指针，因此无法逆向检索，这就导致了在编写代码的时候需要额外考虑最后一个节点的情况
#include <stdio.h>
#include <windows.h>
#define true 1;
#define false 0;
typedef struct LNode{
    int data;
    struct LNode* next;
}LNode, *LinkList;

//在实际使用中，想要使用指针既可以使用LNode*也可以使用LinkeList，
//两者等价，但是一般要根据实际情况使用两者，如果代表的是一个列表，使用LinkList，如果代表的是一个单独的节点，则使用LNode*

//此为带头节点的链表，带有头节点时会使得操作更加简单[
    

//重要！！：函数参数中的*和函数内部的*不是一个意思
//函数参数中代表的是LinkList类型的指针，由于LinkList本身就是个指针，所以函数参数中的L是一个指向指针的指针
//但在函数内部*，代表的是解引用操作，既获取L所指的内容，因为L是一个指针的指针，所以*L就是获取L的内容，既那个指针，也就是那个LinkList；
//由此*L便指向了LinkList，通过修改*L的内容，就可以实现LinkList的内容
int InitList(LinkList* L){
    *L = (LNode*) malloc(sizeof(LNode));
    if (*L == NULL) return false;
    (*L)->next = NULL;
    return true;
}

int InitList_NoHead(LinkList* L){
    *L = (LNode*) malloc(sizeof(LNode));
    if (*L == NULL) return false;
    *L = NULL;
    return true;
}
//实验：参数使用LinkList行不行
// int InitList_Test(LinkList L){ //因为LinkList是个指针，所以L其实是指针，指向的是这个节点
//     L = (LNode*) malloc(sizeof(LNode)); //因为L是个指针，所以直接给他申请内存 L只是个传入参数L的复制品，因此在函数内部对L修改并不会影响传入参数L的内容
//     if (*L == NULL) return false;
//     (*L)->next = NULL;
//     return true;
// } //输出之后发现L依然为NULL，所以这个函数并没有初始化成功

int InitList_My(LinkList* L){
    //
    *L = (LNode*) malloc(sizeof(LNode));
    if (*L == NULL) return false;
    (*L)->data = 10;
    (*L)->next = NULL;
    return true;
}

//下面是不带头结点的链表，不常用
int InitList_Nohead(LinkList* L){
    *L = NULL;
    return true;
}

//判断链表是否为空
int isEmpty(LinkList L){
    // if (L->next == NULL) return true;
    // else return false;
    return L->next == NULL;
}


//接下来的节点前插和后插封装成函数，方便在其他函数中调用，提高代码可读性，避免过度冗杂

//将在指定节点后面后插进行封装
int InsertNextNode(LNode* p, int e){ 
    if (p == NULL) return false;
    LNode *s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
    // //以上循环的目的是为了找到第i - 1个节点，方便进行插入操作
    // if (p == NULL) return false; //说明此时链表为空，连头节点都没有
    // LNode* s = (LNode*)malloc(sizeof(LNode));
    // s->data = e;
    // s->next = p->next; //这两个顺序不能颠倒，s链接后面的时候需要通过p的next链接，
    // p->next = s; //如果先把p的next和s链接，会导致s找不到原来p之后的元素，这样原先p之后的元素就被丢失了
    // //以上四条代码是在已经找到位置的前提下，进行数据的插入
    // return true;
    //上面一段代码用函数InsertNextNode进行封装。
}

//前驱节点插入
/*
若按照后继节点插入的思想，需要先找到插入节点的前一个节点，但问题是由于给定的参数是一个单独的节点
而并不是整个链表，因此寻找前驱节点就尤其麻烦，一个可行的方法便是通过遍历整个链表，来找到待插入节点的前驱节点

还有一种简单方法，可以想想象为后插节点，但是插入时交换数据域，即可实现前插操作，
这种方法实际上并没有真的在这个节点前插入一个新的节点，而是在节点后面插入。

这样实现使得插入前驱节点的操作时间复杂度降为O(1)，封装好之后便可直接在其他函数中调用
*/
int InsertPriorNode(LNode* p, int e){
    if (p == NULL) return false;
    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = p->data;
    p->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//此代码是有bug的，这种方法需要用到下一个节点，但当此节点就是链表中的最后一个节点时，再将next节点的data赋给自己就会出现空指针错误
//这也显现出了单链表的缺点，在代码开头补充
int DeleteNode(LNode* p){
    if (p == NULL) return false;
    p->data = p->next->data;
    p->next = p->next->next;
    return true;
}

LNode* GetElement(LinkList L, int i){
    if (i < 0) return NULL;
    int j = 0; //第j个节点
    LNode* p = L; 

    //按序获得链表元素，j需要到i相同的位置，所以while中时j<i，当j=i时便不再执行。
    while (p != NULL && j < i)
    {  
        p = p->next;
        j++;
    }
    return p;
    // int j = 0; //当前p指向的是第几个节点 因为p开始是指向头结点的，而头节点可以理解为第0个节点，但他并不是真正的节点，只是一个方便操作引入的虚拟节点，没有data域。
    // p = *L; //开始时指向头节点 这里的*同样是解引用操作，既获得L的内容，就是传入的参数的地址，由此便可以通过修改p的内容，修改L中的内容
    // while (p != NULL && j < i - 1){
    //     p = p->next;
    //     j++;
    // }
}

//按位序插入
//j的作用是找到第i个节点
int ListInsert(LinkList* L, int i, int e){
    if (i < 1) return false;

    LNode* p = GetElement(*L, i - 1); //p是第i个节点的前驱节点

    return InsertNextNode(p, e); //p传入的就是个指针，不需要取其地址
}

//不带头结点，不常用，相比于带头结点更加繁琐
//与带头结点不同的是，在第一个位置插入较为特殊,需要重新指定第一个元素，其他元素一致，不过j就要从1开始了
int ListInsert_Nohead(LinkList* L, int i, int e){
    if (i < 1) return false;
    if (i == 1){
        LNode* s = (LNode*)malloc(sizeof(LNode));
        s->data = e;
        s->next = *L; //s变成头
        *L = s; //将L重新指向s，这样就实现了第一个元素的插入。
        return true;
    }
    LNode *p; //p指向当前扫描到的节点
    int j = 1; //当前p指向的是第几个节点
    p = *L; //开始时指向头节点 这里的*同样是解引用操作，既获得L的内容，就是传入的参数的地址，由此便可以通过修改p的内容，修改L中的内容
    while (p != NULL && j < i - 1){
        p = p->next;
        j++;
    }
    //以上循环的目的是为了找到第i个节点的前驱节点，方便进行插入操作
    if (p == NULL) return false; //说明此时链表为空，连头节点都没有
    LNode* s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next; //这两个顺序不能颠倒，s链接后面的时候需要通过p的next链接，
    p->next = s; //如果先把p的next和s链接，会导致s找不到原来p之后的元素，这样原先p之后的元素就被丢失了
    //以上四条代码是在已经找到位置的前提下，进行数据的插入
    return true;
}

//按位序删除
int ListDelete(LinkList* L, int i, int *e){
    if (i < 1) return false;
    LNode* p;
    int j = 0;
    p = *L; //*是解引用作用，由于L是二次指针，所以*操作之后便是LinkList既头结点的地址，后续对p进行修改时便可直接作用于函数外部的参数

    //需要找到待删除节点的前驱节点
    //这是单链表的缺点，访问一个节点的前驱节点只能通过遍历的方式
    //双链表中直接可以使用piror指针域访问，循环单链表中也可以从这个节点以后进行遍历
    while (p != NULL && j < i - 1){
        p = p->next;
        j++;
    }
    *e = p->next->data;
    p->next = p->next->next;
    return true;
}

int ListDelete_Nohead(LinkList* L, int i, int *e){
    if (i < 1) return false;
    if (i == 1){
        LNode* s = (LNode*)malloc(sizeof(LNode));
        s = (*L)->next;
        *L = s;
        return true;    
    }
    LNode* p;
    int j = 1;
    p = *L; //*是解引用作用，由于L是二次指针，所以*操作之后便是LinkList的地址，后续对p进行修改时便可直接作用于函数外部的参数

    //找到待删除节点的前驱节点
    while (p != NULL && j < i - 1){
        p = p->next;
        j++;
    }
    *e = p->next->data;
    p->next = p->next->next;
    return true;
}

//按值查找，找到数据域为e的节点
LNode* LoacteElement(LinkList L, int e){
    LNode* p = L->next; //从第一个节点开始(带有头节点)
    while (p != NULL && p->data != e){
        p = p->next;
    }
    return p;
}

int GetLength(LinkList L){
    LNode* p = L;
    int len = 0;
    while (p->next != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
    
}


//尾插法建立单链表
/*
由于每次输入的数值都是插在尾节点后边的，所以插入后元素按原序排列；接下来要实现的头插法，将每次输入的元素插入到头节点，因此可以实现逆序排序。
这个算法的关键在于t时刻追踪L的尾节点，因为要记录每次循环的L的尾节点，因此本算法并没有复用指定节点后插入的方法
*/
LinkList List_TailInsert(LinkList* L){
    int x;
    // *L = (LinkList)malloc(sizeof(LNode));
    LNode *s, *t = *L; //t为尾指针，s为每次后插操作的插入节点 此赋值操作只将L赋给了t
    scanf("%d",&x);
    while (x != 666)
    {
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x; //将待插入的数值x赋给s的data域
        t->next = s; //将s插入到L后面。（因为t表示的是L的尾指针）
        t = s; //再次将t指向尾节点
        scanf("%d",&x);
    }
    t->next = NULL; //将最后尾节点的指空，防止出现未知错误
    return *L;
}

//头插法建立单链表
/*
由于已经实现了对单个节点的后插操作，所以只需要使用循环调用函数即可
头插法可以实现对一个序列的逆序排列，这在题目中经常出现
*/
LinkList List_HeadInsert(LinkList* L){
    LNode* Head = *L;
    int x;
    scanf("%d", &x);
    while (x != 666)
    {
        InsertNextNode(Head, x);
        scanf("%d", &x);
    }
    return *L;
}


//链表的逆序
/*
通过调用头插法，实现链表的逆序
*/
LinkList List_Reverse(LinkList *L){
    if (!(*L) || !(*L)->next) return *L;
    LNode* Head = (LNode*)malloc(sizeof(LNode));
    Head->next = NULL; //防止出现错误
    LNode* p = (*L)->next; //注意此时p不是从头节点开始的，而是从第一个节点开始，因为while循环中需要直接进行插入
    while (p != NULL)
    {
        InsertNextNode(Head, p->data);
        p = p->next;
    }
    return Head;
    
}
void printList(LinkList L, int signal){
    LNode *p;
    p = L;
    if (signal) p = p->next;
    while (p != NULL)
    {
        printf("%d\n",p->data);
        p = p->next;
    }
    
}

//第一题，递归删除所有值为x的节点(不带头节点)
void T1_Delete_Recursion(LinkList *L, int e){
    LNode *p = *L;
    if (p == NULL) return;
    if (p->data == e){
        *L = p->next;
        free(p);
        T1_Delete_Recursion(L, e);
    }
    else
        T1_Delete_Recursion(&((*L)->next), e);
}

int main(){
    int Del_1;
    LinkList L = NULL;
    InitList_NoHead(&L);
    ListInsert_Nohead(&L, 1, 2);
    ListInsert_Nohead(&L, 2, 3);
    ListInsert_Nohead(&L, 3, 2);
    ListInsert_Nohead(&L, 4, 10);
    ListInsert_Nohead(&L, 5, 2);
    ListInsert_Nohead(&L, 6, 6);
    // ListDelete(&L, 1, &Del_1);
    // printList(List_TailInsert(&L), 1);
    printList(L, 0);
    printf("==========\n");
    T1_Delete_Recursion(&L, 2);
    printList(L, 0);
    // printList(List_Reverse(&L), 1);
    // printf("%d\n",GetElement(L, 3)->data);
    // printf("%d\n",LoacteElement(L, 3)->data);
    // printf("%d\n",GetLength(L));
    system("pause");
    return 0;
}

