#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxVertexNum 5
#define Infinte 10000;
typedef struct{
    char Vex[MaxVertexNum]; //用来存储顶点信息
    int Edge[MaxVertexNum][MaxVertexNum]; //用来存储边信息 在存储无权图时，可不使用int，避免空间的浪费
    int vexnum, arcnum;//存储顶点和边的数量
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
    char List[MaxVertexNum];
    List[0] = 'A';
    List[1] = 'B';
    List[2] = 'C';
    List[3] = 'D';
    List[4] = 'E';
    for (int i = 0; i < MaxVertexNum; i++){
        G->Vex[i] = List[i];
        G->Edge[0][1] = 1;
        G->Edge[1][0] = 1;
        G->Edge[1][2] = 1;
        G->Edge[2][1] = 1;
        G->Edge[2][3] = 1;
        G->Edge[3][2] = 1;
        G->Edge[3][4] = 1;
        G->Edge[4][3] = 1;
    }//生成一个环
}
void PrintGraph(MGraph G){
    for (int i = 0; i < MaxVertexNum; i++){
        for (int j = 0; j < MaxVertexNum; j++)
            printf("%d ", G.Edge[i][j] == 1 ? G.Edge[i][j]:0);
        printf("\n");
    }
}
int main(){
    MGraph G;
    InitGraph(&G);
    CreateGraph(&G);
    PrintGraph(G);
    system("pause");
    return 0;
}