//1.实现基本功能：碰撞检测，砖块消除，胜利提示
//2.实现一个进阶功能：掉落加长挡板包，概率为20%，同时打掉15个方块时一定会掉一个。


#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include<iostream>
#include<random>
using namespace std;

default_random_engine e;
uniform_real_distribution<float> u(0.0, 10.0);
int cell_x, cell_y;
bool lenth_change = false;


bool add_cell(int x,int y) 
{
	cell_x = x, cell_y = y;
	int width = 40, height = 40;
		setlinecolor(RGB(255, 215, 0));
		setfillcolor(RGB(255, 215, 0));
		fillrectangle(cell_x, cell_y, cell_x+width, cell_y+height);
		return true;
}

void add_lenth(int bx,int &len )
{
	if (!lenth_change)
	{
		int cell_vy = 10;
		int width = 40, height = 40;
		cell_y += cell_vy;
		setlinecolor(RGB(255, 215, 0));
		setfillcolor(RGB(255, 215, 0));
		fillrectangle(cell_x, cell_y, cell_x + width, cell_y + height);
		if (cell_y + height > 760 && cell_x + width > bx && cell_x < bx + len)
		{
			len += 50;
			lenth_change = true;
			setlinecolor(RGB(200, 200, 200));
			setfillcolor(RGB(200, 200, 200));
			fillrectangle(cell_x, cell_y, cell_x + width, cell_y + height);
		}
	}
}

int main()
{
	int r = 10;
	int x = 300, y = 750;	//小球坐标
	int vx = 8, vy = -10;	//小球速度
	int i, j;
	int w = 90, h = 40;		//砖块长、宽
	int xs, ys;
	int gap = 5;	//砖块间距
	int bx = 250, len = 100, th = 15;	//板子长宽
	bool s = false;		//游戏开始标志
	bool f = false;		//按空格重新开始
	bool re = false;	//小球撞到砖块
	bool bricks_hit[128] = { false };
	int count = 0;
	int brick_left, brick_top, brick_right, brick_bottom;

	initgraph(600, 800);

	setbkcolor(RGB(200, 200, 200));
	setlinecolor(RGB(0, 128, 128));
	setfillcolor(RGB(0, 128, 128));
	cleardevice();

	BeginBatchDraw();
	while (1)
	{
		if (re)
		{
			add_lenth(bx,len);
		}
		setfillcolor(RGB(0, 128, 128));
		for (i = 0; i < 6; i++) // create a 6 * 5 matrix
			for (j = 0; j < 5; j++)
			{
				setfillcolor(RGB(0, 128, 128));
				setlinecolor(RGB(0, 128, 128));
				if (count == 30)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(60, 0, _T("Arial"));
					outtextxy(270, 400, _T("Win"));
					break;
				}
				xs = i * w;
				ys = j * h;
				brick_left = gap * (i + 1) + xs;
				brick_top = gap * (j + 1) + ys; 
				brick_right = gap * (i + 1) + xs + w;
				brick_bottom = gap * (j + 1) + ys + h;
				//小球撞击砖块上下面
				if ((y - r< brick_bottom && x + r<brick_right && x - r > brick_left)&&brick_bottom-y<=h)
				{
					if (!bricks_hit[i*10+j])
					{
						bricks_hit[i * 10 + j] = true;
						vy = -vy;
						count++;
						if (u(e) < 5 || count == 15 )
						{
							re = add_cell(brick_left,brick_top);
						}
					}
				}
				//小球撞击砖块左右面
				if (x - r < brick_right && y + r<brick_bottom && y - r>brick_top&&x-brick_left<=w&&x-brick_left>0)
				{
					if (!bricks_hit[i * 10 + j])
					{
						bricks_hit[i * 10 + j] = true;
						vx = -vx;
						count++;
						if (u(e) < 5 || count == 15 )
						{
							re= add_cell(brick_left, brick_top);
						}
					}
				}

				if (bricks_hit[i * 10 + j])
				{
					setfillcolor(RGB(200, 200, 200));
					setlinecolor(RGB(200, 200, 200));
					fillrectangle(gap * (i + 1) + xs, gap * (j + 1) + ys, gap * (i + 1) + xs + w, gap * (j + 1) + ys + h);
					continue;
				}
				fillrectangle(gap * (i + 1) + xs, gap * (j + 1) + ys, gap * (i + 1) + xs + w, gap * (j + 1) + ys + h);
			}

		setfillcolor(RGB(0, 0, 128));
		fillrectangle(bx, 760, bx + len, 760 + th); // draw the board

		if (_kbhit())
		{
			char input = _getch();
			if (input == ' ')
			{
				s = true; // game start
				f = true;
			}
			if (GetAsyncKeyState(VK_LEFT))
			{
				bx = bx - 8;
				if (bx <= 0)
					bx = 0;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				bx = bx + 8;
				if (bx >= 600)
					bx = 600;
			}
		}
		if (!s)  //  before game has been started
		{
			setfillcolor(RGB(128, 0, 0));
			fillcircle(bx + len / 2, 760 - r, r);
		}
		else  //  after game has been started
		{
			if ((((y > 750) && (y < 800)) && (x + r >= bx) && (x - r <= bx + len))||y<r)
				vy = -vy;
			if ((x > 600 - r) || (x < r))
				vx = -vx;
			if (f) // initial position of the ball
			{
				x = bx + len / 2;
				y = 760 - r;
				f = !f;
			}
			else  // the position of the ball during the game
			{
				x = x + vx;
				y = y + vy;
				if (y >= 800&&count<30)
				{
					settextcolor(RGB(0, 0, 255));
					settextstyle(60, 0, _T("Arial"));
					outtextxy(270, 400, _T("Lose"));
					// break;
				}
			}
			setfillcolor(RGB(128, 0, 0));
			fillcircle(x, y, r);
		}

		FlushBatchDraw();
		Sleep(30);
		cleardevice();
	}
	closegraph();
	return 0;
}