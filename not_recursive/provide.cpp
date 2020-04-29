#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include"horse_run.h"

using namespace std;



int main()
{
	Costepsinate start;
	cout<<"请输入初始位置\n";
	cin >> start.x;
	cin >> start.y;
	start.x -= 1;
	start.y -= 1;
	int board[8][8] = { 0 };
	let_Horse_Fly(start,board);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			printf("%4d", board[i][j]);
		printf("\n");
	}
	return 0;
}
