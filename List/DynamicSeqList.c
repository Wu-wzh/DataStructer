/*
不完全合乎规范的C语言代码，在进行传进参数的时候，使用了c++中的&引用，而没有使用C语言中的地址。
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define InitSize 10
#define true 1
#define false 0

//SeqList中包含了数据本身，同时包含了最大容量MaxSize和现在容量length
typedef struct{
    int *data;
    int MaxSize;
    int length;
}SeqList;

//初始化线性表,设置其初始元素全为0
void InitList(SeqList* L){
    L->data = (int*)malloc(InitSize * sizeof(int));
    for  (int i = 0; i < InitSize; i++)
        L->data[i] = 0;
    L->length = 0;
    L->MaxSize = InitSize;
}

//扩容线性表，扩容的大小为len,时间复杂度为O(n)
void IncreaseSize(SeqList *L, int len){
    int *p = L->data;
    L->data =(int *)malloc((L->MaxSize + len) * sizeof(int));
    for (int i = 0; i < L->length; i++)
        L->data[i] = p[i];
    L->MaxSize = L->MaxSize + len;
    free(p);
}
void InitList_Line(SeqList *L, int len){
    L->data = (int*)malloc(InitSize * sizeof(int));
    int temp = 1;
    for  (int i = 0; i < len; i++)
        L->data[i] = temp++;
    L->length = len;
    L->MaxSize = InitSize;
}
//线性表的插入
/*
i是位序，从1开始，但是数组下标从0开始
for循环中执行的操作为将第i个以后的元素进行后移
“>= i” :for循环内的操作是后一个赋值到前一个，因此最后一次赋值是将位序i也就是对应数组下标i-1的元素赋给数组下标i的元素，因此循环变量j的结束需要到达i；
数组下标j应该到达位序i；

时间复杂度分析：
i共有从1到length+1(设length为n)n+1个选择，设每次出现的概率相同，每次移动的数量可以用通项n+1-i表示，
算法的平均复杂度为1/(n+1) * i从1到n+1 通项n+1-i求和
求和为从1加到n，即n(n+1)/2,除以每次出现的概率之后得到平均移动次数 n/2, 因此此算法的时间复杂度是O(n)级别的。

特别的，i=length+1时，时间复杂度为o(1)
*/
int ListInsert(SeqList *L, int i, int e){
    if (i < 1 || i > L->length + 1) {
        printf("Invalid Number!!\n");
        return false;
    }
    if (L->length >= L->MaxSize){
        printf("Out of bound!!\n");
        return false;
    } 
    for (int j = L->length; j >= i; j--)
        L->data[j] = L->data[j - 1];
    L->data[i - 1] = e;
    L->length++;
    return true;
}

//线性表元素删除
/*
for 循环代码可修改为
for (int j = i; j < L.length; j++)
        L.data[j - 1] = L.data[j];
此为课本上的代码，两者完全相同；
分析跟插入节点类似

时间复杂度分析：
i共有从1到n n种选择，假设每种情况的概率相同，每次移动元素个数的通项为n-i，因此平均时间复杂度为
1/n * n从1到n 求和，通项为n-i，因此最后平均移动次数的 (n-1)/2 ，因此算法的时间复杂度是O(n)级别的，
特别的，i=length时，时间复杂度为o(1)
*/
int ListDelete(SeqList *L, int i){
    if (i < 1 || i > L->length){
        printf("Invalid Number!!");
        return false;
    }
    int del = L->data[i - 1];
    for (int j = i - 1; j < L->length - 1; j++)
        L->data[j] = L->data[j + 1];
    L->data[L->length - 1] = 0;
    L->length--;
    return true;
}


//按位查找
int GetElement(SeqList L, int i){
    if (i < 1 || i > L.length + 1){
        printf("Invalid Number!!\n");
        return -1;
    } 
    return L.data[i-1];
}

//按值查找 时间复杂度为O(n)
int LocateElement(SeqList L, int e){
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e)
            return i + 1;
    return 0;
}
//遍历线性表输出元素
void printList(SeqList L){
    for (int i = 0; i < L.length; i++)
        printf("data[%d] = %d\n",i+1,L.data[i]);
}



//P17页课本题目

//第一题，顺序表中删除最小值元素(假设唯一)，返回删除的值，并且空出的位置由最后一个元素填补，若顺序表为空则返回错误信息
/*
时间复杂度分析
其关键步骤在于最小值的遍历寻找，无论如何都需要遍历完整个线性表，因此其时间复杂度为O(n)；
*/
int T1_Del_Min(SeqList *L){
    //顺序表为空是返回错误信息
    if (L->length == 0){
        printf("顺序表为空！");
        return -1;
    } 
    int index = 0;
    int min = L->data[0];
    for (int i = 1 ; i < L->length; i++)
        if (L->data[i] < min){
            min = L->data[i];
            index = i;
        }
    L->data[index] = L->data[L->length - 1];
    L->length--;       
    return min;
}

