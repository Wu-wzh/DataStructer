#include <stdio.h>
#include <windows.h>
#define true 1
#define false 0

// 队列元素结构体
typedef struct deque_node {
    int value;
    struct deque_node *prev;
    struct deque_node *next;
} deque_node;

// 双端队列结构体
typedef struct deque {
    deque_node *front;
    deque_node *rear;
    int size;
    int capacity;
} deque;

// 初始化双端队列
void init_deque(deque *d, int capacity) {
    d->front = NULL;
    d->rear = NULL;
    d->size = 0;
    d->capacity = capacity;
}

// 判断双端队列是否为空
int is_empty(deque *d) {
    return d->front == NULL;
}

// 判断双端队列是否已满
int is_full(deque *d) {
    return d->size == d->capacity;
}

// 将元素插入到双端队列头部
void push_front(deque *d, int value) {
    if (is_full(d)) {
        printf("deque is full\n");
        exit(1);
    }
    deque_node *node = (deque_node *)malloc(sizeof(deque_node));
    node->value = value;
    node->prev = NULL;
    node->next = d->front;
    if (is_empty(d)) {
        d->rear = node;
    } else {
        d->front->prev = node;
    }
    d->front = node;
    d->size++;
}

// 将元素插入到双端队列尾部
void push_back(deque *d, int value) {
    if (is_full(d)) {
        printf("deque is full\n");
        exit(1);
    }
    deque_node *node = (deque_node *)malloc(sizeof(deque_node));
    node->value = value;
    node->prev = d->rear;
    node->next = NULL;
    if (is_empty(d)) {
        d->front = node;
    } else {
        d->rear->next = node;
    }
    d->rear = node;
    d->size++;
}

// 从双端队列头部弹出元素
int pop_front(deque *d) {
    if (is_empty(d)) {
        printf("deque is empty\n");
        exit(1);
    }
    deque_node *node = d->front;
    int value = node->value;
    d->front = node->next;
    if (d->front == NULL) {
        d->rear = NULL;
    } else {
        d->front->prev = NULL;
    }
    free(node);
    d->size--;
    return value;
}

// 从双端队列尾部弹出元素
int pop_back(deque *d) {
    if (is_empty(d)) {
        printf("deque is empty\n");
        exit(1);
    }
    deque_node *node = d->rear;
    int value = node->value;
    d->rear = node->prev;
    if (d->rear == NULL) {
        d->front = NULL;
    } else {
        d->rear->next = NULL;
    }
    free(node);
    d->size--;
    return value;
}

// 获取双端队列头部元素的值
int peek_front(deque *d) {
if (is_empty(d)) {
printf("deque is empty\n");
exit(1);
}
return d->front->value;
}

// 获取双端队列尾部元素的值
int peek_back(deque *d) {
if (is_empty(d)) {
printf("deque is empty\n");
exit(1);
}
return d->rear->value;
}

// 获取双端队列的大小
int get_size(deque *d) {
return d->size;
}

// 获取双端队列的容量
int get_capacity(deque *d) {
return d->capacity;
}

// 删除双端队列中的指定值
void delete_value(deque *d, int value) {
deque_node *node = d->front;
while (node != NULL) {
if (node->value == value) {
if (node->prev == NULL) {
d->front = node->next;
} else {
node->prev->next = node->next;
}
if (node->next == NULL) {
d->rear = node->prev;
} else {
node->next->prev = node->prev;
}
deque_node *tmp = node;
node = node->next;
free(tmp);
d->size--;
} else {
node = node->next;
}
}
}

int main() {
deque d;
init_deque(&d, 10);
// 测试受限操作
printf("testing restricted operations...\n");
for (int i = 1; i <= 10; i++) {
    push_back(&d, i);
}
printf("%d\n", peek_front(&d)); // 1
printf("%d\n", peek_back(&d)); // 10
printf("%d\n", get_size(&d)); // 10
delete_value(&d, 5);
printf("%d\n", get_size(&d)); // 9
for (int i = 1; i <= 9; i++) {
    pop_front(&d);
}
printf("%d\n", is_empty(&d)); // true
system("pause");
return 0;
}
