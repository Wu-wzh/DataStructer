#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0

//线索二叉树，利用栈存储结构，利用空域，保存当前节点的前驱节点和后继节点
//可以更快的访问前驱和后继，以及从任意一个节点开始遍历
//三种线索二叉树的构造本质上是对三种深度遍历算法的改造，让树更好的进行操作
typedef struct node
{
    int data;
    struct node *left, *right;
    int ltag, rtag;
}ThreadNode, *ThreadTree;

//定义三个全局变量，用来线索化
ThreadNode *p; //待线索化的节点
ThreadNode *pre = NULL; //寻找过程中记录的前驱节点
ThreadNode *final = NULL; //p节点的前驱节点

//使用二级指针建立树
void CreateTree(ThreadTree *T){
    int data;
    scanf("%d", &data);
    if (data < 0) (*T) = NULL;
    //进行递归调用
    else{
        (*T) = (ThreadNode*)malloc(sizeof(ThreadNode));
        (*T)->data = data;
        (*T)->ltag =0;
        (*T)->rtag =0;
        CreateTree(&((*T)->left));
        CreateTree(&((*T)->right));
    }
}

void vist(ThreadNode* p){
    if (p == NULL) return;
    else printf("%d\n", p->data);
}

//其本质上就是一个遍历过程，在普通二叉树的vist过程中，添加记录前后继节点并更新tag值的操作
void InThread(ThreadTree *T, ThreadNode **pre){
    //由于在主函数中调用时，pre需要传入函数之后再传出时进行改变，因此使用二次指针
    ThreadNode *t = *T;
    if (t != NULL){
        InThread(&(t->left), pre); //递归访问左子树



        //一下代码段对应遍历过程中的vist操作，但是不再是打印该节点，而是进行了线索的建立和pre的更新操作
        if (t->left == NULL){
            t->left = *pre;
            t->ltag = 1;
        } //此次访问的左孩子为空，则说明找到了需要进行线索化的元素，将此元素的左孩子指针指向上次访问的节点，既为它的前驱节点
        if ((*pre) != NULL && (*pre)->right == NULL){  //&&的性质，若前面不满足，不会判断后面，所以不用担心pre为null导致发生错误！！
            (*pre)->right = t;
            (*pre)->rtag = 1;
        }//若上次访问的pre节点不是空，并且pre的右孩子是空，则这次访问的元素为pre的后继节点，进行赋值操作
        //执行完基本的操作之后，为下一次操作做准备
        //首先对pre进行更新
        *pre = t;



        InThread(&(t->right), pre);//递归访问右子树
    }
} //要注意这个过程不是对称的，可以实现对一个节点进行线索化，但不能实现对最后一个节点的线索化，因此在主函数中调用的时候，需要对最后一个节点进行特殊处理


void CreateInThread(ThreadTree *T){
    ThreadNode * pre = NULL;
    if (T != NULL){
        InThread(T, &pre);
        //对最后一个节点进行特别处理
        /*要注意此时pre指向的是中序遍历的最后一个节点，这个节点一定是叶子节点，
        也就是一定没有右孩子，所以不需要判断右孩子是否为空，直接将右孩子赋值为null就可以*/
        pre->right = NULL;
        pre->rtag = 1;
    }
}


