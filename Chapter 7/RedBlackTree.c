#include <stdio.h>
#include <stdlib.h>

// 红黑树节点颜色枚举
typedef enum {
    RED,
    BLACK
} Color;

// 红黑树节点结构体
typedef struct RBNode {
    int data;
    Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
} RBNode;

// 红黑树结构体
typedef struct {
    RBNode* root;
    RBNode* nil; // 哨兵节点，用于表示空节点
} RBTree;

// 创建红黑树节点
RBNode* createNode(int data, Color color, RBNode* nil) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = color;
    node->left = nil;
    node->right = nil;
    node->parent = nil;
    return node;
}

// 初始化红黑树
void initRBTree(RBTree* tree) {
    RBNode* nil = createNode(0, BLACK, NULL);
    tree->root = nil;
    tree->nil = nil;
}

// 左旋操作
void leftRotate(RBTree* tree, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != tree->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == tree->nil) {
        tree->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// 右旋操作
void rightRotate(RBTree* tree, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right != tree->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == tree->nil) {
        tree->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// 红黑树修正操作
void rbInsertFixup(RBTree* tree, RBNode* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// 插入节点到红黑树
void rbInsert(RBTree* tree, int data) {
    RBNode* z = createNode(data, RED, tree->nil);
    RBNode* y = tree->nil;
    RBNode* x = tree->root;
    while (x != tree->nil) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == tree->nil) {
        tree->root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;
    rbInsertFixup(tree, z);
}

// 在红黑树中查找指定值
RBNode* rbSearch(RBTree* tree, int data) {
    RBNode* x = tree->root;
    while (x != tree->nil && x->data != data) {
        if (data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    return x;
}

// 红黑树删除修正操作
void rbDeleteFixup(RBTree* tree, RBNode* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

// 删除红黑树节点
void rbDelete(RBTree* tree, RBNode* z) {
    RBNode* x;
    RBNode* y = z;
    Color originalColor = y->color;
    if (z->left == tree->nil) {
        x = z->right;
        rbTransplant(tree, z, z->right);
    } else if (z->right == tree->nil) {
        x = z->left;
        rbTransplant(tree, z, z->left);
    } else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (originalColor == BLACK) {
        rbDeleteFixup(tree, x);
    }
    free(z);
}

// 删除红黑树中的指定值
void rbRemove(RBTree* tree, int data) {
    RBNode* z = rbSearch(tree, data);
    if (z != tree->nil) {
        rbDelete(tree, z);
    }
}

// 递归销毁红黑树节点
void destroyRBTreeRecursive(RBNode* node, RBNode* nil) {
    if (node != nil) {
        destroyRBTreeRecursive(node->left, nil);
        destroyRBTreeRecursive(node->right, nil);
        free(node);
    }
}

// 销毁红黑树
void destroyRBTree(RBTree* tree) {
    destroyRBTreeRecursive(tree->root, tree->nil);
    free(tree->nil);
    tree->root = NULL;
    tree->nil = NULL;
}



// 中序遍历红黑树
void inorderTraversal(RBNode* node, RBNode* nil) {
    if (node != nil) {
        inorderTraversal(node->left, nil);
        printf("%d ", node->data);
        inorderTraversal(node->right, nil);
    }
}

int main() {
    RBTree tree;
    initRBTree(&tree);

    rbInsert(&tree, 10);
    rbInsert(&tree, 20);
    rbInsert(&tree, 30);
    rbInsert(&tree, 40);
    rbInsert(&tree, 50);

    printf("Inorder traversal of the tree: ");
    inorderTraversal(tree.root, tree.nil);
    printf("\n");

    rbRemove(&tree, 30);

    printf("Inorder traversal after removing 30: ");
    inorderTraversal(tree.root, tree.nil);
    printf("\n");

    destroyRBTree(&tree);

    system("pause");
    return 0;
}
