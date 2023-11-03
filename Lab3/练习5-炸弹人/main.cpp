/*实现功能：
* 1.小球与砖块的碰撞检测
* 2.炸弹的放置：按下空格放置，黑色的是炸弹，没拣道具前，最多可以放两个。
* 3.炸弹的爆炸：爆炸范围是一个十字形，横纵分别占150个像素（三个障碍物），可以炸掉砖块，但炸不掉墙。炸弹放置一段时间后自动爆炸（刷新20遍的时候，20*100ms=2s）。炸弹可以消灭敌人。
* 4.敌人随机生成。
* 5.敌人的移动与跟随：敌人会向玩家处移动，移动路径随机。
* 6.胜负机制：a.胜利：消灭三个敌人或者炸掉砖块捡到钥匙；b.失败：被敌人碰到。输赢均有显示。
* 7.道具机制：砖块会掉落道具，道具在哪个砖块中是随机的，一共有三个道具。
* 8.掉落道具：a.钥匙（白色）拾取即为胜利；b.加速（蓝色），拾取后小球速度+5；c.增加炸弹（青色），拾取后能多放一个炸弹
*/
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include<ctime>

//用户创建头文件，定义实现都在里面
#include"Enemy.h"
#include"Bomb.h"

using namespace std;

#define BLOCKWIDTH 50 //每个障碍物占50个像素
#define ODD(x) ((x/50)%2)	//算是不是奇数

//道具定义
#define KEY 1
#define SPEEDUP 2
#define ADDBOMB 3


int x = 0, y = 0;
int w = 850, h = 850;
int r = 20;
int i = 0, j = 0;
int speed = 5;

//砖块和道具
bool Box[17][17];
int Drop[17][17];

//炸弹
Bomb b;

//敌人数组，最多三个
Enemy e[3];

//敌人计数器
int enemyCounts = 3;

//胜利标志
bool winFlag = false;

//小球控制
void KeyControl()
{
	char userkey = _getch();

	if (GetAsyncKeyState(VK_UP) && ((x - 25) % 100 == 0) && Box[x / BLOCKWIDTH][(y - speed - r) / BLOCKWIDTH] == false)   // Up
	{
		y -= speed;
		if (y <= r) y = r + 5;
	}
	if (GetAsyncKeyState(VK_DOWN) && ((x - 25) % 100 == 0) && Box[x / BLOCKWIDTH][(y + speed + r) / BLOCKWIDTH] == false) // Down
	{
		y += speed;
		if (y >= w - r) y = w - r - 5;
	}
	if (GetAsyncKeyState(VK_LEFT) && ((y - 25) % 100 == 0) && Box[(x - speed - r) / BLOCKWIDTH][y / BLOCKWIDTH] == false) // Left
	{
		x -= speed;
		if (x <= r) x = r + 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) && ((y - 25) % 100 == 0) && Box[(x + speed + r) / BLOCKWIDTH][y / BLOCKWIDTH] == false) // Right
	{
		x += speed;
		if (x >= w - r) x = w - r - 5;
	}

	//生成炸弹
	if (userkey == ' ')
	{
		b.CreateBomb(x, y);
		cout << b.GetBombCounts() << endl;
	}
}

void DrawMap()
{
	for (i = 0; i < 17; i++)
	{
		for (j = 0; j < 17; j++)
		{
			//奇数排、列是墙
			if (i % 2 != 0 && j % 2 != 0)
			{
				int left = (i) * 50;
				int top = (j) * 50;
				int right = left + 50;
				int bottom = top + 50;
				setfillcolor(RGB(190, 190, 190));
				setlinecolor(RGB(150, 150, 150));
				fillrectangle(left, top, right, bottom);
			}

			//偶数排、列是砖块且当Box[i][j]的时候才生成
			else if (Box[i][j])
			{
				int left_b = (i) * 50 + 5;
				int top_b = (j) * 50 + 5;
				int right_b = left_b + 40;
				int bottom_b = top_b + 40;
				setlinecolor(RGB(50, 50, 50));
				setfillcolor(RGB(50, 50, 50));
				fillrectangle(left_b, top_b, right_b, bottom_b);
			}
		}
	}
}

