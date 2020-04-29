#pragma once
#include "stack.h"

#define  len  8  //行列数

void find_The_Way(bool board[][len], int& steps, Stack& way, int num, int& size, int* re);//找路函数

void  let_Horse_Fly(int pos[], int num);//启动函数