//其本质上就是一个遍历过程，在普通二叉树的vist过程中，添加记录前后继节点并更新tag值的操作
void PreThread(ThreadTree *T, ThreadNode **pre){
    //由于在主函数中调用时，pre需要传入函数之后再传出时进行改变，因此使用二次指针
    ThreadNode *t = *T;
    if (t != NULL){
        
        //一下代码段对应遍历过程中的vist操作，但是不再是打印该节点，而是进行了线索的建立和pre的更新操作
        if (t->left == NULL){
            t->left = *pre;
            t->ltag = 1;
        } //此次访问的左孩子为空，则说明找到了需要进行线索化的元素，将此元素的左孩子指针指向上次访问的节点，既为它的前驱节点
        if ((*pre) != NULL && (*pre)->right == NULL){  //&&的性质，若前面不满足，不会判断后面，所以不用担心pre为null导致发生错误！！
            (*pre)->right = t;
            (*pre)->rtag = 1;
        }//若上次访问的pre节点不是空，并且pre的右孩子是空，则这次访问的元素为pre的后继节点，进行赋值操作
        //执行完基本的操作之后，为下一次操作做准备
        //首先对pre进行更新
        *pre = t;
        //现在vist到了前面，前序遍历


        if (t->ltag == 0) PreThread(&(t->left), pre); 
        /*递归访问左子树,要注意访问左右子树和vist操作的顺序问题，在中序和后序线索化时，由于访问左子树始终再vist操作前
        因此不可能出现对节点进行vist操作之后接着进行该节点的左子树遍历，
        但前序遍历不同，他是有可能进行vist操作之后，继续访问自己的左子树的，但是由于进行vist操作之后，此节点的左孩子有可能指向了自己的前驱节点
        这样就造成了两个节点之间一直重复访问，因此需要用到ltag标识符，看看这个节点的左孩子现在是真正的左孩子还是他的前驱节点，只有在是真正的左孩子时才进行左子树的访问*/
        PreThread(&(t->right), pre);//递归访问右子树
    }
} //要注意这个过程不是对称的，可以实现对一个节点进行线索化，但不能实现对最后一个节点的线索化，因此在主函数中调用的时候，需要对最后一个节点进行特殊处理


void CreatePreThread(ThreadTree *T){
    ThreadNode * pre = NULL;
    if (T != NULL){
        PreThread(T, &pre);
        //对最后一个节点进行特别处理
        /*要注意此时pre指向的是前序遍历的最后一个节点，这个节点不一定是叶子节点，
        所以需要判断最后一个节点的右孩子是否为空，当右孩子为空右孩子赋值为null就可以*/
        if (pre->right == NULL){
            pre->right = NULL;//可以不加这条，加上是为了为了和中序保持统一
            pre->rtag = 1;  
        }
        
    }
}



void PostThread(ThreadTree *T, ThreadNode **pre){
    //由于在主函数中调用时，pre需要传入函数之后再传出时进行改变，因此使用二次指针
    ThreadNode *t = *T;
    if (t != NULL){
        
        PostThread(&(t->left), pre); //递归访问左子树

        PostThread(&(t->right), pre);//递归访问右子树



        //一下代码段对应遍历过程中的vist操作，但是不再是打印该节点，而是进行了线索的建立和pre的更新操作
        if (t->left == NULL){
            t->left = *pre;
            t->ltag = 1;
        } //此次访问的左孩子为空，则说明找到了需要进行线索化的元素，将此元素的左孩子指针指向上次访问的节点，既为它的前驱节点
        if ((*pre) != NULL && (*pre)->right == NULL){  //&&的性质，若前面不满足，不会判断后面，所以不用担心pre为null导致发生错误！！
            (*pre)->right = t;
            (*pre)->rtag = 1;
        }//若上次访问的pre节点不是空，并且pre的右孩子是空，则这次访问的元素为pre的后继节点，进行赋值操作

        //执行完基本的操作之后，为下一次操作做准备
        //首先对pre进行更新
        *pre = t;
        //现在vist到了最后面，后序遍历
    }
} //要注意这个过程不是对称的，可以实现对一个节点进行线索化，但不能实现对最后一个节点的线索化，因此在主函数中调用的时候，需要对最后一个节点进行特殊处理


void CreatePostThread(ThreadTree *T){
    ThreadNode * pre = NULL;
    if (T != NULL){
        PostThread(T, &pre);
        //对最后一个节点进行特别处理
        /*要注意此时pre指向的是后序遍历的最后一个节点，这个节点不一定是叶子节点，
        所以需要判断最后一个节点的右孩子是否为空，当右孩子为空右孩子赋值为null就可以*/
        if (pre->right == NULL){
            pre->right = NULL;//可以不加这条，加上是为了为了和中序保持统一
            pre->rtag = 1;  
        }
        
    }
}

//==============================================================================//
//==============================================================================//
//==============================================================================//

//中序线索二叉树的遍历

//首先封装两个重要函数，求特定节点的前驱和求前驱遍历的第一个节点，有了线索树之后，便不用每次进行遍历这么复杂寻找了
ThreadNode *InFirstNode(ThreadNode *p){
    while (p->ltag == 0) p = p->left;
    return p;
}
//获取第一个遍历节点在三种遍历方式中都不一样

