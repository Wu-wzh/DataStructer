#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0

typedef struct AVLNode
{
    int data;
    int balance; //平衡二叉树的平衡因子
    struct AVLNode *left, *right;
}AVLNode, *AVLTree;

//中序遍历
void InOrder(AVLTree T){
    if (T != NULL){
        InOrder(T->left);
        printf("%d\n", T->data);
        InOrder(T->right);
    }
}
//二叉排序树实现，返回BSTNode的指针
//非递归查找空间复杂度为O(1)
AVLNode *BST_Search(AVLTree T, int key){
    AVLNode *p = T;
    while (p != NULL && key != p->data){
        if (key < p->data) p = p->left; //若此节点小于key，由二叉排序树的定义，向此节点的左树寻找
        else p = p->right; //否则向右树寻找
    }
    return T;
}

//递归查找 空间复杂度为O(h)
AVLNode *BST_Search_R(AVLTree T, int key){}

//平很二叉树的插入操作，按照普通二叉排序树的插入之后，会使得二叉树不再平衡，因此需要再进一步将树平衡化

//递归实现
int BST_Insert(AVLTree *T, int key){
    if ((*T) == NULL){
        (*T) = (AVLTree)malloc(sizeof(AVLNode));
        (*T)->data = key;
        (*T)->left = (*T)->right = NULL;
        return 1;
    }
    else if ((*T)->data == key) return 0; //二叉排序树中已经存在了此节点
    else if (key < (*T)->data) return BST_Insert(&((*T)->left), key); //key小于此节点，应该在此节点的左孩子插入
    else if (key > (*T)->data) return BST_Insert(&((*T)->right), key); //key大于此节点，应该在此节点的右孩子插入
}

//二叉树的删除过程，相比于插入操作更为复杂，需要区分多个情况
/*
1.待删除结点是叶子节点，直接删除即可
2.待删除结点只有一颗左子树或右子树，删除此节点之后让其子树的根节点替代自己
3.待删除结点即有左子树又有右子树，最复杂，有多种策略，后续学习平衡二叉树之后，会有最好的策略。
①找到此节点右子树中最小的节点（最左边）
②找到此节点左子树中最大的节点（最右边）
*/

//二叉排序树的建立过程，对str的数据逐一进行插入操作
void Create_BST(AVLTree *T, int str[], int n){
    (*T) = NULL;
    int i = 0;
    while (i < n){
        BST_Insert(T, str[i]);
        i++;
    }
}
//从以上的二叉排序树的建立过程可以看出，查询操作的时间复杂度取决于二叉排序树的高度，因此如何让二叉排序数的查找速度更快，
//即让树变得更加"平衡"，由此有了平衡二叉树的概念。
int main(){
    AVLTree T;
    int str[8] = {50, 66, 60, 26, 21, 30, 70, 68};
    Create_BST(&T, str, 8);
    InOrder(T);
    system("pause");
    return 0; 
}