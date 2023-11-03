#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include<random>

using namespace std;

int main()
{
	int x, y; //炮弹圆心坐标
	int vx = 0, vy = 0; //炮弹发射速度
	int g = 1;	//重力加速度
	int r = 15;	//炮弹半径
	float rect_left_x, rect_top_y, rect_right_x, rect_bottom_y,rect_height;//目标坐标参数
	float vp;	//目标移动速度
	bool f=false,rect_d= false,rect_u=false;
	int score = 0;//分数
	bool is_score = false;//是否发生碰撞
	default_random_engine e;
	uniform_real_distribution<float> u(3.0,10.0); //目标速度随机
	uniform_real_distribution<float> u1(30.0, 100.0); //目标高度随机


	initgraph(600, 800);
	setbkcolor(RGB(50, 50, 50));
	cleardevice();

	rect_right_x = 600;//目标固定在屏幕左侧;
	rect_left_x = 580;//目标宽度固定为20;
	rect_top_y = 0;//目标固定从屏幕上方出现;
	rect_height = 30;//目标初始高度为30;
	rect_bottom_y = rect_top_y + rect_height; //目标右下角坐标初始化
	rect_d=true,rect_u=false ;//控制矩形与边界碰撞，每一边只能碰一次
	x = 0;
	y = 600;
	vp = 5;
	while (1)
	{
		
		fillrectangle(rect_left_x, rect_top_y, rect_right_x, rect_bottom_y); //画矩形
		rect_top_y = rect_top_y + vp; //矩形移动
		rect_bottom_y = rect_top_y + rect_height; //计算矩形右下角坐标
		if (rect_bottom_y >= 800 || rect_top_y <= 0) //矩形碰到边界
		{
			if (rect_d&& rect_bottom_y >= 800) //碰到下边界，变形变速向上。
			{
				rect_height = u1(e);
				vp = u(e);
				vp = -vp;
				rect_d = false;
				rect_u = true;
			}
			else if(rect_u&& rect_top_y <= 0)  //碰到上边界，变形变速向下。
			{
				rect_height = u1(e);
				vp = u(e);
				rect_u = false;
				rect_d = true;
			}
		}

		if (_kbhit())
		{
			char input = _getch();
			if (input == ' '&&f==false) //发射炮弹,炮弹发射后就不能操作
			{
				f = true;
				vx = 15;
				vy = -30;
			}
		}
		if (f)
		{
			vy = vy + g;
			x = x + vx;
			y = y + vy;
		}
		else
		{
			x = 0;
			y = 600;
		}
		if (x <0||x>=600||y>=800)
		{
			
				x = 0;
				y = 600;
				f = false;
				if (!is_score)	//没碰到目标，分数清零
					score = 0;
				is_score = false;
				
			
		}
		//炮弹全部落在在目标内
		if (x + r > rect_left_x && y - r >= rect_top_y && y + r <= rect_bottom_y)
		{
			vx = -0.9*vx;
			is_score = true;
			score++;
		}
		//炮弹下半部分击中目标
		if (x + r > rect_left_x && y + r > rect_top_y && y - r < rect_top_y)
		{
			vx = -0.9 * vx;
			is_score = true;
			score++;
		}
		//炮弹上半部分击中目标
		if (x + r > rect_left_x && y + r > rect_bottom_y && y - r < rect_bottom_y)
		{
			vx = -0.9 * vx;
			is_score = true;
			score++;
		}
		fillcircle(x, y, r);
		TCHAR s[20];   
		_stprintf_s(s, _T("%d"), score);
		settextstyle(30, 0, _T("Arial"));
		outtextxy(50, 30, s);
		Sleep(40);
		cleardevice();
	}

	closegraph();
	return 0;
}
