#pragma once
#include <stdlib.h>
#define STACK_INIT_SIZE 200
typedef struct
{
	int x;
	int y;
}Costepsinate;



typedef struct
{
	int steps;
	Costepsinate seat; //зјБъ
	int di;
}node;

typedef struct
{
	node* base;
	node* top;
	int stacksize;
}Stack;

int  InitStack(Stack* s1);

node Pop(Stack* s, node m);

int Push(Stack* s1, node m);

int StackEmpty(Stack* s);