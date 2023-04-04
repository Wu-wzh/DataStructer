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

//栈的实现

typedef struct LinkNode{
    struct BiNode* node;
    struct LinkNode* next;
}LinkNode, *LStatic;

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
    l->node = (BiNode*)T;
    l->next = (*S)->next;
    (*S)->next = l;
    return true;
}

BiNode* Pop(LStatic* S){
    if ((*S)->next == NULL) return false;
    BiNode *t;
    LinkNode* p = (*S)->next;
    t = (BiNode*)p->node;
    (*S)->next = p->next;
    free(p);
    return t;
}

BiNode* GetTop(LStatic S){
    BiNode* t;
    if (S->next == NULL) return false;
    t = (BiNode*)S->next->node;
    return t;
}

int Empty(LStatic L){
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

    BiNode *s = T;
    //将所有的左子树入栈
    while (s != NULL)
    {
        printf("%d\n",s->data);
        Push(&L, s);
        s = s->left;
    }

    //对右子树进行同样的策略，直到链栈为空
    while (!Empty(L))
    {
        BiNode* top = GetTop(L);
        BiNode* t = top->right;
        Pop(&L);
        while (t != NULL)
        {
            printf("%d\n",t->data);
            Push(&L, t);
            t = t->left;
        }
    }
    

    // printStack(L);

}

//中序遍历
void InOrder(BiTree T){
    if (T != NULL){
        PreOrder(T->left);
        printf("%d\n", T->data);
        PreOrder(T->right);
    }
}
//非递归实现的前序遍历
void InOrder_NoRecursion(BiTree T){
    LStatic L;
    InitStack(&L);

    if (T == NULL) return;

    BiNode *s = T;
    //将所有的左子树入栈
    while (s != NULL)
    {
        Push(&L, s);
        s = s->left;
    }

    //对右子树进行同样的策略，直到链栈为空
    while (!Empty(L))
    {
        BiNode* top = GetTop(L);
        BiNode* t = top->right;
        BiNode* x = Pop(&L);
        printf("%d\n",x->data);
        while (t != NULL)
        {
            Push(&L, t);
            t = t->left;
        }
    }
    

    // printStack(L);

}
//后序遍历
void PostOrder(BiTree T){
    if (T != NULL){
        PreOrder(T->left);
        PreOrder(T->right);
        printf("%d\n", T->data);
    }
}



int main(){
    BiTree T;
    InitTree(&T);
    CreateTree(&T);
    // printf("前序遍历：\n");
    InOrder_NoRecursion(T);
    // printf("中序遍历：\n");
    // InOrder(T);
    // printf("后序遍历：\n");
    // PostOrder(T);
    system("pause");
    return 0;
}