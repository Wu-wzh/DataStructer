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

int main(){
    BiTree T;
    InitTree(&T);
    CreateTree(&T);
    PreOrder(T);
    system("pause");
    return 0;
}