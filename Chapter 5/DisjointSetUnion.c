#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxSize 100
typedef char EleType;

typedef struct{
    EleType name;
    int parent;
}Node;
typedef struct{
    Node node[MaxSize];
    int n; //存储并查集中的元素个数
}DSU;

void InitDSU(DSU *D){
    for (int i = 0; i < MaxSize; i++)
        D->node[i].parent = -1;
    D->n = 0;
}

void CreateDSU(DSU *D){
    D->node[0].name = 'A';
    D->node[0].parent = -1;
    D->n++;
    D->node[1].name = 'E';
    D->node[1].parent = 0;
    D->n++;
    D->node[2].name = 'C';
    D->node[2].parent = 0;
    D->n++;
    D->node[3].name = 'H';
    D->node[3].parent = 1;
    D->n++;
    D->node[4].name = 'B';
    D->node[4].parent = -1;
    D->n++;
    D->node[5].name = 'D';
    D->node[5].parent = 4;
    D->n++;
    D->node[6].name = 'F';
    D->node[6].parent = 4;
    D->n++;
    D->node[7].name = 'G';
    D->node[7].parent = -1;
    D->n++;
    D->node[8].name = 'I';
    D->node[8].parent = 7;
    D->n++;
}
void PrintDSU(DSU D){
    for (int i = 0; i < D.n; i++){
        printf("%c ", D.node[i].name);
        printf("%d\n", D.node[i].parent);
    }
}

int FindIndex(DSU D, char A){
    int i = 0;
    while (D.node[i].name != A)
    {
        i++;
        if (i >= D.n) return -2;
    }
    // return i < D.n ? D.node[i].parent : -2;
    return D.node[i].parent;
}

char Find(DSU D, char A){
    int index = FindIndex(D, A);
    while (D.node[index].parent >= 0)
    {
        index = D.node[index].parent;
    }
    return D.node[index].name;
}

// void Union(DSU D, char A)
int main(){
    DSU D;
    InitDSU(&D);
    CreateDSU(&D);
    // printf("%d", D.n);
    PrintDSU(D);
    // printf("%d", FindIndex(D, 'H'));
    char A;
    printf("输入要查找的字母(存在于并查集中)\n");
    scanf("%c", &A);
    printf("字母%c所在集合的根字母为%c\n",A, Find(D, A));

    system("pause");
    return 0;
}