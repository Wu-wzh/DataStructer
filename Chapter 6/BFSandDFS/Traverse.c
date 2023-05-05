#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 11
#define Infinte 10000;


//队列数据结构
typedef struct LinkNode{
    int data;
    struct LinkNode *next;
}LinkNode;

typedef struct LinkQueue{
    LinkNode *front, *tail;
}LinkQueue;

int InitQueue(LinkQueue *Q){
    Q->front = Q->tail = (LinkNode*)malloc(sizeof(LinkNode));
    Q->front->next = NULL;
    return true;
}

void EnQueue(LinkQueue *Q, int e){
    LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
    p->data = e;
    p->next =NULL;
    Q->tail->next = p;
    Q->tail = p;
}

//出队操作，只对头节点进行操作，但是要注意，当出队后队列变为空，此时需要修改tail尾指针使其与front指向同一位置
int DeQueue(LinkQueue *Q, int *x){
    if (Q->front == Q->tail) return false;
    LinkNode *p = Q->front->next;
    *x = p->data;
    Q->front->next = p->next;
    if (p == Q->tail) Q->front = Q->tail;
    p = NULL;
    free(p);
    return true;
}

int isEmpty(LinkQueue Q){
    if (Q.front == Q.tail) return true;
    else return false;
}

typedef struct{
    char Vex[MaxVertexNum]; //用来存储顶点信息
    int Edge[MaxVertexNum][MaxVertexNum]; //用来存储边信息 在存储无权图时，可不使用int，避免空间的浪费
    int vexnum, arcnum;//存储顶点和边的数量
    int isdir; //是否是有向图
} MGraph;
/*此存储结构的时间复杂度：
存储顶点结构O(n),存储边结构O(n^2),所以总时间复杂度为O(n^2)
当用邻接矩阵来存储稀疏矩阵时，会造成很多存储空间的浪费，使用链式存储结构更好一点

★★★邻接矩阵A的n次方，A^n[i][j]数字代表的是从顶点i到顶点j距离为n的长度的路径个数★★★
*/

void InitGraph(MGraph *G){
    for (int i = 0; i < MaxVertexNum; i++){
        // G->Vex[i] = NULL;
        for (int j = 0; j < MaxVertexNum; j++)
        {
            if (i == j) G->Edge[i][j] = 0;
            else G->Edge[i][j] = Infinte;
        }
    }
}
void CreateGraph(MGraph *G){
    // 初始化图的边
    InitGraph(G);

    printf("请输入顶点数和边数（用空格隔开）：");
    scanf("%d%d", &G->vexnum, &G->arcnum);
    // 输入每个顶点的信息
    printf("请依次输入每个顶点的信息：\n");
    for (int i = 0; i < G->vexnum; i++){
        printf("Vex[%d] = ", i);
        scanf("%s", &G->Vex[i]);
    }
    //无向图还是有向图
    printf("无向图或有向图（0无向图，1有向图）：\n");
    scanf("%d", &G->isdir);

    // 输入每条边的起点和终点
    printf("请依次输入每条边的起点和终点（用空格隔开,编号从0开始）：\n");
    for (int i = 0; i < G->arcnum; i++){
        int v1, v2;
        printf("输入存在边的两个顶点(有向图只需要输入一次)", i);
        scanf("%d%d", &v1, &v2);
        G->Edge[v1][v2] = 1;
        if (G->isdir == 0) G->Edge[v2][v1] = 1;
    }
}

void PrintGraph(MGraph G){
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++)
            printf("%d ", G.Edge[i][j] == 1 ? G.Edge[i][j]:0);
        printf("\n");
    }
}

//★★易考的方法★★
//找到顶点x的第一个邻接节点，在邻接矩阵中唯一
//扫描x所在的行，找到第一个节点就return，没有return-1
int FirstNeighbor(MGraph G, int x){
    for (int i = 0; i < G.vexnum; i++){
        if (G.Edge[x][i] == 1) return i;
    }
    return -1;
}//O(1)~O(|V|)

