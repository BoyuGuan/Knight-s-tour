#include "horse_run.h"
#include <iostream>

bool pass(int pos[], bool board[][len])
{
	if (pos[0] >= 0 && pos[0] < len && pos[1] >= 0 && pos[1] < len && !board[pos[0]][pos[1]])
		return 1;
	return 0;
}

int add[len * 2]{ -2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2,-2 ,-1 };
int found = 0;


void greedy_sort(int cur[], int gre[], bool board[][len])
{
	int cnt[8]{ -1,-1,-1,-1,-1,-1,-1,-1 }; //每个方向上能走的数目，初始值设为-1
	int nex[2];
	for (size_t i = 0; i < 8; i++)
	{
		nex[0] = cur[0] + add[2 * i];
		nex[1] = cur[1] + add[2 * i + 1]; //8个下一个可能的位置
		if (pass(nex, board)) //如果这个下一个位置合法
		{
			cnt[i]++; //计数加一
			int nex_nex[2];
			for (size_t j = 0; j < 8; j++)
			{				
				//再以下一个位置为出发点，求下一个位置的下一个位置的8种情况位置合法的情况
				nex_nex[0] = nex[0] + add[2 * j];
				nex_nex[1] = nex[1] + add[2 * j + 1];
				if (pass(nex_nex, board))
					cnt[i]++; 
			}
		}
	}
	for (size_t i = 0; i < 8; i++) //简单的冒泡排序，用每个方向上可能去的位置数做指标，对方向进行排序，能去的地方多的排前边先入栈
		for (int j = i + 1; j < 8; j++) 
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

void outputway(Stack way, int* re, int size) {
	for (int i = 63; i >= 0; i--)
	{
		int pos[2];
		pop_And_Return(way, pos);
		re[(size - 1) * 64*2 + 2 * i] = pos[0];
		re[(size - 1) * 64*2 + 2 * i + 1] = pos[1];
	}
}


void find_The_Way(bool board[][len], int& steps, Stack& way, int num, int& size, int* re)
{
	if (size >= num) //如果解的数量够了就赶紧退，不再管剩下的了
		return; 
	int cur[2];
	GetTop(way, cur); //当前位置坐标
	if (!pass(cur, board)) // 这个位置符不符题意
		return; 
	if (steps >= len * len) {   //棋盘走完了么？
		size++;   //解个数加1
		outputway(way, re, size); //输出路径
		return;
	}
	board[cur[0]][cur[1]] = 1; //把这个地方标记一下走过了
	int gre[8]{ 0,1,2,3,4,5,6,7 };   //用贪心算法求下一步走的方向的方向数组
	greedy_sort(cur, gre, board);  //用贪心算法给下一步方向排序
	for (size_t i = 0; i < 8; i++)	//按照贪心算法求出来的顺序穷举下个方向
	{
		int ii = gre[i]; //ii为下一个方向的代号
		int nex[2];
		nex[0] = cur[0] + add[2 * ii];
		nex[1] = cur[1] + add[2 * ii + 1];
		Push(way, nex); //将下个位置入栈
		steps++; //步数+1
		find_The_Way(board, steps, way, num, size,  re); //下一步为新的出发点，
		if (size >= num) //如果解的数量够了就赶紧退，不再管剩下的了
			return;
		Pop(way);
		steps--;
	}
	board[cur[0]][cur[1]] = 0; // 此位置清空，没有走马
}

void let_Horse_Fly(int pos[], int num)
{
	int* re = (int*)calloc(num * 2 * 64, sizeof(int)); //为答案分配空间
	bool board[len][len]{  }; //建长度×长度的棋盘，并且全置0以表示没来过
	Stack way; InitStack_Sq(way);
	Push(way, pos);
	int steps = 1;
	int size = 0;
	find_The_Way(board, steps, way, num, size, re);
	for (size_t i = 0; i < num; i++)
	{
		std::cout << "The " << i + 1 << "th sloution is:\n" ;
		for (size_t j = 0; j < 8; j++)
		{
			for (size_t k = 0; k < 8; k++)
				std::cout << re[i * 64 * 2 + 2 * 8 *j + 2*k] + 1<< " " << re[i * 64 * 2 + 2 * 8*j + 2*k + 1]+1 << "  ->   ";
			std::cout << "\n";
		}
	}
}
