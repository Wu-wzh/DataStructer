#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 10

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
    int isdir;
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
    printf("请输入顶点数和边数（用空格隔开）：");
    scanf("%d%d", &G->vexnum, &G->arcnum);
    // 输入每个顶点的信息
    printf("请依次输入每个顶点的信息：\n");
    for (int i = 0; i < G->vexnum; i++){
        printf("顶点[%d]为：", i);
        scanf("%s", &G->vertices[i].data);
    }

    //无向图还是有向图
    printf("无向图或有向图（0无向图，1有向图）：\n");
    scanf("%d", &G->isdir);

    for (int j = 0; j < G->vexnum; j++){
        printf("第%d个顶点共有几条边：", j);
        int len;
        scanf("%d", &len);
        int vex[len];
        printf("依次输入与第%d个顶点邻接的顶点：\n");
        for (int k = 0; k < len; k++){
            scanf("%d", &vex[k]);
        }
        CreateList(&(G->vertices[j].first), vex, len);
    }
    
}

//判断两个节点是否相邻 x y 为节点的标号，从0开始(只实现了无向图，有向图需要进行两遍如下操作)
int Adjacent(ALGraph G, int x, int y){
    ArcNode* p = G.vertices[x].first;
    while(p != NULL){
        if (p->adjvex == y) return true;
        p = p->next;
    }
    return false;
}

//输出一个节点所有的边
//
void Neighbors(ALGraph G, int x){
    if (G.isdir == 0){ //无向图 直接找到此节点的链表遍历即可
        ArcNode* p = G.vertices[x].first;
        while(p != NULL){
            printf("%d ",p->adjvex);
            p = p->next;
        }
    }

    //有向图 不仅要找到此节点的链表，还要找到其他节点的链表中是否有自己
    //时间复杂度较高，取决于边的条数和顶点的个数，但在稀疏矩阵中和无向图差异不大
    else{
        for (int i = 0; i < G.vexnum; i++){
            //若为自己的链表，输出所有
            //此if为寻找出边
            if (i == x) {
                ArcNode* p = G.vertices[i].first;
                while(p != NULL){ 
                    printf("%d ",p->adjvex);
                    p = p->next;
                }
            }
            //此else为寻找入边，可以看到，邻接表存取时，寻找入边需要遍历整个表，时间复杂度为O(|E|)
            else{
                ArcNode* p = G.vertices[i].first;
                while(p != NULL){ 
                    if (p->adjvex == x){
                        printf("%d ", i);
                        break;
                    }
                    p = p->next;
                }
            }
        }
    }
}//O(|V| + |E|)

//插入一个新的顶点(刚插入时不和任何边相连)
void InsertVertex(ALGraph* G, char x){
    //将vexnum加一，并且将x赋值给最后一个顶点的名字
    (*G).vertices[(*G).vexnum++].data = x;
}//O(1)

//删除一个顶点
//不仅要将顶点所在行的列表全部删除，还要遍历整个邻接表，删除所有关于此顶点的信息
//因此最坏情况下需要遍历完全部的边
void DeleteVertex(ALGraph* G,int x){}
//O(|E|)

//添加已存在顶点x和y之间的边
//使用头插法更快，有向图和无向图操作略有不同
void AddEdge(ALGraph* G, int x, int y){
    if (G->isdir){ //有向图只需要对x的链表进行头插
        ArcNode* t = (ArcNode*)malloc(sizeof(ArcNode));
        t->adjvex = y;
        //头插法，first为头节点
        t->next = (*G).vertices[x].first->next;
        (*G).vertices[x].first->next = t;
    }
    else{//无向图不仅需要对x，还要镜像对y的链表进行修改
        ArcNode* t1 = (ArcNode*)malloc(sizeof(ArcNode));
        t1->adjvex = y;
        //头插法，first为头节点
        t1->next = (*G).vertices[x].first->next;
        (*G).vertices[x].first->next = t1;

        ArcNode* t2 = (ArcNode*)malloc(sizeof(ArcNode));
        t2->adjvex = x;
        //头插法，first为头节点
        t2->next = (*G).vertices[y].first->next;
        (*G).vertices[x].first->next = t2;
    }
}//O(1)


//★★易考的方法★★
//找到顶点x的第一个邻接节点，在邻接表中可能唯一，因为链表是没有顺序的
//扫描x的链表，找到第一个节点就return，没有return-1
int FirstNeighbor(ALGraph G, int x){
    if (G.vertices[x].first != NULL) return G.vertices[x].first->adjvex;
    else return -1;
}//O(1)
//有向图寻找入边比较复杂，一般不使用邻接表
//因此只考虑无向图和有向图出边的情况

//假设y是x的第一个邻接点，求x的下一个邻接点
//与寻找第一个邻接点类似
int NextNeighbor(ALGraph G, int x, int y){
    if (G.vertices[x].first->next != NULL) return G.vertices[x].first->next->adjvex;
    else return -1;
}

//有权图中的赋权操作，与Adjacent方法完全一致，实现简单
int Get_edge_value(ALGraph G, int x, int y){}
int Set_edge_value(ALGraph G, int x, int y){}

void PrintAdjList(ALGraph G){
    for (int i = 0; i < G.vexnum; i++){
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
    // printf("%d\n", Adjacent(G, 0, 2));
    // printf("%d\n", Adjacent(G, 0, 4));
    Neighbors(G, 0);
    system("pause");
    return 0;
}