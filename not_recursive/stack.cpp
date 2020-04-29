#include "stack.h"

int InitStack(Stack* s1)
{
	s1->base = (node*)malloc(STACK_INIT_SIZE * sizeof(node));
	if (!s1->base)
		exit(1);
	s1->top = s1->base;
	s1->stacksize = STACK_INIT_SIZE;
	return (1);
}

node Pop(Stack* s, node m){
	m = *(--s->top);
	return m;
}

int Push(Stack* s1, node m)
{
	*(s1->top++) = m;
	return 1;
}

int StackEmpty(Stack* s){
	if (s->base == s->top)
		return (1);
	else
		return (0);
}