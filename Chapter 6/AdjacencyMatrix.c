#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 10
#define Infinte 10000;
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


//判断两个节点是否相邻 x y 为节点的标号，从0开始 
//若使用节点名称，需要有一个名称到标号的转移过程，需要消耗更多的时间复杂度
int Adjacent(MGraph G, int x, int y){
    return G.Edge[x][y];
}//O(1)

//输出一个节点所有的边
void Neighbors(MGraph G, int x){
    //有向图和无向图的处理方式不一样
    if (G.isdir == 0){
        for (int i = 0; i < G.vexnum; i++)
        if (G.Edge[x][i] == 1) printf("%d ", i);
        printf("\n");
    }
    else{
        for (int i = 0; i < G.vexnum; i++){ //有向图需要列和行同时遍历
            if (G.Edge[x][i] == 1) printf("%d ", i);
            if (G.Edge[i][x] == 1) printf("%d ", i);
        }
        printf("\n");
    }
}//O(|V|)

void PrintGraph(MGraph G){
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++)
            printf("%d ", G.Edge[i][j] == 1 ? G.Edge[i][j]:0);
        printf("\n");
    }
}
int main(){
    MGraph G;
    InitGraph(&G);
    CreateGraph(&G);
    PrintGraph(G);
    Neighbors(G, 0);
    system("pause");
    return 0;
}