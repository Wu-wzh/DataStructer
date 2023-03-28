#include <stdio.h>
#include <windows.h>

/*理解堆栈调用，其中存的有三部分
1.调用返回地址
2.实参
3.局部变量

三部分会在调用一个新的函数时压入堆栈，因此当递归调用过多时，会造成栈满
*/
int fun2(int x){
    int m, n;
    m = x + 1;
    n = x + 2;
}
int fun1 (int a, int b){
    int x = a + b;
    fun2(x);
    x = x + 10086;
    a = 10;
    b = 30;
}
int factorial(int n){
    if (n == 0 || n == 1) return 1;
    else return n * factorial(n - 1);
}
int Fib(int n){
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return Fib(n - 1) + Fib(n - 2);
    
}

int main(){
    // int a = 1, b = 2, c = 3;
    // fun1(a, b);
    // c = a + b;
    // printf("%d\n",factorial(10));
    printf("%d\n",Fib(8));
    system("pause");
    return 0;
}