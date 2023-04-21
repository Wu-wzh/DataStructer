#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 5

typedef struct ArcNode{ //就是个链表
    int adjvex; //这个链表节点指向那个顶点
    struct ArcNode *next;
} ArcNode;

typedef struct VEle{ //叫元素好一点，改名后续不影响
    char data; //存储顶点信息
    ArcNode *first;//顶点对应一个链表，表示和他相连，顺序不唯一
} VEle, AdjList[MaxVertexNum];

typedef struct{
    AdjList vertices; //AdjList是一个VNode的顺序表
    int vexnum, arcnum;
} ALGraph;

void CreateList(ArcNode** first, int vex[], int len){ //len为vex的长度
    if (len == 0) return; //无邻接，直接返回
    //初始fitst为空，先进行首节点创建，否则会报错
    ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex = vex[0];
    p->next = NULL;
    *first = p;

    //p来记录最后一个节点
    for (int i = 1; i < len; i++){
        ArcNode* t = (ArcNode*)malloc(sizeof(ArcNode));
        t->adjvex = vex[i];
        t->next = NULL;
        p->next = t;
        p = t;
    }
}

// void AddNode(ArcNode** p, ArcNode* q){
//     (*p)->next = q;
// }

void InitGraph(ALGraph *G){
    for (int i = 0; i < MaxVertexNum; i++){
        // G->vertices[i].data = ;
        G->vertices[i].first = NULL;
    }        
}

void CreateGraph(ALGraph *G){
    G->vertices[0].data = 'A';
    G->vertices[1].data = 'B';
    G->vertices[2].data = 'C';
    G->vertices[3].data = 'D';
    G->vertices[4].data = 'E'; //顶点

    int x1[3] = {1,2,3};
    CreateList(&(G->vertices[0].first), x1, 3);
    int x2[2] = {0,4};
    CreateList(&(G->vertices[1].first), x2, 2);
    int x3[4] = {0,1,2,3};
    CreateList(&(G->vertices[2].first), x3, 4);
    int x4[1] = {2};
    CreateList(&(G->vertices[3].first), x4, 1);
    int x5[3] = {0,3,4};
    CreateList(&(G->vertices[4].first), x5, 3);
    
}

void PrintAdjList(ALGraph G){
    for (int i = 0; i < MaxVertexNum; i++){
        printf("%c : ",G.vertices[i].data);
        ArcNode* p = G.vertices[i].first;
        while (p != NULL)
        {
            printf("%d->", p->adjvex);
            p = p->next;
        }
        printf("end\n");
    }
}

int main(){
    ALGraph G;
    InitGraph(&G);
    CreateGraph(&G);
    PrintAdjList(G);
    system("pause");
    return 0;
}