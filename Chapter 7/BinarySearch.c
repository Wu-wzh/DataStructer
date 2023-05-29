//二分查找，只适用于有序顺序表的查找 用两个指针不断进行缩小，每次缩小为原来的二分之一
//查找判定树ASL(平均查找长度)计算 其判定树是一个平衡二叉排序树

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define InitSize 11
#define true 1
#define false 0

typedef struct{
    int *data;
    int length;
}SSTable;

void InitList(SSTable* L){
    L->data = (int*)malloc(InitSize * sizeof(int));
    for  (int i = 0; i < InitSize; i++)
        L->data[i] = 0;
    L->length = 0;
}

int ListInsert(SSTable *L, int i, int e){
    if (i < 1 || i > L->length + 1) {
        printf("Invalid Number!!\n");
        return false;
    }
    for (int j = L->length; j >= i; j--)
        L->data[j] = L->data[j - 1];
    L->data[i - 1] = e;
    L->length++;
    return true;
}

int CreateTable(SSTable *S){
    printf("输入顺序查找表内容(有序表,以666为结束)：\n");
    int x, i = 0;
    scanf("%d", &x);
    while (x != 666){
        S->data[i++] = x;
        S->length++;
        scanf("%d", &x);
    }
}

int Search_Binary(SSTable L, int key){
    //初始化两个指针分别为第一个和最后一个元素，并且声明low和high的中间指针
    int low = 0, high = L.length - 1, mid;
    while (low <= high){
        mid = (high + low) / 2; //int型将进行整除
        if (key == L.data[mid]) return mid; //若找到了key的位置，直接返回mid值
        else if (key < L.data[mid]) //待查找在中间元素的后面，则更新high值为mid - 1
            high = mid - 1;
        else low = mid + 1; //待查找在中间元素的前面，则更新low值为mid + 1
    }
    //遍历完成后都没有找到符合条件的mid值，说明没找到，返回-1
    return -1;
} //要注意二分查找必须是顺序表，且为升序排列，其时间复杂度为O(log2n),可以看到，算法的时间复杂度很好

int main(){
    SSTable S;
    InitList(&S);
    CreateTable(&S);
    printf("%d\n", Search_Binary(S, 44));
    system("pause");
    return 0;
}