//第二题，逆置元素，要求空间复杂度是O(1)
/*
重新申请内存空间进行赋值的操作空间复杂度为O(n)，因此需要实现原地逆序，从中间开始，对称元素交换即可。
不用考虑奇数偶数情况，偶数是全部元素进行对调，奇数时最中间的元素不进行移动

时间复杂度分析
算法的操作次数为T(n/2)，因此其时间复杂度为O(n);
*/
void T2_Reverse(SeqList *L){
    int temp = 0;
    for (int i = 0; i < L->length / 2; i++){
        temp = L->data[i];
        L->data[i] = L->data[L->length - 1 - i];
        L->data[L->length - 1 - i] = temp;
    }
}

//第三题，时间复杂度为O(n),空间复杂度为O(1),实现删除线性表中所有值为x的元素；

/*
为了使空间复杂度为O(1),只能采用原地删除的方式，既不能重新申请内存。

*/

/*
第一种方法 使用num记录线性表中不等于e的元素个数，若元素数值不为e，则将这个元素赋值给data[num]，同时num++,
若此元素数值为e，则不进行赋值操作，使其被后来元素覆盖，注意这样赋值之后，若线性表中有k个元素值为e，则最后k个元素需要删除，只需要将L的length赋值为num即可，但数据还是保存在了内存当中
*/
void T3_Del_Value_1(SeqList *L, int e){
    int num = 0;
    for (int i = 0; i < L->length; i++){
        if (L->data[i] != e){
            L->data[num] = L->data[i];
            num++;
        }
    }
    L->length = num;
}

/*
第二种方法 使用num记录线性表中等于e的元素个数，若元素数值不为e，则将元素前移num个位置，若元素个数为e，则num++，
遍历一遍线性表即可实现删除元素操作,最后将线性表长度设为length-num
*/
void T3_Del_Value_2(SeqList *L, int e){
    int num = 0;
    for (int i = 0; i < L->length; i++){
        if (L->data[i] != e){
            L->data[i - num] = L->data[i];
        }
        else num++;
    }
    L->length = L->length - num;
}

/*以上两种方法都是通过辅助变量num记录为e或者不为e的个数，通过个数进行覆盖赋值，
第三种方法在线性表中使用指针的思想，一个头指针一个尾指针，两者分别向中间移动，直到相遇,
但这种方式最后的结果会导致顺序改变，若不在乎线性表顺序，此方法将是三种方法中时间复杂度最低的算法
注：while条件中需要小于等于，若缺少等于，可能多出元素，如全2线性表，删除2后tail最后到达0，但长度却赋为了1，这是不对的因为此时正确答案应该线性表中数据应该全部删除
*/

void T3_Del_Value_3(SeqList *L, int e){
    int head = 0;
    int tail = L->length - 1;
    while (head <= tail){
        if (L->data[head] == e){
            if (L->data[tail] != e){
                // int temp = L->data[head];
                L->data[head] = L->data[tail];
                tail--;
                head++;
            }
            else{
                tail--;
            }
        }
        else head++;
    }
    L->length = tail + 1;
}


//第四题， 有序（在很多教材中有序是指的递增有序）顺序表中删除值在s到t之间的元素（s<t，并且包含s和t），s或t不合理或表空，返回对应错误信息
/*
有序顺序表是关键，最好的算法是同时从头的尾进行比较，直到找到临界值对应的标号，将中间的元素进行覆盖即可
下面是我的方法，分析其时间复杂度为O(n)级别的，在最坏情况下需要进行n次比较，并且进行n次赋值操作
发现课本方法跟我的基本一致，但课本的代码更加简洁。需要学习一下。
*/
void T4_Del_Range_1(SeqList *L, int s, int t){
    if (L->length == 0) printf("Empty List!!\n");
    else if (s > t) printf("Invalid s and t!!\n");
    else{
        int head = 0;
        int tail = L->length - 1;
        //升序情况
        while (L->data[head] < s){
            head++;
        }
        while (L->data[tail] > t){
            tail--;
        }
        for (int i = 0; i <= L->length - tail - 1; i++){
            L->data[head + i] = L->data[tail + i + 1];
        }
        L->length = L->length - (tail - head + 1);
        
    }
}

