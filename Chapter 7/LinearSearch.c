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
    
    printf("输入顺序查找表内容(以666为结束)：\n");
    int x, i = 1;
    scanf("%d", &x);
    while (x != 666){
        S->data[i++] = x;
        scanf("%d", &x);
    }

}

int Search_Seq(SSTable *L, int key){
    L->data[0] = key;
    int i;
    for (i = L->length; L->data[i] != key; --i) //无步骤循环，仅仅找到i
    return i;
}
/*两种优化 ：
1、有序表中可以优化查找策略，减少查找成功的时间复杂度
2、有序表中元素的概率不同，将概率高的放在查找前面，减少查找失败的时间复杂度
两种优化方法要根据问题中查找成功的情况多还是查找失败的情况多
*/
int main(){
    SSTable L;
    InitList(&L);
    CreateTable(&L);
    printf("%d\n", Search_Seq(&L, 66));
    system("pause");
    return 0;
}