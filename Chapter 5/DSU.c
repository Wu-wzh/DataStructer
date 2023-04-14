#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0
#define MaxSize 100
//并查集表示的为集合关系，只实现集合的查询和并的操作
//查操作和并操作都有优化，并操作的优化是为了降低查操作的时间复杂度
//查操作的优化效率很高，甚至达到了常数级别
//将n个独立的元素合并为一个集合，由于并操作需要先找到带合并元素的根节点，因此其时间复杂度为并操作乘查操作的时间复杂度
int UFSets[MaxSize];

//全部初始化为-1
void Initial(int S[]){
    for (int i = 0; i < MaxSize; i++)
        S[i] = -1;
}

//根节点的绝对值为此集合树的高度
void CreateDSU(int S[]){
    S[0] = -3;
    S[1] = 0;
    S[2] = 0;
    S[3] = 1;
    S[4] = -2;
    S[5] = 4;
    S[6] = 4;
    S[7] = -2;
    S[8] = 7;
}

//查操作 找到输入参数的所属集合
int Find_Bad(int S[], int x){
    //时间复杂度为O(n)，n为高度
    while(S[x] >= 0)
        x = S[x];
    return x;
}

//查操作的优化，压缩路径 变为尽量宽的树
int Find(int S[], int x){
    int root = x;
    while(S[root] >= 0)
        root = S[root];

    //压缩路径
    while (x != root){
        int t = S[x]; //找到x的父节点
        S[x] = root; //将父节点直接挂载到根节点上
        x = t; //找父节点，继续进行压缩
    }
    //以上while便实现了将x到root节点上的所有节点进行压缩，降低了查找树，提高后续时间复杂度
}
//优化之后的时间复杂度甚至降低到常数级别;

//查操作的时间复杂度与单个集合所构成的树的高度有关
//因此要想进行快速的查询，需要在并操作时使合并的树高度尽可能少

//下面代码是直接合并，可能会导致合并后的新书变高，影响查的速度
void Union_Bad(int S[], int root1, int root2){
    if (root1 == root2) return;
    S[root2] = root1;
}

//小树并入大树
//对并操作进行优化之后，树的高度不超过O(logn),所以查操作的时间复杂度也降到logn，但并的操作还是O(1)
void Union(int S[], int root1, int root2){
    if (root1 == root2) return;

    //由于规定在根节点的值为负值，因此值越大，树越小
    if (S[root1] > S[root2]){ //root1为小树
        S[root2] += S[root1];
        S[root1] = root2;
    } else{ //root2为小树
        S[root1] += S[root2];
        S[root2] = root1;
    }
}

int main(){

    system("pause");
    return 0;
}