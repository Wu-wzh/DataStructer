#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 4

typedef struct EdgeNode {
    int vertex1;            // 边的两个端点
    int vertex2;
    struct EdgeNode* next1; // 指向同一个端点的下一条边
    struct EdgeNode* next2; // 指向另一个端点的下一条边
} EdgeNode;

//与十字链表最大的不同便是把两个链表邻接表和逆邻接表进行了合并，
//所以不区分边的方向，因此邻接多重表只能存储无向图
typedef struct VertexNode {
    char data;              // 顶点数据
    EdgeNode* firstedge;    // 指向第一条依附该顶点的边
} VertexNode, AdjList[MaxVertexNum];

typedef struct {
    AdjList vertices;       // 顶点数组
    int vexnum;             // 顶点数
    int edgenum;            // 边数
} AMGraph;

void CreateEdgeNode(EdgeNode** edge, int v1, int v2) {
    *edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    (*edge)->vertex1 = v1;
    (*edge)->vertex2 = v2;
    (*edge)->next1 = NULL;
    (*edge)->next2 = NULL;
}

void CreateList(AMGraph* G, int v1, int v2) {
    EdgeNode* edge;
    CreateEdgeNode(&edge, v1, v2);

    // 为v1添加一条新的边
    if (G->vertices[v1].firstedge == NULL) {
        G->vertices[v1].firstedge = edge;
    } else {
        EdgeNode* p = G->vertices[v1].firstedge;
        while (p->next1 != NULL) {
            p = p->next1;
        }
        p->next1 = edge;
    }

    // 为v2添加一条新的边
    if (G->vertices[v2].firstedge == NULL) {
        G->vertices[v2].firstedge = edge;
    } else {
        EdgeNode* p = G->vertices[v2].firstedge;
        while (p->next2 != NULL) {
            p = p->next2;
        }
        p->next2 = edge;
    }
}

void InitGraph(AMGraph* G) {
    G->vexnum = MaxVertexNum;
    G->edgenum = 0;
    for (int i = 0; i < G->vexnum; i++) {
        G->vertices[i].data = 'A' + i;
        G->vertices[i].firstedge = NULL;
    }
}

void PrintGraph(AMGraph* G) {
    printf("图的邻接多重表如下：\n");
    for (int i = 0; i < G->vexnum; i++) {
        printf("%c: ", G->vertices[i].data);
        EdgeNode* p = G->vertices[i].firstedge;
        while (p != NULL) {
            if (p->vertex1 == i) {
                printf("%c ", G->vertices[p->vertex2].data);
                p = p->next1;
            } else {
                printf("%c ", G->vertices[p->vertex1].data);
                p = p->next2;
            }
        }
        printf("\n");
    }
}

int main() {
    AMGraph G;
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
