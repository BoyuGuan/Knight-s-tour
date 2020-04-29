#include <iostream>
#include <vector>
#include "horse_run.h"

using namespace std;



int main()
{
	int x, y;
	cout << "Input begin coordinate x ,y.   8>=x ,y >=1 \n";
	cin >> x >> y;
	cout << "How many slotions do you want?\n";
	int num = 0;
	cin >> num;
	if (x <= 0 || x > len || y > len || y <= 0 || num <= 0)
	{
		cout << "input error";
		return 0;
	}
	x--, y--;
	int begin[2]{ x, y };
	let_Horse_Fly(begin, num);
}

