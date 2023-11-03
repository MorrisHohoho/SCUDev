//练习1：人物跑动


#include <stdio.h>
#include <graphics.h>
#include "conio.h"
#include "EasyXPng.h"


#define WIDTH  640
#define HEIGHT 480
#define LEFT 0
#define RIGHT 1

int cnt;
int x = 0;//The Location of girl
int speed = 6;
bool dir = RIGHT;

int main()
{
	IMAGE im_bk, im_dra;
	initgraph(WIDTH, HEIGHT,EX_SHOWCONSOLE);

	int i = 0;
	TCHAR filename[64];	//这里我的路径要长一点，所以我开成了64
	IMAGE imgLeft[8];
	IMAGE imgRight[8];


	//Loag Imgae of Left
	for (i = 0; i < 8; i++)
	{
		_stprintf_s(filename, _T("./Pictures/Images/girl/gl%d.png"),i);
		loadimage(&imgLeft[i], filename);
	}

	//Load Image of Right
	for (i = 0; i < 8; i++)
	{
		_stprintf_s(filename, _T("./Pictures/Images/girl/gr%d.png"), i);
		loadimage(&imgRight[i], filename);
	}
	

	loadimage(&im_bk, _T("./Pictures/bg.png"));

	int image_width = imgRight[0].getwidth();
	i = 0;
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, &im_bk);
		if (dir == RIGHT)
		{
			putimagePng(x, HEIGHT / 2, &imgRight[i]);
		}
		else if (dir == LEFT)
		{
			putimagePng(x, HEIGHT / 2, &imgLeft[i]);
		}
		Sleep(60);

		x = x + speed;
		if (i == 7) i = 0;
		i++;
		if (x+image_width > WIDTH)
		{
			dir = !dir;
			speed= -speed;
			i = 0;
		}
		if (x < 0)
		{
			dir = !dir;
			speed= -speed;
			i = 0;
		}

		FlushBatchDraw();
	}

	_getch();
	return 0;
}

