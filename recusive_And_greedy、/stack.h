#pragma once
#include <stdlib.h>
# define STACK_INIT_SIZE  100      // 顺序栈 (默认的)的初始分配最大容量
# define STACKINCREMENT  10        // (默认的)增补空间量

typedef struct {
	int* stack;                  // 存储数据元素的一维数组
	int top;                         // 栈顶指针
	int stacksize;                   // 当前分配的数组容量（以int为单位）
	int incrementsize;	           // 增补空间量（以int为单位）
}Stack;

void InitStack_Sq(Stack& S, int maxsize = STACK_INIT_SIZE, int incresize = STACKINCREMENT);// InitStack_Sq

int StackLength_Sq(Stack S);// StackLength_Sq


bool Push(Stack& S, int* e);// Push_Sq

bool Pop(Stack& S);

bool GetTop(Stack S, int* e);//取顺序栈栈顶元素，并让e返回其值

bool StackEmpty_Sq(Stack S);

void pop_And_Return(Stack& S, int* e);