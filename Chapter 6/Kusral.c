#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 10
#define MaxSize 20
#define Infinte 10000
typedef struct
{
    char Vex[MaxVertexNum];               // 用来存储顶点信息
    int Edge[MaxVertexNum][MaxVertexNum]; // 用来存储边信息 在存储无权图时，可不使用int，避免空间的浪费
    int vexnum, arcnum;                   // 存储顶点和边的数量
    int isdir;                            // 是否是有向图
} MGraph;
/*此存储结构的时间复杂度：
存储顶点结构O(n),存储边结构O(n^2),所以总时间复杂度为O(n^2)
当用邻接矩阵来存储稀疏矩阵时，会造成很多存储空间的浪费，使用链式存储结构更好一点

★★★邻接矩阵A的n次方，A^n[i][j]数字代表的是从顶点i到顶点j距离为n的长度的路径个数★★★
*/

void InitGraph(MGraph *G)
{
    for (int i = 0; i < MaxVertexNum; i++)
    {
        // G->Vex[i] = NULL;
        for (int j = 0; j < MaxVertexNum; j++)
        {
            if (i == j)
                G->Edge[i][j] = 0;
            else
                G->Edge[i][j] = Infinte;
        }
    }
}
void CreateGraph(MGraph *G)
{
    // 初始化图的边
    InitGraph(G);

    printf("请输入顶点数和边数（用空格隔开）：");
    scanf("%d%d", &G->vexnum, &G->arcnum);
    // 输入每个顶点的信息
    printf("请依次输入每个顶点的信息：\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        printf("Vex[%d] = ", i);
        scanf("%s", &G->Vex[i]);
    }
    // 无向图还是有向图
    printf("无向图或有向图（0无向图，1有向图）：\n");
    scanf("%d", &G->isdir);

    // 输入每条边的起点和终点
    printf("请依次输入每条边的起点和终点（用空格隔开,编号从0开始）：\n");
    for (int i = 0; i < G->arcnum; i++)
    {
        int v1, v2, w;
        printf("输入存在边的两个顶点(有向图只需要输入一次)", i);
        scanf("%d%d%d", &v1, &v2, &w);
        G->Edge[v1][v2] = w;
        if (G->isdir == 0)
            G->Edge[v2][v1] = w;
    }
}

void CreateGraph_My(MGraph *G)
{
    // 初始化图的边
    InitGraph(G);

    (*G).vexnum = 6;
    (*G).arcnum = 10;
    (*G).isdir = 0;;

    int arr[10][3] = {{0,1,6},{0,2,5},{0,3,1},{1,3,5},{1,4,3},{2,3,4},{2,5,2},{3,4,6},{3,5,4},{4,5,6}};
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 3; j++){
            (*G).Edge[arr[i][0]][arr[i][1]] = arr[i][2];
            (*G).Edge[arr[i][1]][arr[i][0]] = arr[i][2];
        }
    }
}


void PrintGraph(MGraph G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        for (int j = 0; j < G.vexnum; j++)
            printf("%d ", G.Edge[i][j] >= 1 && G.Edge[i][j] < Infinte ? G.Edge[i][j] : 0);
        printf("\n");
    }
}
// 并查集表示的为集合关系，只实现集合的查询和并的操作
// 查操作和并操作都有优化，并操作的优化是为了降低查操作的时间复杂度
// 查操作的优化效率很高，甚至达到了常数级别
// 将n个独立的元素合并为一个集合，由于并操作需要先找到带合并元素的根节点，因此其时间复杂度为并操作乘查操作的时间复杂度

// 全部初始化为-1
void Initial_DSU(int S[])
{
    for (int i = 0; i < MaxSize; i++)
        S[i] = -1;
}

// 查操作 找到输入参数的所属集合 
int Find(int S[], int x){
    // 时间复杂度为O(n)，n为高度
    while (S[x] >= 0)
        x = S[x];
    return x;
}

// 下面代码是直接合并，可能会导致合并后的新书变高，影响查的速度
void Union(int S[], int root1, int root2)
{
    if (root1 == root2)
        return;
    S[root2] = root1;
}

//自定义qsort函数比较器
int comp(const void *a,const void *b){
    if (((int*)a)[0]<((int*)b)[0]) return -1;
    else return 1;
}

void Sort(MGraph G, int (*SortEdge)[3]){
    int index = 0;//SortEdge索引

    for (int i = 0; i < G.vexnum; i++){
        for (int j = i + 1; j < G.vexnum; j++){
            if (G.Edge[i][j] > 0 && G.Edge[i][j] < Infinte){
                SortEdge[index][0] = G.Edge[i][j];
                SortEdge[index][1] = i;
                SortEdge[index][2] = j;
                index++;
            }
                
        }
    } 
    //使用C语言自带的快速排序
    //store二维数组名 count行长度  sizeof(int)*2 总共两列 comp1自定义函数 
    qsort(SortEdge, G.arcnum, sizeof(int) * 3, comp);
}

// Kusral算法
void Kusral(MGraph G){
    int val = 0;//权重大小
    int SortEdge[G.arcnum][3]; //边排序后的数组，包含边长度和两边顶点索引

    Sort(G, SortEdge);//Sort函数得到排序后的边权二维数组
    for (int i = 0; i < G.arcnum; i++)
        printf("%d %d %d\n", SortEdge[i][0], SortEdge[i][1], SortEdge[i][2]);
    int S[MaxSize]; //S为并查集，使用树中的双亲表示法
    Initial_DSU(S); //初始化并查集，每个节点独立
    for (int i = 0; i < G.arcnum; i++){
        //判断这条边的两个顶点是否属于同一个集合
        if (Find(S, SortEdge[i][1]) != Find(S, SortEdge[i][2])){
            val += SortEdge[i][0];
            Union(S, Find(S, SortEdge[i][1]), Find(S, SortEdge[i][2]));//若不属于同一个集合，则将其进行合并
            //合并时要主要，需要将顶点进行合并，否则会出现丢失节点。
            printf("点%d和点%d相连\n", SortEdge[i][1], SortEdge[i][2]);
        }
    }
    printf("总权值大小为：%d\n", val);

}
int main()
{
    MGraph G;
    InitGraph(&G);
    CreateGraph(&G);
    PrintGraph(G);

    // Prim算法是一种顶点的贪心算法，通过不断将有最短距离的顶点并入prime数组，来找到最小生成树序列
    // 后续的Kruskal算法是一种边的贪心算法，通过不断将最短边的两个顶点并入结果数组，用到了集合之间的合并操作，因此需要使用并查集。
    // 并查集其实是一种集合数据结构，但是仅仅实现合并和判断是否是一个集合的操作，称之为并和查。
    Kusral(G);
    system("pause");
    return 0;
}