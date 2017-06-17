#include<iostream>
#include"tetris.h"
#include<windows.h>
#include<ctime>
#include <conio.h>
using namespace std;
void Box::SetColor(int colorID)
{
	int n_color;
	switch (colorID)
	{
	case 0: n_color = 0x08; break;
	case 1: n_color = 0x0C; break;
	case 2: n_color = 0x0D; break;
	case 3: n_color = 0x0E; break;
	case 4: n_color = 0x0A; break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n_color);
}
void Box::DrawMap()//画界面  
{
	int i;

	SetColor(0);//界面颜色  

	for (i = 0; i<14; i++)
	{
		SetPos(i * 2, 0);
		cout << "■";
	}
	for (i = 1; i <= 24; i++)
	{
		SetPos(0, i);
		cout << "■";
		SetPos(13 * 2, i);
		cout << "■";
	}
	for (i = 0; i<14; i++)
	{
		SetPos(i * 2, 24);
		cout << "■";
	}

	i = 15;
	for (i = 15; i <= 25; i++)
	{
		SetPos(i * 2, 0);
		cout << "■";
	}
	for (i = 1; i <= 8; i++)
	{
		SetPos(15 * 2, i);
		cout << "■";
		SetPos(25 * 2, i);
		cout << "■";
	}
	for (i = 15; i <= 25; i++)
	{
		SetPos(i * 2, 9);
		cout << "■";
	}

	SetPos(16 * 2, 16);
	cout << "俄罗斯方块";
	SetPos(16 * 2, 17);
	cout << "分数：" << point;
	SetPos(16 * 2, 18);
	cout << "级别：" << level;
}

void Box::DrawBox(int x, int y, int num)//绘制图形  
{
	int i;
	int nx, ny;
	if (num<2)SetColor(1);//0、1是长条  
	else if (num<3) SetColor(2);//2 方块  
	else if (num<11) SetColor(3);//3、4、5、6、7、8、9、10  
	else SetColor(4);
	for (i = 0; i<4; i++)
	{
		nx = x + sharp[num][i * 2];
		ny = y + sharp[num][i * 2 + 1];
		SetPos((ny + 1) * 2, nx + 1);//利用sharp数组相对于点x,y绘制形状  
									 //SetColor(i+1);  
		cout << "■";
	}
}

void Box::Redraw(int x, int y, int num)//擦除图形，原理同上  
{
	int i;
	int nx, ny;
	for (i = 0; i<4; i++)
	{
		nx = x + sharp[num][i * 2];
		ny = y + sharp[num][i * 2 + 1];
		SetPos((ny + 1) * 2, nx + 1);
		cout << " ";
	}
}

void Box::Turn()//转动图形，单纯的该ID而已  
{
	switch (ID)
	{
	case A1: ID = A2; break;
	case A2: ID = A1; break;

	case B: ID = B; break;

	case C11: ID = C12; break;
	case C12: ID = C13; break;
	case C13: ID = C14; break;
	case C14: ID = C11; break;

	case C21: ID = C22; break;
	case C22: ID = C23; break;
	case C23: ID = C24; break;
	case C24: ID = C21; break;

	case D11: ID = D12; break;
	case D12: ID = D11; break;

	case D21: ID = D22; break;
	case D22: ID = D21; break;
	}

}

void Box::Welcome()//欢迎界面  
{
	char x;
	while (1)
	{
		system("cls");
		cout << "■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "■        俄罗斯方块控制台版        ■" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "■     A,D左右移动  S向下加速       ■" << endl;
		cout << "■     W 转动方块   P暂停游戏       ■" << endl;
		cout << "■            Q退出游戏             ■" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■" << endl;
		cout << "■                                  ■" << endl;
		cout << "■        按1-9选择等级！！         ■" << endl;
		cout << "■                                  ■" << endl;
		cout << "■                                  ■" << endl;
		cout << "■■■■■■■■■■■■■■■■■■■" << endl;
		SetPos(16, 9);
		x = _getch();
		if (x <= '9'&&x >= '1')//设置等级  
		{
			level = x - '0';
			break;
		}
	}
}

void Box::UpdataMap()//更新画面（关键）  
{
	int clear;
	int i, j, k;
	int nx, ny;
	int flag;
	for (i = 0; i<4; i++)//更新map数组的信息  
	{
		nx = hotpoint[0] + sharp[ID][i * 2];
		ny = hotpoint[1] + sharp[ID][i * 2 + 1];
		map[nx][ny] = 1;
	}
	if (hotpoint[0]<top)//如果热点高于顶点则更新顶点,这里0表示的是纵向的  
		top = hotpoint[0];
	clear = 0;//消除的格数  
	for (i = hotpoint[0]; i<hotpoint[0] + high[ID]; i++)
	{
		flag = 0;
		for (j = 0; j<12; j++)//检测是否可以消除此行  
		{
			if (map[i][j] == 0)//代表有空格，不能消除  
			{
				flag = 1;//1表示不能消除  
				break;
			}
		}
		if (flag == 0)//可以消除  
		{
			for (k = i; k >= top; k--)//从当前位置向上所有的点下移一行  
			{
				if (k == 0)//最高点特殊处理  
					for (j = 0; j<12; j++)
					{
						map[k][j] = 0;
						SetPos((j + 1) * 2, k + 1);
						cout << " ";
					}
				else
				{
					for (j = 0; j<12; j++)
					{
						map[k][j] = map[k - 1][j];
						SetPos((j + 1) * 2, k + 1);
						if (map[k][j] == 0)
							cout << " ";
						else
							cout << "■";
					}
				}
			}
			top++;//消除成功，最高点下移  
			clear++;
			point += clear * 10 * level;
		}
	}
	SetColor(0);
	SetPos(16 * 2, 17);
	cout << "分数：" << point;
}

