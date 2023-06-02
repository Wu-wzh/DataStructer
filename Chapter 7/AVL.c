#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int data;
    int balance; // 平衡因子
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

typedef AVLNode* AVLTree;

// 计算节点的高度
int Height(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = Height(node->left);
    int rightHeight = Height(node->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// 计算节点的平衡因子
int BalanceFactor(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return Height(node->left) - Height(node->right);
}

// 左旋操作
AVLNode* LeftRotate(AVLNode* node) {
    AVLNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    // 更新平衡因子
    node->balance = BalanceFactor(node);
    newRoot->balance = BalanceFactor(newRoot);
    return newRoot;
}

// 右旋操作
AVLNode* RightRotate(AVLNode* node) {
    AVLNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    // 更新平衡因子
    node->balance = BalanceFactor(node);
    newRoot->balance = BalanceFactor(newRoot);
    return newRoot;
}

// 插入操作
AVLNode* Insert(AVLNode* root, int key) {
    if (root == NULL) {
        AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
        newNode->data = key;
        newNode->balance = 0;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->data) {
        root->left = Insert(root->left, key);
    } else if (key > root->data) {
        root->right = Insert(root->right, key);
    } else {
        // 若已存在相同节点，则不进行插入操作
        return root;
    }

    // 更新平衡因子
    root->balance = BalanceFactor(root);

    // 平衡维护
    if (root->balance > 1) {
        if (key < root->left->data) {
            // LL型，进行右旋操作
            root = RightRotate(root);
        } else if (key > root->left->data) {
            // LR型，先左旋后右旋
            root->left = LeftRotate(root->left);
            root = RightRotate(root);
        }
    } else if (root->balance < -1) {
        if (key > root->right->data) {
            // RR型，进行左旋操作
            root = LeftRotate(root);
        } else if (key < root->right->data) {
            // RL型，先右旋后左旋
            root->right = RightRotate(root->right);
            root = LeftRotate(root);
        }
    }

    return root;
}

// 中序遍历
void InOrder(AVLNode* root) {
    if (root != NULL) {
        InOrder(root->left);
        printf("%d\n", root->data);
        InOrder(root->right);
    }
}

int main() {
    AVLNode* root = NULL;
    int keys[] = {50, 66, 60, 26, 21, 30, 70, 68};
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < numKeys; i++) {
        root = Insert(root, keys[i]);
    }

    InOrder(root);

    system("pause");
    return 0;
}
