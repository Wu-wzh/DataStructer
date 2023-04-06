//满二叉树，完全二叉树（高频考点），平衡二叉树是对形状有要求的树，完全二叉树其实是满二叉树的子集
//二叉排序树是一种节点有要求的树，若二叉排序树越接近平衡二叉树，则搜索效率越高

#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0

typedef struct node
{
    int data;
    struct node *left, *right;
}BiNode, *BiTree;

void InitTree(BiTree *T){
    (*T) = NULL;
}



//栈的结构体
typedef struct LinkNode{
    struct BiNode* node;
    struct LinkNode* next;
}LinkNode, *LStatic;

//队列结构体
typedef struct LinkQueue{
    LinkNode *front, *tail;
}LinkQueue;

//栈的实现
//带头结点
int InitStack(LStatic* S){
    *S = (LinkNode*) malloc(sizeof(LinkNode));
    if (*S == NULL) return false;
    (*S)->next = NULL;
    return true;
}

int Push(LStatic* S, BiNode* T){ 
    if (*S == NULL) return false;
    LinkNode* l = (LinkNode*)malloc(sizeof(LinkNode));
    l->node = (struct BiNode*)T;
    l->next = (*S)->next;
    (*S)->next = l;
    return true;
}

int Pop(LStatic* S, BiNode** p){
    if ((*S)->next == NULL) return false;
    LinkNode* n = (*S)->next;
    (*p) = (BiNode*)n->node;
    (*S)->next = n->next;
    free(n);
    return true;
}

int GetTop(LStatic S, BiNode** t){
    if (S->next == NULL) return false;
    (*t) = (BiNode*)S->next->node;
    return true;
}

int Empty_Stack(LStatic L){
    return L->next == NULL;
}
void printStack(LStatic S){
    LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
    t = S->next;
    while (t != NULL)
    {
        //先要初始化，不能直接用t->node->data
        BiNode* x = (BiNode*)t->node;
        printf("%d\n",x->data);
        t = t->next;
    }
    
}

//队列的实现
int InitQueue(LinkQueue *Q){
    Q->front = Q->tail = (LinkNode*)malloc(sizeof(LinkNode));
    Q->front->next = NULL;
    return true;
}
//入队操作
void EnQueue(LinkQueue *Q, BiNode* t){
    LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
    p->node = (struct BiNode*)t;
    p->next = NULL;
    Q->tail->next = p;
    Q->tail = p;
}
//出队操作
int DeQueue(LinkQueue *Q, BiNode** x){
    if (Q->front == Q->tail) return false;
    LinkNode *p = Q->front->next;
    (*x) = (BiNode*)p->node;
    Q->front->next = p->next;
    if (p == Q->tail) Q->front = Q->tail;
    p = NULL;
    free(p);
    return true;
}
int isEmpty_Queue(LinkQueue Q){
    if (Q.front == Q.tail) return true;
    else return false;
}
void printQueue(LinkQueue Q){
    LinkNode *p = Q.front;
    while (p->next != NULL){
        BiNode* t = (BiNode*)p->node;
        printf("%d<-", t->data);
        p = p->next;
    }
    printf("end\n");
}


//访问一个树节点
void vist(BiNode* p){
    if (p == NULL) return;
    else printf("%d\n", p->data);
}

//使用二级指针建立树
void CreateTree(BiTree *T){
    int data;
    scanf("%d", &data);
    if (data < 0) (*T) = NULL;
    //进行递归调用
    else{
        (*T) = (BiTree)malloc(sizeof(BiNode));
        (*T)->data = data;
        CreateTree(&((*T)->left));
        CreateTree(&((*T)->right));
    }
}

//不使用二级指针，使用返回值的方式创建
BiTree CreateTree_1(BiTree T){
    int data;
    scanf("%d", &data);
    if (data < 0) return NULL;
    //进行递归调用
    else{
        T = (BiTree)malloc(sizeof(BiNode));
        T->data = data;
        T->left = CreateTree_1(T->left);
        T->right = CreateTree_1(T->right);
    }
    return T;
}


//前序遍历
void PreOrder(BiTree T){
    if (T != NULL){
        printf("%d\n", T->data);
        PreOrder(T->left);
        PreOrder(T->right);
    }
}

//非递归实现的前序遍历
void PreOrder_NoRecursion(BiTree T){
    LStatic L;
    InitStack(&L);

    if (T == NULL) return;

    BiNode *p = T;
    while (p || !Empty_Stack(L))
    {
        if (p)
        {
            Push(&L, p);
            vist(p);
            p = p->left;
        }
        else{
            Pop(&L, &p);
            p = p->right;
        }
        
    }
}
//中序遍历
void InOrder(BiTree T){
    if (T != NULL){
        PreOrder(T->left);
        printf("%d\n", T->data);
        PreOrder(T->right);
    }
}
//非递归实现的中序遍历
void InOrder_NoRecursion(BiTree T){
    LStatic L;
    InitStack(&L);

    if (T == NULL) return;

    BiNode *p = T;
    while (p || !Empty_Stack(L))
    {
        if (p)
        {
            Push(&L, p);
            p = p->left;
        }
        else{
            Pop(&L, &p);
            vist(p);
            p = p->right;
        }
        
    }

}
//后序遍历
void PostOrder(BiTree T){
    if (T != NULL){
        PreOrder(T->left);
        PreOrder(T->right);
        printf("%d\n", T->data);
    }
}
//非递后续遍历
void PostOrder_NoRecursion(BiTree T){
    LStatic L;
    InitStack(&L);
    BiNode *p = T; 
    BiNode *r = NULL;//可以理解为初始化叶子节点的右节点为null
    //p为遍历节点,r为记录当前节点右孩子的辅助节点
    while (p || !Empty_Stack(L))
    {
        if (p){ //走到最左边
            Push(&L, p);
            p  = p->left;
        }
        else{
            //先不着急出栈，需要判读栈顶元素的右节点是否被访问过，访问过之后才进行出栈
            GetTop(L, &p);
            if (p->right && p->right != r)  p = p->right; //若p的右节点不为空或者未被访问过，先不进行出栈，向右子树寻找可以出栈的值
            else{
                Pop(&L, &p);
                vist(p);
                r = p; //r赋值为p，保存p节点信息，若后续判断是否出栈时，上次保存的r一定是新p的右孩子
                p = NULL;//直接进入第一个else分支
                //p必须要赋空，若不赋空，会导致同一个节点多次入栈
                //因为在前序和中序遍历中，else中都执行了取右孩子操作，但此else分支中的else分支，并没有进行取右节点操作
            }
        }
    }
    
}

//层序遍历(使用队列)
void LevelOrder(BiTree T){
    LinkQueue Q;

    InitQueue(&Q);
    BiNode* p = T;
    EnQueue(&Q, p);//入队没问题
    while (!isEmpty_Queue(Q))
    {
        DeQueue(&Q, &p);//出队没指向null！！
        vist(p);
        if (p->left != NULL){
            EnQueue(&Q, p->left);
        }
        if (p->right != NULL){
            EnQueue(&Q, p->right);
        } 
        // printQueue(Q);
    }
    
}

int main(){
    BiTree T;
    InitTree(&T);
    CreateTree(&T);
    printf("前序遍历：\n");
    // PreOrder(T);
    PreOrder_NoRecursion(T);
    printf("中序遍历：\n");
    // InOrder(T);
    InOrder_NoRecursion(T);
    printf("后序遍历：\n");
    // PostOrder(T);
    PostOrder_NoRecursion(T);
    printf("层次遍历：\n");
    LevelOrder(T);
    system("pause");
    return 0; 
}