void Box::Run()//运行游戏  
{
	int i = 0;
	char x;
	int Count;//计数器  
	int nextID;
	int temp;
	srand((int)time(0));//将随机数的起点设置为time（0）：不带秒  
	ID = rand() % 15;//随机生成ID和下一个ID  
	nextID = rand() % 15;//这里为了方便，其实每个形状不是等概率生成的  
	DrawBox(hotpoint[0], hotpoint[1], ID);//绘制图形  
	DrawBox(3, 17, nextID);
	Count = 1000 - level * 100;//等级决定计数，这里是用Count控制时间，来控制下落的速度  
	while (1)
	{
		if (i >= Count)
		{
			i = 0;//计数器清零  
			if (Judge(hotpoint[0] + 1, hotpoint[1]))//如果下个位置无效（即到底）  
			{
				UpdataMap();//更新画面  
				ID = nextID;//生成新ID，用原等待ID替换为当前ID  
				hotpoint[0] = 0;//热点更新  
				hotpoint[1] = 5;
				Redraw(3, 17, nextID);
				nextID = rand() % 15;
				DrawBox(hotpoint[0], hotpoint[1], ID);
				DrawBox(3, 17, nextID);
				if (Judge(hotpoint[0], hotpoint[1]))//无法绘制开始图形，游戏结束  
				{
					//getch();  
					system("cls");
					SetPos(25, 15);
					cout << "游戏结束！！！最终得分为：" << point << endl;
					system("pause");//就是在命令行上输出一行类似于“Press   any   key   to   exit”  
					exit(0);//关闭所有文件，退出正在执行的程序，返回0代表正常结束  
				}
			}
			else
			{
				Redraw(hotpoint[0], hotpoint[1], ID);//没有到底，方块下移一位  
				hotpoint[0]++;//热点下移  
				DrawBox(hotpoint[0], hotpoint[1], ID);
			}
		}
		if (_kbhit())//读取键盘信息  
		{
			x = _getch();
			if (x == 'a' || x == 'A')//左移  
			{
				if (Judge(hotpoint[0], hotpoint[1] - 1) == 0)
				{
					Redraw(hotpoint[0], hotpoint[1], ID);
					hotpoint[1] -= 1;
					DrawBox(hotpoint[0], hotpoint[1], ID);
				}
			}
			if (x == 'd' || x == 'D')//右移  
			{
				if (Judge(hotpoint[0], hotpoint[1] + 1) == 0)
				{
					Redraw(hotpoint[0], hotpoint[1], ID);
					hotpoint[1] += 1;
					DrawBox(hotpoint[0], hotpoint[1], ID);
				}
			}
			if (x == 's' || x == 'S')//向下加速！！！！！！！！此处可以改进，可以改进加速效果。改成+3之后，会出现BUG，最后几个无法加速  
			{
				if (Judge(hotpoint[0] + 3, hotpoint[1]) == 0)
				{
					Redraw(hotpoint[0], hotpoint[1], ID);
					hotpoint[0] += 1;
					DrawBox(hotpoint[0], hotpoint[1], ID);
				}
			}
			if (x == 'w' || x == 'W')//转动方块  
			{
				temp = ID;
				Turn();
				if (!Judge(hotpoint[0], hotpoint[1]))
				{
					Redraw(hotpoint[0], hotpoint[1], temp);
					DrawBox(hotpoint[0], hotpoint[1], ID);
				}
				else
					ID = temp;
			}
			if (x == 'p' || x == 'P')
			{
				//getch();  
				//system("cls");  
				Pause();
			}
			if (x == 'q' || x == 'Q')
			{
				system("cls");
				SetPos(25, 15);
				cout << "游戏结束！！！最终得分为：" << point << endl;
				system("pause");
				exit(0);
			}
			while (_kbhit())//读掉剩下的键盘信息  
				_getch();
		}
		Sleep(1);//等待1毫秒  
		i++;//计数器加1  
	}
}

bool Box::Judge(int x, int y)//判断当前是否可以绘制方块  
{
	int i;
	int nx, ny;
	for (i = 0; i<4; i++)
	{
		nx = x + sharp[ID][i * 2];
		ny = y + sharp[ID][i * 2 + 1];
		if (nx<0 || nx >= 23 || ny<0 || ny >= 12 || map[nx][ny] == 1)//不能，返回1  
			return 1;
	}
	return 0;
}
void Box::Pause()
{
	system("cls");
	while (1)
	{
		SetPos(30, 13);
		cout << "暂停等待，咖啡时间^-^" << endl;
		if (_getch() == 'p' || _getch() == 'P')
			break;
	}
	SetPos(30, 13);
	cout << "                            " << endl;
	DrawMap();
	int i, j;
	for (i = 0; i<23; i++)
		for (j = 0; j<12; j++)
			if (map[i][j] == 1)
			{
				SetPos((j + 1) * 2, i + 1);
				cout << "■";
			}
}
void main()//主函数  
{
	Box game;
	game.Welcome();
	system("cls");
	game.DrawMap();
	game.Run();
}
