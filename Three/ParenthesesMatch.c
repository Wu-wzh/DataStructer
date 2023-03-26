#include <stdio.h>
#include <windows.h>
#define true 1;
#define false 0;

//À¨ºÅÆ¥Åä
typedef struct LinkNode{
    char data;
    struct LinkNode* next;
}LinkNode, *LStatic;

int InitStack(LStatic* S){
    *S = (LinkNode*) malloc(sizeof(LinkNode));
    if (*S == NULL) return false;
    (*S)->next = NULL;
    return true;
}
int Push(LStatic* S, char x){ 
    if (*S == NULL) return false;
    LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
    t->data = x;
    t->next = (*S)->next;
    (*S)->next = t;
    return true;
}
int Pop(LStatic* S, char *x){
    if ((*S)->next == NULL) return false;

    LinkNode* p = (*S)->next;
    *x = p->data;
    (*S)->next = p->next;
    free(p);
    return true;
}
void printStatic(LStatic S){
    LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
    t = S->next;
    while (t != NULL)
    {
        printf("%c\n",t->data);
        t = t->next;
    }
    
}

int isEmpty(LStatic S){
    return S->next == NULL;
}

int Match(char str[]){
    LStatic S;
    InitStack(&S);
    int len = strlen(str);
    for (int i = 0; i < len; i++){
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
            Push(&S, str[i]);
        else{
            if (isEmpty(S)) return false;
            char top;
            Pop(&S, &top);
            if (str[i] == '(' && top != ')') return false;
            if (str[i] == '[' && top != ']') return false;
            if (str[i] == '{' && top != '}') return false;
        }
    }

    return isEmpty(S);
    
}
int main(){
    LStatic S;
    InitStack(&S);
    printStatic(S);
    char str[] = "({})";
    printf("%d\n", Match(str));
    system("pause");
    return 0;
}