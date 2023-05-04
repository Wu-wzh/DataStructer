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
        int v1, v2, w;
        printf("输入存在边的两个顶点(有向图只需要输入一次)", i);
        scanf("%d%d%d", &v1, &v2, &w);
        G->Edge[v1][v2] = w;
        if (G->isdir == 0) G->Edge[v2][v1] = w;
    }
}


//判断两个节点是否相邻 x y 为节点的标号，从0开始 
//若使用节点名称，需要有一个名称到标号的转移过程，需要消耗更多的时间复杂度
int Adjacent(MGraph G, int x, int y){
    return G.Edge[x][y];
}//O(1)

//有权图中的赋权操作，与Adjacent方法完全一致，实现简单
int Get_edge_value(MGraph G, int x, int y){
    return G.Edge[x][y];
}
int Set_edge_value(MGraph* G, int x, int y, int w){
    G->Edge[x][y] = w;
}

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

//插入一个新的顶点(刚插入时不和任何边相连)
void InsertVertex(MGraph* G, char x){
    //将vexnum加一，并且将x赋值给最后一个顶点的名字
    (*G).Vex[(*G).vexnum++] = x;
}//O(1)

//删除一个顶点
//一种方法是吧此行和此列删除后，进行元素移动，但是由于移动的是三个分块矩阵
//所以时间复杂度较高，因此采用添加一个标志位，删除时将此行此列全部赋值为0，并且标志位设为0即可
void DeleteVertex(MGraph* G,int x){}
//O(|V|)

//添加已存在顶点x和y之间的边
//利用随机存取的特性，极其简单
void AddEdge(MGraph* G, int x, int y){
    (*G).Edge[x][y] = 1;
}//O(1)


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

void PrintGraph(MGraph G){
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++)
            printf("%d ", G.Edge[i][j] == 1 ? G.Edge[i][j]:0);
        printf("\n");
    }
}

//Prim算法
void Prim(MGraph G, int start){
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

        prime[index++] = G.Vex[k]; //第一个顶点先入prime数组
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