void T4_Del_Range_2(SeqList *L, int s, int t){
    //输出对应的错误类型
    // if (s > L->data[L->length]) printf("S too large!!\n");
    // else if (t < L->data[0]) printf("T too small!!\n");
    if (s > t) printf("Invalid S and T!!\n");
    else if (L->length == 0) printf("Empty List!!\n");

    else{
        int i, j;
        //由此可见，for循环可以写一句单独判断，用来找临界值

        //O(n)
        for (i = 0; i < L->length && L->data[i] <s; i++);  //寻找第一个大于等于s的元素下标i
        for (j = i; j < L->length && L->data[i] <= t; j++); //寻找第一个大于t的下标j
        //接下来将从i到j-1的元素，使用j开始到最后的元素进行替换即可，
        //这也是为什么i要找到大于等于，因为i就是要替换的第一个元素，必须要保证i严格在s和t的区间内，所以取s或者取大于s
        //i是第一个替换的元素必须在s和t之外也就是严格大于t

        //接下来进行替换即可
        //取决于j的初值
        for (; j < L->length; j++,i++)
            L->data[i] = L->data[j];
        //最后将L的长度赋为i
        L->length = i;
    }

}

//第五题 与第四题类似，但不要求顺序表是有序的，因此不能使用i和j下边找到区间再进行替换，
//将所有符合条件的元素放到顺序表的前部分，使用num记录符合条件元素的数量，最后将num后的元素覆盖前面元素，但这种方法会使得原有的顺序发生改变。

void T5_Del_Range_Unorder_1(SeqList *L, int s, int t){
    int num = 0;
    for (int i = 0; i < L->length; i++){
        //将所有的在区间内的元素全部放到前面。
        if (L->data[i] >= s && L->data[i] <= t){
            int temp = L->data[num];
            L->data[num] = L->data[i];
            L->data[i] = temp;
            num++;
        }
        // printList(*L);
        // printf("========\n");
        //使用后面的元素覆盖前面的元素，完成区间原地删除.
    }
    

    for (int j = 0; j + num < L->length; j++){
            int temp = L->data[j];
            L->data[j] = L->data[j + num];
            L->data[j + num] = temp;
    }
    L->length = L->length - num;
}

//课本上的方法是将所有不在区间的元素前移，和我的方法相反，但是可以保证不在区间内的元素顺序不发生改变。

/*
分析：此算法通过记录属于区间内元素的个数k，当此元素属于区间时，个数加一，不属于时，
此元素前移个数个元素，这保证了在任何时间，前i-k个一定是不属于区间内的元素。
*/
void T5_Del_Range_Unorder_2(SeqList *L,int s, int t){
    if (!L->length) printf("Empty List!!\n");
    if (s > t) printf("Invalid S and T!!\n");
    int k  = 0;
    for (int i = 0; i < L->length; i++){
        if (L->data[i] >= s && L->data[i] <= t) k++;
        else L->data[i - k] = L->data[i];
    }
    L->length -= k;
}

//第六题 在有序顺序表中删除所有重复元素，使得最后得到的线性表内元素均不同。


//从上面几个题可以总结出，改变循环变量i之前的元素，不会影响或造成混乱，因此可以考虑在第i个元素时，如何比较，如何对i前面元素进行操作，从而实现算法。
void T6_Del_Repeat_1(SeqList *L){
    int i, j ;
    for (i = 0,j = 1; j < L->length; j++)
        if (L->data[j] != L->data[i]) L->data[++i] = L->data[j];
    L->length = i + 1;
}
//另外，因为顺序表是有序的，所以重复元素都会排列在一地，因此实现删除算法较为简单，下面将考虑无序顺序表中删除方法，考虑使用散列结构。
//散列结构是查找部分的内容，后续还会对这里进行补充。
void T6_Del_Repeat_2(SeqList *L){
    int MaxSize = 100;
    int Hashtable[MaxSize];
    memset(Hashtable, 0, sizeof(Hashtable));  // 将数组元素全部设为0
    for (int i = 0; i < L->length; i++){
        Hashtable[L->data[i]] += 1;
    }
    int new_length = 0;
    for (int j = 0; j< L->MaxSize; j++){
        printf("%d: %d\n",j, Hashtable[j]);
        if (Hashtable[j] != 0){
            L->data[new_length] = j;
            new_length++;
        }
    }
    L->length = new_length;
}

