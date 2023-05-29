//满二叉树，完全二叉树（高频考点），平衡二叉树是对形状有要求的树，完全二叉树其实是满二叉树的子集
//二叉排序树是一种节点有要求的树，若二叉排序树越接近平衡二叉树，则搜索效率越高

/*一种给定遍历序列(除中序序列外)，确定该序列有多少种形状的方法：
将已知序列看作入栈顺序，有卡特兰数种出栈顺序，可将这些出栈顺序看作一个中序序列，由此一种顺序对应一种形状的数（中序序列和其他序列唯一确定颗树）
所以共有(1 / n) * 2n和n的组合数
对给定中序序列，出栈视为随便一种其他遍历方式，结果同上
*/

#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0

typedef struct AVLNode
{
    int data;
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

//二叉排序树是一种动态的查找，可以进行数据的插入和删除，现在不考虑插入和删除的平衡化

//二叉树的插入操作，若可以插入，则插入的节点必定为叶子节点，因此实现过程也比较简单
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