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
	int cnt[8]{ -1,-1,-1,-1,-1,-1,-1,-1 }; //ÿ�����������ߵ���Ŀ����ʼֵ��Ϊ-1
	int nex[2];
	for (size_t i = 0; i < 8; i++)
	{
		nex[0] = cur[0] + add[2 * i];
		nex[1] = cur[1] + add[2 * i + 1]; //8����һ�����ܵ�λ��
		if (pass(nex, board)) //��������һ��λ�úϷ�
		{
			cnt[i]++; //������һ
			int nex_nex[2];
			for (size_t j = 0; j < 8; j++)
			{				
				//������һ��λ��Ϊ�����㣬����һ��λ�õ���һ��λ�õ�8�����λ�úϷ������
				nex_nex[0] = nex[0] + add[2 * j];
				nex_nex[1] = nex[1] + add[2 * j + 1];
				if (pass(nex_nex, board))
					cnt[i]++; 
			}
		}
	}
	for (size_t i = 0; i < 8; i++) //�򵥵�ð��������ÿ�������Ͽ���ȥ��λ������ָ�꣬�Է������������ȥ�ĵط������ǰ������ջ
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
	if (size >= num) //�������������˾͸Ͻ��ˣ����ٹ�ʣ�µ���
		return; 
	int cur[2];
	GetTop(way, cur); //��ǰλ������
	if (!pass(cur, board)) // ���λ�÷���������
		return; 
	if (steps >= len * len) {   //����������ô��
		size++;   //�������1
		outputway(way, re, size); //���·��
		return;
	}
	board[cur[0]][cur[1]] = 1; //������ط����һ���߹���
	int gre[8]{ 0,1,2,3,4,5,6,7 };   //��̰���㷨����һ���ߵķ���ķ�������
	greedy_sort(cur, gre, board);  //��̰���㷨����һ����������
	for (size_t i = 0; i < 8; i++)	//����̰���㷨�������˳������¸�����
	{
		int ii = gre[i]; //iiΪ��һ������Ĵ���
		int nex[2];
		nex[0] = cur[0] + add[2 * ii];
		nex[1] = cur[1] + add[2 * ii + 1];
		Push(way, nex); //���¸�λ����ջ
		steps++; //����+1
		find_The_Way(board, steps, way, num, size,  re); //��һ��Ϊ�µĳ����㣬
		if (size >= num) //�������������˾͸Ͻ��ˣ����ٹ�ʣ�µ���
			return;
		Pop(way);
		steps--;
	}
	board[cur[0]][cur[1]] = 0; // ��λ����գ�û������
}

void let_Horse_Fly(int pos[], int num)
{
	int* re = (int*)calloc(num * 2 * 64, sizeof(int)); //Ϊ�𰸷���ռ�
	bool board[len][len]{  }; //�����ȡ����ȵ����̣�����ȫ��0�Ա�ʾû����
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