//随机制造砖块和墙，按列生成
void CreateBox()
{
	int tmp = 0;	//一把钥匙，一个加速，一个增加炸弹
	for (i = 0; i < 17; i++)
	{
		for (j = 0; j < 17; j++)
		{
			//生成砖块后才能生成道具
			if ((i + j) % 2 != 0 && rand() % 3 == 0)
			{
				Box[i][j] = true;
				if (tmp == 0)
				{
					Drop[i][j] = KEY;
					tmp++;
				}
				else if (tmp == 1)
				{
					Drop[i][j] = SPEEDUP;
					tmp++;
				}
				else if (tmp == 2)
				{
					Drop[i][j] = ADDBOMB;
					tmp++;
				}
			}
			else
			{
				Box[i][j] = false;
				Drop[i][j] = 0;
			}
		}
	}
}

//胜利显示
void Win()
{
	TCHAR s[20];
	_stprintf_s(s, _T("Win"));
	settextstyle(100, 0, _T("Arial"));
	outtextxy(300, 400, s);
}

int main()
{
	initgraph(w, h);	// Create screen
	setbkcolor(RGB(0, 120, 0));
	cleardevice();

	srand((unsigned int)time(NULL));

	x = rand() % 9 * 100 + r + 5; //  random position
	y = rand() % 9 * 100 + r + 5;

	//随机生成敌人
	for (int i = 0; i < 3; i++)
	{
		e[i].CreateEnemy(rand() % 9 * 100 + r + 5, rand() % 9 * 100 + r + 5, true);
	}

	//生成砖块和道具
	CreateBox();

	BeginBatchDraw();
	while (true)
	{

		DrawMap();  //  create map

		setfillcolor(RED);

		if (_kbhit())
			KeyControl();

		fillcircle(x, y, r);

		for (int i = 0; i < 3; i++)
		{
			if (e[i].GetEnemyLife())
			{
				setfillcolor(YELLOW);
				fillcircle(e[i].GetEnemy_x(), e[i].GetEnemy_y(), r);
				e[i].EnemyMove(w, speed, r, Box, x, y);
			}
		}

		//掉落道具
		for (int i = 0; i < 17; i++)
			for (int j = 0; j < 17; j++)
			{
				if (Box[i][j] == false && Drop[i][j] != 0)
				{

					if (Drop[i][j] != 0)
					{
						int drop_x = i * BLOCKWIDTH + 25;
						int drop_y = j * BLOCKWIDTH + 25;

						switch (Drop[i][j])
						{
						case KEY:
						{
							setfillcolor(WHITE);
							fillcircle(drop_x, drop_y, 20);
							break;
						}
						case SPEEDUP:
						{
							setfillcolor(BLUE);
							fillcircle(drop_x, drop_y, 20);
							break;
						}
						case ADDBOMB:
						{
							setfillcolor(CYAN);
							fillcircle(drop_x, drop_y, 20);
						}
						default:
							break;
						}
					}

					//拾取道具
					if ((x - r) / BLOCKWIDTH == i && (y - r) / BLOCKWIDTH == j)
					{
						int drop_x = i * BLOCKWIDTH + 25;
						int drop_y = j * BLOCKWIDTH + 25;

						switch (Drop[i][j])
						{
						case KEY:
						{
							setfillcolor(RGB(0, 120, 0));
							setlinecolor(RGB(0, 120, 0));
							fillcircle(drop_x, drop_y, 20);
							winFlag = true;
							Drop[i][j] = 0;
							break;
						}
						case SPEEDUP:
						{
							setfillcolor(RGB(0, 120, 0));
							setlinecolor(RGB(0, 120, 0));
							fillcircle(drop_x, drop_y, 20);
							speed += 5;
							Drop[i][j] = 0;
							break;
						}
						case ADDBOMB:
						{
							setfillcolor(RGB(0, 120, 0));
							setlinecolor(RGB(0, 120, 0));
							fillcircle(drop_x, drop_y, 20);
							b.SetBombMax(3);
							Drop[i][j] = 0;
							break;
						}
						default:
							break;
						}
					}
				}
			}

		//存在炸弹
		if (b.GetBombCounts() != 0)
		{
			setfillcolor(BLACK);
			for (int i = 1; i <= 3; i++)
			{
				BOMBITEM tmp = b.GetBomb(i);

				//炸弹存在
				if (tmp.existsTime >= 1)
				{
					//炸弹计时
					b.SetBombLife(i);
					fillcircle(tmp.bomb_x, tmp.bomb_y, 20);
				}

				if (tmp.existsTime >= 20)
				{
					//炸弹爆炸，画十字
					int columnLeft = tmp.bomb_x - 25;
					int columnTop = tmp.bomb_y - 25 - BLOCKWIDTH;
					int columnRight = tmp.bomb_x + 25;
					int columnBottom = tmp.bomb_y + 25 + BLOCKWIDTH;

					//没有墙
					if (ODD(columnLeft) == 0)
					{

						//炸弹和砖块交互
						fillrectangle(columnLeft, columnTop, columnRight, columnBottom);
						for (int i = columnTop / BLOCKWIDTH; i <= columnBottom / BLOCKWIDTH; i++)
						{
							//消除砖块
							if (Box[columnLeft / BLOCKWIDTH][i])
								Box[columnLeft / BLOCKWIDTH][i] = false;
						}

						//炸弹和敌人交互
						for (int i = 0; i < 3; i++)
						{
							if (e[i].GetEnemyLife())
							{
								//敌人和炸弹在同一列
								if (e[i].GetEnemy_x() / BLOCKWIDTH == columnLeft / BLOCKWIDTH)
								{
									if (e[i].GetEnemy_y() / BLOCKWIDTH >= columnTop / BLOCKWIDTH && e[i].GetEnemy_y() / BLOCKWIDTH <= columnBottom / BLOCKWIDTH)
									{
										e[i].DeleteEnemy();
										enemyCounts--;
									}
								}
							}
						}
					}

					//有墙
					else
					{
						columnTop = tmp.bomb_y - 25;
						columnBottom = tmp.bomb_y + 25;
						fillrectangle(columnLeft, columnTop, columnRight, columnBottom);
					}

					int rowLeft = tmp.bomb_x - 25 - 50;
					int rowTop = tmp.bomb_y - 25;
					int rowRight = tmp.bomb_x + 25 + 50;
					int rowBottom = tmp.bomb_y + 25;

					if (ODD(rowTop) == 0)
					{
						fillrectangle(rowLeft, rowTop, rowRight, rowBottom);
						for (int i = rowLeft / 50; i <= rowRight / 50; i++)
						{
							if (Box[i][rowTop / 50])
								Box[i][rowTop / 50] = false;
						}

						//敌人和炸弹在同一行
						if (e[i].GetEnemy_y() / BLOCKWIDTH == rowTop / BLOCKWIDTH)
						{
							if (e[i].GetEnemy_x() / BLOCKWIDTH >= rowLeft / BLOCKWIDTH && e[i].GetEnemy_x() / BLOCKWIDTH <= rowRight / BLOCKWIDTH)
							{
								e[i].DeleteEnemy();
								enemyCounts--;
							}
						}
					}

					else
					{
						rowLeft = tmp.bomb_x - 25;
						rowRight = tmp.bomb_x + 25;
						fillrectangle(rowLeft, rowTop, rowRight, rowBottom);
					}
					b.DeleteBomb(i);
				}
			}
		}

		//消灭敌人，捡到钥匙，游戏胜利
		if (enemyCounts == 0 || winFlag)
		{
			Win();
		}

		//碰到敌人，游戏结束
		for (int i = 0; i < 3; i++)
		{
			int eX = e[i].GetEnemy_x() / BLOCKWIDTH;
			int eY = e[i].GetEnemy_y() / BLOCKWIDTH;
			int pX = x / BLOCKWIDTH;
			int pY = y / BLOCKWIDTH;
			if (eX == pX && eY == pY)
			{
				TCHAR s[20];
				_stprintf_s(s, _T("Lose"));
				settextstyle(100, 0, _T("Arial"));
				outtextxy(300, 400, s);
			}
		}

		FlushBatchDraw();
		Sleep(50);
		cleardevice();
	}

	_getch();
	closegraph();
	return 0;
}

