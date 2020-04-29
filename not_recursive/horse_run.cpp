#include "horse_run.h"

Costepsinate move[8] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };

inline bool Pass(Costepsinate pos,int board[][8])
{
	if (!board[pos.x][pos.y]&& (pos.x <= 7) && (pos.x >= 0)&& (pos.y <= 7) && (pos.y >= 0))
		return 1;
	else
		return 0;
}

Costepsinate NextPos(Costepsinate s, int i)
{
	s.x = s.x + move[i].x;
	s.y = s.y + move[i].y;
	return(s);
}

void let_Horse_Fly(Costepsinate start, int board[][8])
{
	int step = 0;
	Stack way;
	node top_tem;
	Costepsinate curpos = start;
	InitStack(&way);

	do
	{
		if (Pass(curpos,board))
		{
			step++;
			board[curpos.x][curpos.y] = step;
			top_tem.seat = curpos;
			top_tem.steps = step;
			top_tem.di = 0;
			Push(&way, top_tem);
			if (step == 64)
				break;
			else
				curpos = NextPos(curpos, top_tem.di);
		}
		else
		{
			if (!StackEmpty(&way))
			{
				Pop(&way, top_tem); //往前回溯
				while (top_tem.di == 7 && !StackEmpty(&way))
				{
					board[top_tem.seat.x][top_tem.seat.y] = 0;//恢复原态
					top_tem = Pop(&way, top_tem);	 //往前回溯
					step = top_tem.steps;			//恢复原态
				}
				if (top_tem.di < 7) //穷举所有可能
				{
					top_tem.di++;
					Push(&way, top_tem);
					curpos = NextPos(top_tem.seat, top_tem.di);
				}
			}
		}
	} while (!StackEmpty(&way));
}