//第七题 本题将所有数据唯一化，只需修改相等的情况即可，与合并两个有序单链表的方法类似，只不过不能使用头插法，
//使用两个指针变量i和j，来记录L1和L2的插入位置，当一个表完全被比较完成时，结束while循环，然后将没有比较完的按顺序放到L后面
//因此在有一个表中的最大数据都小于另一个表中的最小数据，时间复杂度为Omin(L1.length,L2.length)
SeqList T7_Merge(SeqList L1, SeqList L2){
    SeqList L;
    L.data = (int*)malloc((L1.length + L2.length)* sizeof(int));
    int len = 0;
    int i = 0;
    int j = 0;
    while (i != L1.length && j != L2.length){
        if (L1.data[i] < L2.data[j]){
            L.data[len++] = L1.data[i++];
        }
        else if (L1.data[i] == L2.data[j])
        {
            L.data[len++] = L1.data[i++];
            j++;
        }
        else{
            L.data[len++] = L2.data[j++];
        }
    }
    if (i == L1.length)
        for (; j < L2.length; j++)
            L.data[len++] = L2.data[j];
    else if (j == L2.length)
        for (; i < L1.length; i++)
            L.data[len++] = L1.data[i];
    
    L.length = len;
    return L;
    
}

//第八题，在一个一维数组中含有两个顺序表，实现两个顺序表的位置互换
//此问题若重新申请内存较为简单

SeqList T8_Inverse0(SeqList L, int s){ //s为第一个数组的长度
    SeqList new_L;
    new_L.data = (int*) malloc(L.length * sizeof(int));
    int len = 0;
    //插入后一部分
    for (int i = s; i < L.length; i++)
        new_L.data[len++] = L.data[i];
    //插入后一部分
    for (int j = 0; j < s; j++){
        new_L.data[len++] = L.data[j];
    }
    new_L.length = len;
    return new_L;

}

//还可以使用空间复杂度为O(1)的算法，先将所有的元素进行逆置，然后分别对前后对应的两个数组分别进行逆置

//首先编写一个逆置函数，实现区间内的逆置
void Reverse(SeqList *L, int m, int n){

    int temp, mid = (m + n) / 2;
    for (int i = m - 1; i < mid; i++){
        temp = L->data[i];
        L->data[i] = L->data[--n];
        L->data[n] = temp;
    }

}

//之后便可以先对整个数组逆置，然后分别对两组元素进行逆置,n为第一个数组的长度
SeqList T8_Inverse(SeqList L, int n){
    Reverse(&L, 1, L.length);
    Reverse(&L, 1, L.length - n);
    Reverse(&L, L.length - n + 1, L.length);
    return L;
}
//第九题
//在有序数组中查找元素，并且使其与后继元素交换。
//由于数组是有序的，可以使用二分法，将查找的时间复杂度降低到logn级别
int BinarySearch(SeqList L, int e){
    int left = 0;
    int right = L.length - 1;
    int mid;
    while (left <= right){ //注意：若将循环条件改成!=，在技术序列中没有影响
        mid = (left + right) / 2;
        if (L.data[mid] == e)
            return mid;
        else if (L.data[mid] < e)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
void T9_SearchOrInsert(SeqList *L, int e){
    int index = BinarySearch(*L, e);
    if (index != -1){
        if (index != L->length - 1){
            int temp = L->data[index];
            L->data[index] = L->data[index + 1];
            L->data[index + 1] = temp;
        }
    }
    else{
        int i = 0;
        while (true)
        {
            if (L->data[i++] > e){
                ListInsert(L, i, e);
                break;
            }
                
        }
        
    }
}

int main(){
    SeqList L;
    InitList(&L);
    // InitList(&L2);
    // InitList_Line(&L, 10);

    ListInsert(&L, 1, 0);
    ListInsert(&L, 2, 3);
    ListInsert(&L, 3, 5);
    ListInsert(&L, 4, 6);
    ListInsert(&L, 5, 9);
    IncreaseSize(&L, 2);
    printList(L);
    // printf("%d\n", L.length);
    printf("========\n"); 
    // printf("%d\n", BinarySearch(L, 0));
    // T9_SearchOrInsert(&L, 10);
    T9_SearchOrInsert(&L,10);
    printList(L);
    // Reverse(&L, 1, 9);
    // printList(T8_Inverse(L, 3));
    // printList(T8_Inverse(L, 3));
    // printList(T7_Merge(L1, L2));
    // printf("%d\n",T1_Del_Min(&L));
    // T2_Reverse(&L);
    // T3_Del_Value_3(&L, 2);
    // T4_Del_Range_2(&L, 5, 8);
    // T5_Del_Range_Unorder_1(&L, 1, 8);
    // T5_Del_Range_Unorder_2(&L, 1, 5);
    // T6_Del_Repeat_1(&L);
    // T6_Del_Repeat_2(&L);
    system("pause");
    return 0;

}
