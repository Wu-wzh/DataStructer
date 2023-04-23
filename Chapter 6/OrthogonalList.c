#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 4

typedef struct ArcNode {
    int inversename;  // 弧的起点 逆邻接表
    int positivename;  // 弧的终点 邻接表
    struct ArcNode* inverselink;  // 指向同终点的下一条弧 或者叫做逆邻接表指针
    struct ArcNode* positivelink;  // 指向同起点的下一条弧 或者叫做正邻接表指针
} ArcNode;

typedef struct VEle {
    char data;  // 顶点数据
    ArcNode* firstout;  // 指向第一条出弧
    ArcNode* firstin;   // 指向第一条入弧
} VEle, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;  // 顶点数组
    int vexnum;        // 顶点数
    int arcnum;        // 弧数
} ALGraph;

void CreateArcNode(ArcNode** arc, int tail, int head) {
    *arc = (ArcNode*)malloc(sizeof(ArcNode));
    (*arc)->inversename = tail;
    (*arc)->positivename = head;
    (*arc)->inverselink = NULL;
    (*arc)->positivelink = NULL;
}

void CreateList(ALGraph* G, int node_pre, int node_later) {  //横向纵向创建十字链表
    ArcNode* arc;
    CreateArcNode(&arc, node_pre, node_later);

    //逆邻接表的实现
    if (G->vertices[node_pre].firstout == NULL) { //将此节点当作邻接表的头节点
        G->vertices[node_pre].firstout = arc;
    } else {  //头插法
        arc->positivelink = G->vertices[node_pre].firstout;
        G->vertices[node_pre].firstout = arc;
    }

    //邻接表的实现
    if (G->vertices[node_later].firstin == NULL) { //将此节点当作逆邻接表的头节点
        G->vertices[node_later].firstin = arc;
    } else { //头插法
        arc->inverselink = G->vertices[node_later].firstin;
        G->vertices[node_later].firstin = arc;
    }

    //十字链表实际上是吧邻接表和逆邻接表放在了同一个结构体中，从而使得计算出度和入度都很简单
    //因此十字链表只能存储有向图，因为只有有向图才有入度和出度
}

void InitGraph(ALGraph* G) {
    G->vexnum = MaxVertexNum;
    G->arcnum = 0;
    for (int i = 0; i < G->vexnum; i++) {
        G->vertices[i].data = 'A' + i;  // 给顶点赋值
        G->vertices[i].firstout = NULL;
        G->vertices[i].firstin = NULL;
    }
}

void PrintGraph(ALGraph* G) {
    printf("图的十字链表如下：\n");
    for (int i = 0; i < G->vexnum; i++) {
        printf("%c: ", G->vertices[i].data);
        ArcNode* out = G->vertices[i].firstout;
        ArcNode* in = G->vertices[i].firstin;
        printf("出边节点 : ");
        while (out != NULL) {
            printf("%c, ", G->vertices[out->positivename].data);
            out = out->positivelink;
        }
        printf(" || ");
        printf("入边节点 : ");
        while (in != NULL) {
            printf("%c, ", G->vertices[in->inversename].data);
            in = in->inverselink;
        }
        printf("\n");
    }
}

int main() {
    ALGraph G;
    InitGraph(&G);
    CreateList(&G, 0, 1);
    CreateList(&G, 0, 2);
    CreateList(&G, 2, 0);
    CreateList(&G, 2, 3);
    CreateList(&G, 3, 0);
    CreateList(&G, 3, 1);
    CreateList(&G, 3, 2);
    PrintGraph(&G);

    system("pause");
    return 0;
}