//假设y是x的第一个邻接点，求x的下一个邻接点
//与寻找第一个邻接点类似
int NextNeighbor(MGraph G, int x, int y){
    for (int i = y + 1; i < G.vexnum; i++){
        if (G.Edge[x][i] == 1) return i;
    }
    return -1;
}


void visit(MGraph G, int x){
    printf("%c ", G.Vex[x]);
}
//图的遍历算法
//与树的便利不同，遍历过程中可能出现多次遍历同一个顶点，因此需要一个visited数组来标记是否已经访问过此顶点


//BFS广度优先遍历
int visited[MaxVertexNum];//全局变量visited visited可能不完全使用

void BFS(MGraph G, int v){
    LinkQueue Q;
    InitQueue(&Q);
    //开始遍历，与树的遍历类似，只不过是添加了visited判断操作
    visit(G, v);
    visited[v] = 1; //节点v访问过，visited值设置为1
    EnQueue(&Q, v);//v入队，进行后续操作
    //从w的第一个邻接顶点开始，

    //进入while循环，直到Q为空，若还有为遍历的顶点，则还会进行入队操作，所以不用担心还没遍历完就提前结束
    while (!isEmpty(Q)){
        DeQueue(&Q, &v);//v出队，并且将为访问过的v的邻接节点全部入队
        //检测所有v节点的邻接节点，未visited过的入队

        //若所有顶点都被访问完，下面for循环不会造成入队，这样队列的数量最终减小到0，结束while循环
        for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
            if (!visited[w]){
                visit(G, w);
                visited[w] = 1;
                EnQueue(&Q, w);//当然也可以出队时访问，这是由于队列的FIFO的特性决定的，两者都可以
            }
    }
    printf("\n");
}
//邻接矩阵BFS遍历是唯一的，但是邻接表是不唯一的


void BFSTraverse(MGraph G, int v){
    int len = 1;//记录是第几个连通分量
    //初始化visited数组（只需要初始化顶点数个就可以）
    for (int i = 0; i < G.vexnum; i++){
        visited[i] = 0;
    }
    printf("第%d个连通分量的BFS遍历结果为：", len++);
    BFS(G, v);//先调用一次BFS至少遍历一个连通分量，之后检查是不是还有其他的连通分量
    for (int i = 0; i < G.vexnum; i++){
        if (!visited[i]){
            printf("第%d个连通分量的BFS遍历结果为：", len++);
            BFS(G, i);//遍历其他连通分量
        }
        
    }
        
    
}
//从顶点v出发进行广度优先遍历
//空间复杂度：队列存储最多的情况为O(|V|)
//时间复杂度：邻接矩阵：O(|V|^2)
//邻接表：O(|V| + |E|)


void DFS(MGraph G, int v){
    visit(G, v);
    visited[v] = 1;
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w)){
        if(!visited[w])
            DFS(G, w);
    }
}//广度优先遍历用队列，深度优先遍历用递归，堆栈调用

void DFSTraverse(MGraph G, int v){
        int len = 1;//记录是第几个连通分量
    //初始化visited数组（只需要初始化顶点数个就可以）
    for (int i = 0; i < G.vexnum; i++){
        visited[i] = 0;
    }
    printf("第%d个连通分量的DFS遍历结果为：", len++);
    DFS(G, v);//先调用一次BFS至少遍历一个连通分量，之后检查是不是还有其他的连通分量
    for (int i = 0; i < G.vexnum; i++){
        if (!visited[i]){
            printf("第%d个连通分量的BFS遍历结果为：", len++);
            DFS(G, i);//遍历其他连通分量
        }
    }
}
int main(){
    MGraph G;
    InitGraph(&G);
    CreateGraph(&G);
    PrintGraph(G);
    BFSTraverse(G, 1);
    DFSTraverse(G, 1);
    system("pause");
    return 0;
}