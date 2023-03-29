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
    S->length = i;
    return true;
}

void StrCopy(char *s, SString S){
    for (int i = 0; i < S.length + 1; i++){
        s[i] = S.ch[i];
    }
}

int StrLength(SString S){
    return S.length;
}

void ClearString(SString *S){
    S->length = 0;
}

void DestoryString(SString *S){
    S = NULL;
    free(S);
    
}

int Concat(SString *S, char S1[], char S2[]){
    int i, j;
    for (i = 0; S1[i] != '\0'; i++)
        S->ch[i + 1] = S1[i];
    S->length = i;
    for (j = 0; S2[j] != '\0'; j++)
        S->ch[S->length + 1 + j] = S2[j];
    S->length += j;
    return true;
}

int SubString(SString *Sub, SString S, int pos, int len){
    if (pos + len - 1 > S.length) return false;
    for (int i = pos; i < pos + len; i++){
        Sub->ch[i - pos + 1] = S.ch[i];
    }
    Sub->length = len;
    return true;
}

int StrCompare(SString S, SString T){
    for (int i = 0; i <= S.length && i <= T.length; i++)
        if(S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    return S.length - T.length;
}


//暴搜
int Index(SString S, SString T){
    int i = 1, n = StrLength(S), m = StrLength(T);
    SString sub;
    while (i < n - m + 1)
    {
        SubString(&sub, S, i, m);
        if (StrCompare(S,sub) != 0) i++;
        else return i;
    }
    return 0;
}

//暴力搜索适合小字符串匹配，消耗较大的空间
int NaviePatternMatching(SString S, SString T){
    int i, j = 1; //i和j分别为主串S和模式串T的指针
    while (i <= S.length && j <= T.length)
    {
        if (S.ch[i] == T.ch[j]){
            i++; j++;
        }
        else{
            i = i - j + 2; //若匹配失败，则将i设置为主串中的下一个需要和模式串匹配的串的初始位置
            j = 1; //j重置为1
        }
    }
    if (j > T.length) return i - T.length; //wihle循环结束的条件是j越界，既成功匹配，若是i越界，j<T.length则没有匹配成功
    else return 0;
    
}


//求next数组，就是比较看前j个字串的前缀的头和后缀的末尾之间有多少字符可以匹配， 理解前缀和和后缀很关键
//一个串的前缀为除了最后一个字符外的所有字符构成的子串，后缀为除第一个字符
void Next(SString T,int *next)
{
    char s[T.length + 1];
    StrCopy(s, T);
    next[1] = 0;
    int i = 1, j = 0;
    while (i <= strlen(s))
    {
        if (j == 0 || s[i] == s[j]) next[++i] = ++j;
        else j = next[j];
    }
    
}


//KMP算法为朴素模式匹配的改进，在匹配过程中，j后移时，后移过的元素说明已经成功匹配，因此i的值不需要一个一个的移动
//KMP算法充分利用了模式串信息，减小匹配次数 与朴素模式匹配相比，i指针不需要回溯，这是很重要的
//模式串的信息可以用一个数组next来存储，所以算法的关键在于模式串的next数组的信息
int KMP(SString S, SString T){

    
    //求next数组
    int next[T.length + 1];
    char s[T.length + 1];
    StrCopy(s, T);
    next[1] = 0;
    int a = 1, b = 0;
    while (a <= T.length + 1)
    {
        if (b == 0 || s[a] == s[b]) next[++a] = ++b;
        else b = next[b];
    }

    // for (int c = 1; c < T.length + 1; c++){
    //     printf("%d ",next[c]);
    // }
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length)
    {
        if (j == 0 | S.ch[i] == T.ch[j]){ //next数组中的j=0的情况较为特殊，为了代码的形式统一，将j设为0，然后ij同时加一
            i++; j++;
        }
        else
            j = next[j]; //此步是关键，也是与朴素模式匹配最大的不同，本质上是优化版的暴搜
    }
    if (j > T.length) return i - T.length;
    else return 0;  
}
//时间复杂度达到了O(m+n)

void printStr(SString S){
    for (int i = 1; i < S.length + 1; i++){
        printf("%c", S.ch[i]);
    }
    printf("\n");
}

int main(){
    SString S, T;
    char s[] = "adassadababacaxzc"; 
    char sub[] = "ababac"; 
    // 赋值操作
    StrAssign(&S, s);
    StrAssign(&T, sub);
    // printf("S: ");
    // printStr(S); // 输出：wuzihaoasdds

    // // 复制操作
    // StrCopy(&T, S);
    // printf("T: ");
    // printStr(T); // 输出：wuzihaoasdds

    // // 求串长操作
    // printf("S Length: %d\n", StrLength(S)); // 输出：13

    // // 清空操作
    // ClearString(&S);
    // printf("S: ");
    // printStr(S); // 输出：

    // // 销毁操作
    // DestoryString(&T);
    // // printf("T: ");
    // // printStr(T); // 此处调用已被销毁的 T，可能会导致异常

    // // 连接操作
    // Concat(&S, "wuzi", "haohaha");
    // printf("S: ");
    // printStr(S); // 输出：wuzihaohaha
    // SString Sub;
    // SubString(&Sub, S, 3, 2);
    // printStr(Sub);
    // printf("%d\n",StrCompare(S, T));
    // printf("%d\n", NaviePatternMatching(S, T));
    // printf("%d\n", KMP(S, T));
    printf("%d\n", KMP(S, T));
    
    system("pause");
    return 0;
    
}
