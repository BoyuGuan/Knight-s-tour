#include "horse_run.h"
#include <iostream>

bool pass(int pos[], bool board[][len])
{
	if (pos[0] >= 0 && pos[0] < len && pos[1] >= 0 && pos[1] < len && !board[pos[0]][pos[1]])
		return 1;
	return 0;
}

int add[len*2]{ -2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2,-2 ,-1 };
int found = 0;


void greedy_sort(int cur[], int gre[], bool board[][len])
{
	int cnt[8]{ -1,-1,-1,-1,-1,-1,-1,-1 };
	int nex[2] ;
	for (size_t i = 0; i < 8; i++)
	{
		nex[0] = cur[0] + add[2 * i];
		nex[1] = cur[1] + add[2 * i + 1];
		if ( pass(nex,board))
		{
			cnt[i]++;
			int nex_nex[2];
			for (size_t j = 0; j < 8; j++)
			{
				nex_nex[0] = nex[0] + add[2 * j];
				nex_nex[1] = nex[1] + add[2 * j +1];
				if (pass(nex_nex, board))
					cnt[i]++;
			}
		}
	}
	for (size_t i = 0; i < 8; i++)
	{
		for (int j = i + 1; j < 8; j++) {
			if (cnt[j] < cnt[i])
			{
				int tem = cnt[j];
				cnt[j] = cnt[i];
				cnt[i] = tem;
				tem = gre[j];
				gre[j] = gre[i];
				gre[i] = tem;
			}
		}
	}
}

void find_The_Way(bool board[][len], int& steps, Stack& way )
{
	if (steps >= len * len +1) 
		return;
	int cur[2];
	GetTop(way, cur);
	if (!pass(cur,board) )
		return; // 不符题意
	board[cur[0]][cur[1]] = 1; 
	int gre[8]{ 0,1,2,3,4,5,6,7 };
	greedy_sort(cur, gre, board);
	/* 以下是穷举的8种可能的情况： */
	for (size_t i = 0; i < 8; i++)
	{
		int ii = gre[i];
		int nex[2];
		nex[0] = cur[0] + add[ 2*ii];
		nex[1] = cur[1] + add[ 2*ii+1];
		Push(way, nex);
		steps++;
		find_The_Way(board, steps , way);
		if (steps >= len*len +1)
			 return;
		Pop(way);
		steps--;
	}
	board[cur[0]][cur[1]] = 0; // 此位置清空，没有走马
}

void let_Horse_Fly(int pos[])
{
	bool board[len][len]{0};
	Stack way; InitStack_Sq(way);
	Push(way, pos);
	int steps = 1; 
	find_The_Way(board, steps, way);
	Pop(way);
	Stack re; InitStack_Sq(re);
	
	for (size_t i = 0; i < 64; i++)
	{
		int tem[2];
		pop_And_Return(way, tem);
		Push(re, tem);
	}
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int tem[2];
			pop_And_Return(re, tem);
			std::cout <<" "<< tem[0]+1 << ' ' << tem[1]+1<<" ->";
		}
		std::cout<< std::endl;
	}
}
