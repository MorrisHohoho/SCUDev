/*下100层小游戏
* 
* 实现功能：1、死亡后按空格重来
* 2、键盘控制（左、右、跳）
* 3、小球和板子的碰撞检测
* 4、血量系统，左上角为小球血量，归0时视为死亡，游戏结束
* 5、板子随机出现道具，功能为小球增加一条血量
* 5、随机出现尖刺板子，碰到后扣除一条血量，且尖刺板子无法落脚，小球会向上弹起
* 
*/

#include <graphics.h>  
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int r = 10;	//小球半径

//板子结构体
struct Board
{
	int x, y;
	int speed;
	bool sharp;
	bool item;
};

//小球类
class Player {
public:
	int getPlayerX();	//获取小球当前横坐标
	int getPlayerY();	//获取小球当前纵坐标
	int getPlayerBlood();	//获取小球当前血量
	void setPlayer(int x, int y);	//设置小球坐标
	void setPlayerBlood(int b);	//设置小球血量
	void move();	//小球移动
	bool collision(Board board, int bw);	//小球碰撞
	bool get_item(Board board, int bw);		//小球获取道具
	Player();	//构造函数，初始化小球参数
private:
	int player_x, player_y;	//小球当前坐标
	int blood;	//初始血量为5
	bool jump;	//判断小球是否起跳
	int last_player_x, last_player_y;	//小球上一帧坐标
	float vy, vx, g;	//小球移动速度
};

Player::Player()
{
	blood = 5;
	player_x = 0;
	player_y = 0;
	jump = false;
	vy = 0;
	vx = 10;
	g = 0;
}

int Player::getPlayerX()
{
	return player_x;
}

int Player::getPlayerY()
{
	return player_y;
}

int Player::getPlayerBlood()
{
	return blood;
}
void Player::setPlayer(int x, int y)
{
	last_player_x = player_x;
	last_player_y = player_y;
	player_x = x;
	player_y = y;
}

void Player::setPlayerBlood(int b)
{
	blood = b;
}

void Player::move()
{
	if (_kbhit())
	{
		char input = _getch();

		if (input == ' ' && !jump)
		{
			vy = -30;
			g = 5;
			jump = true;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			last_player_x = player_x;
			player_x -= vx;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			last_player_x = player_x;
			player_x += vx;
		}
	}
	last_player_y = player_y;
	player_y += vy;
	vy += g;
}

bool Player::get_item(Board board, int bw)
{
	if (board.item && collision(board, bw))
	{
		if (player_x + r > (2 * board.x + bw) / 2 && player_x - r < (2 * board.x + bw) + 30)
		{
			blood++;
			return true;
		}
		else return false;
	}
	else return false;
}


bool Player::collision(Board board, int bw)
{
	if (player_x + r >= board.x && player_x - r <= board.x + bw)
	{
		if (board.y - player_y <= r && board.y - player_y >= -r)
		{
			vy = 0;
			g = 0;
			jump = false;
			if (board.sharp)
			{
				blood--;
				vy = -40;
				g = 5;
			}
			return true;
		}
		else if (last_player_y<board.y && player_y>board.y)
		{
			vy = 0;
			g = 0;
			jump = false;
			if (board.sharp)
				blood--;
			return true;
		}
		else
			return false;
	}
	else
	{
		g = 5;
		return false;
	}
}


int main()
{
	int w = 600, h = 600;	//画布大小
	int bw = 100, bh = 10;	//板子长宽
	int speed;	//板子速度
	int x, y = 590;
	int i = 0;	//遍历板子用参数
	bool cflag = false;	//判断小球是否碰撞
	srand((unsigned int)time(NULL));

	Board board[6];

	initgraph(w, h);

	//初始化板子参数
	speed = 5;
	for (i = 0; i < 6; i++)
	{
		board[i].x = rand() % 500;
		board[i].y = 590;
		board[i].sharp = false;
		board[i].item = false;
	}

	Player user;
	user.setPlayer((2 * board[0].x + bw) / 2, board[0].y - r);

	BeginBatchDraw();
	while (1)
	{
		//顶部尖刺
		for (i = 0; i < 20; i++)
		{
			line(30 * i, 0, 30 * i + 15, 30);
			line(30 * i + 15, 30, 30 * (i + 1), 0);
		}
		//绘制小球
		fillcircle(user.getPlayerX(), user.getPlayerY(), r);

		//没血就不能控制了
		if(user.getPlayerBlood()>0)
		{	user.move();
			//遍历板子
			for (i = 0; i < 6; i++)
			{
				if (i == 0 || board[i].y - board[i - 1].y > 100 || board[i].y <= 100)
				{
					//先判断是否碰撞
					cflag = user.collision(board[i], bw);

					//六分之一的概率生成带刺板子或道具板子

					//带刺板子
					if (board[i].sharp)
					{
						for (int count = 0; count < 5; count++)
						{
							line(board[i].x + count * 20, board[i].y, board[i].x + 20 * (2 * count - 1), board[i].y - 10);
							line(board[i].x + 20 * (2 * count - 1), board[i].y - 10, board[i].x + 20 + count * 20, board[i].y);
						}
						fillrectangle(board[i].x, board[i].y, board[i].x + bw, board[i].y + bh);
					}

					//道具板子
					else if (board[i].item)
					{
						if (user.get_item(board[i], bw))
							board[i].item = false;

						setfillcolor(RGB(200, 200, 200));
						setlinecolor(RGB(200, 200, 200));
						fillrectangle((2 * board[i].x + bw) / 2, board[i].y, (2 * board[i].x + bw) / 2 + 30, board[i].y - 30);
						fillrectangle(board[i].x, board[i].y, board[i].x + bw, board[i].y + bh);
					}

					//普通板子
					else
						fillrectangle(board[i].x, board[i].y, board[i].x + bw, board[i].y + bh);

					//板子上移
					board[i].y = board[i].y - speed;

					//如果发生碰撞
					if (cflag)
					{
						//让小球停在板子上
						user.setPlayer(user.getPlayerX(), board[i].y - r);
						cflag = false;
					}
				}

				//随机生成板子相关参数
				if (board[i].y < 0)
				{
					board[i].y = h - bh;
					board[i].speed = rand() % 3 + 3;
					board[i].x = rand() % 500;
					if ((rand() % 6 + 1) == 1)
						board[i].sharp = true;
					else
						board[i].sharp = false;
					if ((rand() % 6 + 1) == 2 && board[i].sharp == false)
						board[i].item = true;
					else
						board[i].item = false;
				}
			}
		}

		//重新开始
		else
		{
			if (_kbhit())
			{
				char input = _getch();
				if (input == ' ')
				{
					user.setPlayerBlood(3);
					for (i = 0; i < 6; i++)
					{
						board[i].x = rand() % 500;
						board[i].y = 590;
						board[i].sharp = false;
						board[i].item = false;
					}

					user.setPlayer((2 * board[0].x + bw) / 2, board[0].y - r);
				}
			}
		}

		//左上角显示血量
		TCHAR s[20];
		_stprintf_s(s, _T("%d"), user.getPlayerBlood());
		settextstyle(30, 0, _T("Arial"));
		outtextxy(50, 30, s);

		FlushBatchDraw();
		Sleep(100);
		cleardevice();

		//失败提示
		if (user.getPlayerY() > 600 || user.getPlayerY() < 30||user.getPlayerBlood()<0)
		{
			user.setPlayerBlood(0);
			settextcolor(RGB(0, 0, 255));
			settextstyle(60, 0, _T("Arial"));
			outtextxy(270, 400, _T("Lose"));
		}
	}
	_getch();
	closegraph();
	return 0;
}