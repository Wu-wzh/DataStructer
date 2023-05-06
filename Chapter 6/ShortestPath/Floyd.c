/*动态规划的思想：
初始化带权距离矩阵和前驱节点矩阵
若允许在v0中转，最短路为
若允许在v0、v1中转，最短路为
若允许在v0、v1、v2中转，最短路为
......
若允许在v0、v1、...、vn-1中转，最短路为

并且此算法可以解决存在负权的图
但无法解决带有负权回路的图
*/
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
    // int arr[5][3] = {{0,1,6},{1,0,10},{0,2,13},{2,0,5},{1,2,4}};
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
void Floyd(MGraph G){
    //初始化A(-1)和p(-1)矩阵
    int A[G.vexnum][G.vexnum];
    int p[G.vexnum][G.vexnum];
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++){
            A[i][j] = G.Edge[i][j];//初始化A为不经过任何顶点的距离，即初始路径矩阵
            p[i][j] = -1; 
            //p矩阵初始化为全-1，表示现在不经过任何节点，因此没有前驱节点
        }
    }
    
    //循环主体
    for (int k = 0; k < G.vexnum; k++) //以顶点v<=k为中转
        for (int i = 0; i < G.vexnum; i++) //进行A矩阵的遍历
            for (int j = 0; j < G.vexnum; j++)
                //若从以k节点为中继，所得到的路径小于当前的路径，则进行替换
                if (A[i][k] + A[k][j] < A[i][j]){
                    A[i][j] = A[i][k] + A[k][j];
                    p[i][j] = k; //并且更新前驱顶点p的信息
                }

    //打印输出
    printf("A矩阵：\n");
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("p矩阵：\n");
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++){
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
    int temp;
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++){
            if (i == j) continue;
            if (A[i][j] != Infinte){
                printf("顶点%d与顶点%d的最短路径长度为：%d，",i, j, A[i][j]);
                printf("最短路径为：%d", i);
                temp = j;
                while (p[i][temp] > 0){
                    temp = p[i][temp];
                    printf("-->%d", temp);
                }
                printf("-->%d", j);
                printf("\n");
            }
            else{
                printf("顶点%d与顶点%d的最短路径长度不存在\n",i, j);
            }
        }
        
    }
    
}

int main(){
    MGraph G;
    InitGraph(&G);
    CreateGraph_My(&G);
    PrintGraph(G);
    //三重for循环，时间复杂度为O(n^3)
    Floyd(G);
    system("pause");
    return 0;
}
