#include "stack.h"

void InitStack_Sq(Stack& S, int maxsize, int incresize)

{
	S.stack = (int*)malloc(maxsize * 2 * sizeof(int)); // 为顺序栈分配初始存储空间
	if (!S.stack)  exit(1);                                // 存储空间分配失败
	S.top = -1;                                            // 置栈空
	S.stacksize = maxsize;                                 // 顺序栈的当前容量
	S.incrementsize = incresize;                           // 增补空间
}

int StackLength_Sq(Stack S)
{
	return S.top + 1;
}

bool Push(Stack& S, int* e)

{  //在顺序栈的栈顶插入元素e
	if (S.top == S.stacksize - 1) {
		S.stack = (int*)realloc(S.stack, (S.stacksize + S.incrementsize) * sizeof(int)); // 栈满，给顺序栈增补空间
		if (!S.stack)     return false;                // 分配存储空间失败
		S.stacksize += S.incrementsize;
	}
	S.stack[++S.top] = *e;                             // 栈顶指针上移，元素e进栈
	S.stack[++S.top] = *(e + 1);
	return true;
}

bool Pop(Stack& S)// Pop_Sq
{   // 删除顺序栈栈顶元素
	if (S.top == -1)  return false;
	S.top -= 2;
	return true;
}

bool GetTop(Stack S, int* e)
{   
	if (S.top == -1)  return false;
	*(e + 1) = S.stack[S.top];
	*e = S.stack[S.top - 1];
	return true;
}
bool StackEmpty_Sq(Stack S)
{
	if (S.top == -1)  return true;
	else return false;
}

void pop_And_Return(Stack& S, int* e)
{
	*(e + 1) = S.stack[S.top--];
	*e = S.stack[S.top--];
}
// StackEmpty_Sq