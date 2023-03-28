#include <stdio.h>
#include <windows.h>
#define MaxSize 10
typedef struct{
    //two attribute ,one data of seqlist ,anotherlength now;
    int data[MaxSize]; 
    int length;
}SeqList;

//Initional data with 0
void InitList(SeqList *L){
    for (int i = 0; i < MaxSize; i++)
        L->data[i] = 0;
    L->length = 0;
}


int main(){
    SeqList L;
    InitList(&L);
    for (int i = 0; i < L.length; i++)
        printf("data[%d] = %d \n", i, L.data[i]);
    system("pause");
    return 0 ;
}
