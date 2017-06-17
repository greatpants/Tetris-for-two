#ifndef TETRIS_H_
#define TETRIS_H_
#include <windows.h>

#define A1 0//A代表长条型，B为方块，C为L型，D为闪电型  
#define A2 1  

#define B 2  

#define C11 3  
#define C12 4  
#define C13 5  
#define C14 6  

#define C21 7  
#define C22 8  
#define C23 9  
#define C24 10  

#define D11 11  
#define D12 12  

#define D21 13  
#define D22 14  

void SetPos(int i, int j)//设定光标位置  
{
	COORD pos = { i,j };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

const int sharp[15][8] =
{
	{ 0,0,1,0,2,0,3,0 },{ 0,0,0,1,0,2,0,3 },
	{ 0,0,1,0,0,1,1,1 },
	{ 0,0,1,0,1,1,1,2 },{ 0,1,1,1,2,0,2,1 },{ 0,0,0,1,0,2,1,2 },{ 0,0,0,1,1,0,2,0 },
	{ 1,0,1,1,1,2,0,2 },{ 0,0,0,1,1,1,2,1 },{ 0,0,0,1,0,2,1,0 },{ 0,0,1,0,2,0,2,1 },
	{ 0,0,0,1,1,1,1,2 },{ 0,1,1,0,1,1,2,0 },
	{ 0,1,0,2,1,0,1,1 },{ 0,0,1,0,1,1,2,1 }
};//形状点的各个坐标，先纵后横  


const int high[15] = { 4,1,2,2,3,2,3,2,3,2,3,2,3,2,3 };//这个数组是用来保存各个形状高度的，以上面的坐标相对应 

class Box
{
private:
	int map[23][12];//画面坐标，记录有方块的点，也是游戏界面  
	int hotpoint[2];//当前活动的点，所有图形都是以此为基准绘制的  
	int top;//当前最高位置  
	int point;//分数  
	int level;//等级  
	int ID;//当前活动图形的ID号  
	int colorID;//图形的颜色ID。  
public:
	Box()//初始化  
	{
		int i, j;
		for (i = 0; i<23; i++)
			for (j = 0; j<12; j++)
				map[i][j] = 0;
		hotpoint[0] = 0;
		hotpoint[1] = 5;
		point = 0;
		level = 1;
		top = 99;
		ID = 0;
	}
	void SetColor(int color);//颜色  
	void DrawMap();//画游戏的大界面  
	bool Judge(int x, int y);//判断当前位置能否绘制图形  
	void Welcome();//欢迎界面  
	void DrawBox(int x, int y, int num);//绘制图形  
	void Redraw(int x, int y, int num);//擦除图形  
	void Run();//运行  
	void Turn();//转动方块  
	void UpdataMap();//更新画面  
	void Pause();//暂停  
};

#endif // !TETRIS_H_
