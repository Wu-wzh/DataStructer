//字符集相当于函数的定义域，而编码规则相当于函数映射
#include <stdio.h>
#include <windows.h>

#define true 1
#define false 0
#define MaxSize 255


//空出第一个元素，使其下标和串字符的序号对应。
typedef struct {
    char ch[MaxSize];
    int length;
}SString;


//赋值操作
int StrAssign(SString *S, char chars[]){
    int i;
    for (i = 0; chars[i] != '\0'; i++){
        if (i + 2 == MaxSize) return false;
        S->ch[i + 1] = chars[i];
    }
    S->length = i + 1;
    return true;
}

void StrCopy(SString *T, SString S){
    for (int i = 0; i < S.length; i++){
        T->ch[i] = S.ch[i];
    }
    T->length = S.length;
}

int StrLength(SString S){
    return S.length;
}

void ClearString(SString *S){
    S->length = 0;
}

void DestoryString(SString *S){
    free(S);
    S = NULL;
}

int Concat(SString *S, char S1[], char S2[]){
    int i, j;
    for (i = 0; S1[i] != '\0'; i++)
        S->ch[i + 1] = S1[i];
    S->length = i + 1;
    for (j = 0; S2[j] != '\0'; j++)
        S->ch[S->length + j] = S2[j];
    S->length += j;
    return true;
}

void printStr(SString S){
    for (int i = 1; i < S.length; i++){
        printf("%c", S.ch[i]);
    }
    printf("\n");
}

int main(){
    SString S, T;

    // 赋值操作
    char chars[] = "wuzihaoasdds";
    StrAssign(&S, chars);
    printf("S: ");
    printStr(S); // 输出：wuzihaoasdds

    // 复制操作
    StrCopy(&T, S);
    printf("T: ");
    printStr(T); // 输出：wuzihaoasdds

    // 求串长操作
    printf("S Length: %d\n", StrLength(S)); // 输出：13

    // 清空操作
    ClearString(&S);
    printf("S: ");
    printStr(S); // 输出：

    // 销毁操作
    DestoryString(&T);
    // printf("T: ");
    // printStr(T); // 此处调用已被销毁的 T，可能会导致异常

    // 连接操作
    Concat(&S, "wuzi", "haohaha");
    printf("S: ");
    printStr(S); // 输出：wuzihaohaha

    system("pause");
    return 0;
    
}