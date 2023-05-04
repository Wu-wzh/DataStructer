#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 10
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

    (*G).vexnum = 6;
    (*G).arcnum = 10;
    (*G).isdir = 0;
    
    int c = 48;
    for (int i = 0; i < G->vexnum; i++){
        (*G).Vex[i] = c++;
    }
    

    int arr[10][3] = {{0,1,6},{0,2,5},{0,3,1},{1,3,5},{1,4,3},{2,3,4},{2,5,2},{3,4,6},{3,5,4},{4,5,6}};
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 3; j++){
            (*G).Edge[arr[i][0]][arr[i][1]] = arr[i][2];
            (*G).Edge[arr[i][1]][arr[i][0]] = arr[i][2];
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

//Prim算法
void Prim(MGraph G, int start){
    int val = 0;//最小权值
    int lowCast[G.vexnum]; //记录当前树邻接节点的权值
    int isJoin[G.vexnum]; //标记各节点是否入树
    char prime[G.vexnum]; //最小生成树结果数组
    int index = 0; //最小生成树的索引

    //初始化lowCast和isJoin数组
    for (int i = 0; i < G.vexnum; i++){
        lowCast[i] = G.Edge[start][i];
        isJoin[i] = 0;
    }

    prime[index++] = G.Vex[start]; //第一个顶点先入prime数组
    lowCast[start] = 0;//由于start顶点已经并入prime数组，将其lowCast设为0;
    isJoin[start] = 1;//start顶点已经完成

    //进行for循环遍历
    for (int i = 0; i < G.vexnum; i++){
        if (i == start) continue; //start节点已经完成了

        int j = 0;
        int k; //存储最小值的索引
        //寻找lowCast最小值过程
        int min = Infinte; //初始化为一个极大的数
        while (j < G.vexnum){
            if (!isJoin[j] && lowCast[j] < min){ //只寻找未进入prime数组的最小值
                min = lowCast[j];
                k = j;
            }
            j++;
        }
        val += min;
        prime[index++] = G.Vex[k]; //顶点放入prime数组
        lowCast[k] = 0;//由于k顶点已经并入prime数组，将其lowCast设为0;
        isJoin[k] = 1;//k顶点已经完成

        //更新lowCast的值
        for (int z = 0; z < G.vexnum; z++)
            if (!isJoin[z] && G.Edge[k][z] < lowCast[z]) 
            //未入prime数组且lowCast值比新入prime数组k顶点离j大，则说明此时这条边距离prime数组组成的更近
                lowCast[z] = G.Edge[k][z];
        
    }
    
    // 打印最小生成树
    printf("Prim算法生成最小生成树为：\n");
    for (int i = 0; i < index; i++)
        printf("%c ", prime[i]);
    printf("\n");
    printf("最小权值为：%d\n", val);

}
int main(){
    MGraph G;
    InitGraph(&G);
    CreateGraph(&G);
    PrintGraph(G);

    //Prim算法是一种顶点的贪心算法，通过不断将有最短距离的顶点并入prime数组，来找到最小生成树序列
    //后续的Kruskal算法是一种边的贪心算法，通过不断将最短边的两个顶点并入结果数组，用到了集合之间的合并操作，因此需要使用并查集。
    //并查集其实是一种集合数据结构，但是仅仅实现合并和判断是否是一个集合的操作，称之为并和查。
    Prim(G, 0);
    system("pause");
    return 0;
}