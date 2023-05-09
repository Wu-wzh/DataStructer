#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define InitSize 11
#define true 1
#define false 0
#define TableLength 5


//索引表结构体
typedef struct{
    int maxvalue;
    int low, high;
} Index, IndexTable[TableLength];

void InitTable(IndexTable **T){  //修改函数参数类型为 IndexTable**
    int k = 10;
    for (int i = 0; i < TableLength; i++){
        (*T)[i]->maxvalue = k;   //通过指针修改 IndexTable 中的元素
        (*T)[i]->low = 0;
        (*T)[i]->high = 0;
        k+=10;
    }
}


int CreateTable(IndexTable *T){
    int List[14] = {7,10,13,19,16,20,27,22,30,40,36,43,50,48};
    T[0]->low = 0;
    T[0]->high = 1;

    T[1]->low = 2;
    T[1]->high = 5;

    T[2]->low = 6;
    T[2]->high = 8;

    T[3]->low = 9;
    T[3]->high = 10;
    
    T[4]->low = 11;
    T[4]->high = 13;
} 
//块内无序，但是块间有序，用这种分块的方法可以让得到块间的有序序列，
//从而使用时间复杂度低的算法先对块间进行查找，若找到符合的块则进入块内进行顺序查找

int Search_Block_Binary(IndexTable *T, int key){
    int List[14] = {7,10,13,19,16,20,27,22,30,40,36,43,50,48};

    int low = 0, high = 4, mid;
    while (low <= high){
        mid = (low + high) / 2;
        if (key == T[mid]->maxvalue) //若找到了key的位置
            for (int i = T[mid]->low; i <= T[mid]->high; i++)
                if (key == List[i]) return i;

        else if (key < T[mid]->maxvalue) //待查找在中间元素的后面，则更新high值为mid - 1
            high = mid - 1;
    
        else low = mid + 1; //待查找在中间元素的前面，则更新low值为mid + 1
    }

    //完了之后并不是结束，可以验证若可以查找到，必在结束循环后low所在的索引表对应的元素中
    for (int i = T[i]->low; i <= T[i]->high; i++)
                if (key == List[i]) return i;
    return -1;    
}

int main(){
    IndexTable *T;
    T = (IndexTable*)malloc(sizeof(Index) * 5);
    InitTable(&T);
    CreateTable(&T); //仅仅为特例，为实现任意顺序表创建索引表
    printf("%d\n", Search_Block_Binary(T, 19));
    system("pause");
    return 0;
}