#include <stdio.h>
#include <windows.h>

int InitSymmetricMatrix(int matrix[][]){
    int i = sizeof(matrix) / sizeof(matrix[0]);  // 行数
    int j = sizeof(matrix[0]) / sizeof(matrix[0][0]);  // 列数

}
//矩阵的相关存取
int main(){

    //通常使用二维数组来存储一般的矩阵；
    //遍历方法可以用两个循环，也可以用指针的方式访问其地址
    // int matrix[2][3] ={{1,2,3},{4,5,6}};
    // for (int i = 0; i < 2; i++){
    //     for (int j = 0; j < 3; j++){
    //         printf("%d ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("============\n");
    // int *p = &matrix[0][0];
    // for (int i = 0; i < 2 * 3; i++){
    //     if (!(i % 3) && i != 0) printf("\n");
    //     printf("%d ", *(p + i));
    // }
    

    

    system("pause");
    return 0;
}