ThreadNode *InNextNode(ThreadNode *p){

    //若右节点不是后继节点，则寻找右子树中第一个访问的元素，即为此节点的后继节点
    //而寻找右子树第一个访问的元素便可调用上面的FirstNode函数
    if (p->rtag == 0) return InFirstNode(p->right);

    //若右节点就是后继节点，直接返回即可
    else return p->right;
}

//封装玩上面两个函数之后，便可以通过一个for循环，从第一个遍历节点开始
//，不断调用nextnode函数，直到p为空(遍历最后的元素是右指针必为空，上文已经解释过为什么)。
void InOrder(ThreadNode *T){
    for (ThreadNode* p = InFirstNode(T); p != NULL; p = InNextNode(p))
        vist(p);
}

//按照相同的逻辑实现中序线索二叉树逆向的遍历
ThreadNode *InLastNode(ThreadNode *p){
    while (p->rtag == 0) p = p->right;
    return p;
}
//获取第一个遍历节点在三种遍历方式中都不一样

ThreadNode *InPreNode(ThreadNode *p){

    //若右节点不是后继节点，则寻找右子树中第一个访问的元素，即为此节点的后继节点
    //而寻找右子树第一个访问的元素便可调用上面的FirstNode函数
    if (p->ltag == 0) return InLastNode(p->left);

    //若右节点就是后继节点，直接返回即可
    else return p->left;
}

//封装玩上面两个函数之后，便可以通过一个for循环，从第一个遍历节点开始
//，不断调用nextnode函数，直到p为空(遍历最后的元素是右指针必为空，上文已经解释过为什么)。
void RevInOrder(ThreadNode *T){
    for (ThreadNode* p = InLastNode(T); p != NULL; p = InPreNode(p))
        vist(p);
}



//==============================================================================//
//==============================================================================//
//==============================================================================//



//先序线索二叉树的遍历

//先序遍历的第一个节点一定是根节点，因此不需要编写FirstNode函数

//寻找先序线索化之后的指定节点的后继节点
ThreadNode *PreNextNode(ThreadNode *p){

    //若右节点就是后继节点，直接返回即可
    if (p->rtag == 1)
        return p->right;
    else{
        if (p->left == NULL) return p->right;
        else return p->left;
    }

}

void PreOrder(ThreadNode *T){
    for (ThreadNode* p = T; p != NULL; p = PreNextNode(p))
        vist(p);
}


//寻找先序遍历的最后一个节点，就是遍历一遍先序线索二叉树
ThreadNode *PreLastNode(ThreadNode *p){
    while (p->rtag == 0) p = p->right;
    return p;
}

//现实先序线索树的任意节点的前驱节点，用当前存储结构需要遍历整个树，
//可通过添加一个前驱指针来解决这一问题
// ThreadNode *PrePreNode(ThreadNode *p){}



//==============================================================================//
//==============================================================================//
//==============================================================================//



//后续线索二叉树的遍历

//寻找指定节点的后继节点

//同样难以查找，需要遍历整个树，考虑用三叉链表实现
// ThreadNode *PostNextNode(ThreadNode *p){}

//找前驱比较简单

ThreadNode *PostPreNode(ThreadNode *p){
    if (p->ltag == 1) return p->left;

    //若左节点就是前驱节点，直接返回即可
    else{
        if (p->right != NULL) return p->right;
        else return p->left;
    }
}

//封装玩上面两个函数之后，便可以通过一个for循环，从第一个遍历节点开始
//，不断调用nextnode函数，直到p为空(遍历最后的元素是右指针必为空，上文已经解释过为什么)。

//逆序输出后序遍历结果，从最后一个节点既根节点开始
void RevPostOrder(ThreadNode *T){
    for (ThreadNode* p = T; p != NULL; p = PostPreNode(p))
        vist(p);
}



int main(){
    ThreadTree T;
    CreateTree(&T);
    // CreateInThread(&T);
    // CreatePreThread(&T);
    CreatePostThread(&T);
    // InOrder(T);
    // PreOrder(T);
    RevPostOrder(T);
    printf("==============\n");
    // RevInOrder(T);
    system("pause");
    return 0;
}