#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 20
#define Infinte 10000
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
        int v1, v2, w;
        printf("输入存在边的两个顶点(有向图只需要输入一次)", i);
        scanf("%d%d%d", &v1, &v2, &w);
        G->Edge[v1][v2] = w;
        if (G->isdir == 0) G->Edge[v2][v1] = w;
    }
}

void CreateGraph_My(MGraph *G)
{
    // 初始化图的边
    InitGraph(G);

    (*G).vexnum = 5;
    (*G).arcnum = 10;
    (*G).isdir = 1;
    
    int c = 48;
    for (int i = 0; i < G->vexnum; i++){
        (*G).Vex[i] = c++;
    }
    

    int arr[10][3] = {{0,1,10},{0,4,5},{1,4,2},{4,1,3},{1,2,1},{4,3,2},{2,3,4},{3,2,6},{3,0,7},{4,2,9}};
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 3; j++){
            (*G).Edge[arr[i][0]][arr[i][1]] = arr[i][2];
            // (*G).Edge[arr[i][1]][arr[i][0]] = arr[i][2];
        }
    }
}

void PrintGraph(MGraph G){
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++)
            printf("%d ", G.Edge[i][j] >= 1 && G.Edge[i][j] < Infinte ? G.Edge[i][j] : 0);
        printf("\n");
    }
}

//Dijkstra算法
void Dijkstra(MGraph G, int start){
    int min_dis, index;//dist中的最短路径和对应的节点
    int dist[G.vexnum]; //记录当前循环最短路径长度
    int path[G.vexnum]; //记录当前循环各顶点的前驱顶点
    char vex[G.vexnum]; //记录各顶点是否找到最短路径

    //初始化vex、dist、path数组
    dist[start] = 0; //开始节点到自己的最短路径为0
    path[start] = -1; //开始节点无前驱
    vex[start] = 1;
    for (int i = 0; i < G.vexnum; i++){
        if (i == start) continue;
        vex[i] = 0; //vex开始只有开始节点为1，其余都为0
        dist[i] = G.Edge[start][i];
        path[i] = G.Edge[start][i] == Infinte ? -1 : start;
    }

    //进行n-1次遍历
    for (int i = 0; i < G.vexnum - 1; i++){
        //找到dist中最小的值和对应的顶点
        min_dis = Infinte; //初始化为无穷大
        index = -1;//顶点初始化为-1
        for (int i = 0; i < G.vexnum; i++){
            if (!vex[i] && dist[i] < min_dis){
                min_dis = dist[i];
                index = i;
            }
        }
        //找到的这个dist最小值就是到达index顶点的最短路径
        //所以index顶点最短路径被找到了，将其vex设置为1
        vex[index] = 1;
        //更新dist
        for (int j = 0; j < G.vexnum; j++){
            //若第j个顶点未找到最短路径，且index顶点到j顶点的距离更近，就更新dist的值
            //并且将第j个顶点的前驱节点改为index
            if (!vex[j] && G.Edge[index][j] + min_dis < dist[j]){
                dist[j] = G.Edge[index][j] + min_dis;
                path[j] = index;
            } //经过此操作之后，dist中的无穷也将被替换
        }    
    }

    printf("dist：");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%d ", dist[i]);
    }
    printf("\n");
    printf("path：");
    for (int i = 0; i < G.vexnum; i++)
    {
        printf("%d ", path[i]);
    }
    printf("\n");
    for (int i = 0; i < G.vexnum; i++){
        if (i == start) continue;
        printf("顶点%d到顶点%d的最短路径长度为：%d，最短路径为：", start, i, dist[i]);
        printf("%d", i);
        int temp = path[i];
        while (temp > 0){
            printf("<--%d", temp);
            temp  = path[temp];
        }
        printf("<--%d", start);
        printf("\n");
    }
    
        
    
    
}
int main(){
    MGraph G;
    InitGraph(&G);
    CreateGraph_My(&G);
    PrintGraph(G);
    //Dijkstra和Prime算法很像
    //两者的时间复杂度都是O(n^2)
    Dijkstra(G, 0);   
    system("pause");
    return 0;
}