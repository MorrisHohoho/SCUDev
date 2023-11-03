//练习2：键盘控制人物左右移动


#include <stdio.h>
#include <graphics.h>
#include "conio.h"
#include "EasyXPng.h"


#define WIDTH  640
#define HEIGHT 480
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
int cnt;
int x=WIDTH/2,y=HEIGHT/2;//The Location of girl
int speed = 6;
int dir = DOWN;
bool dir_change = false;
char counter;



int main()
{
	IMAGE im_bk, im_dra;
	initgraph(WIDTH, HEIGHT,EX_SHOWCONSOLE);

	int i = 0;
	TCHAR filename[64];	//这里我的路径要长一点，所以我开成了64
	IMAGE imgLeft[8];
	IMAGE imgRight[8];
	IMAGE imgUp[8];
	IMAGE imgDown[8];


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
	//Load Image of Up
	for (i = 0; i < 8; i++)
	{
		_stprintf_s(filename, _T("./Pictures/Images/girl/gu%d.png"), i);
		loadimage(&imgUp[i], filename);
	}

	//Load Image of Dight
	for (i = 0; i < 8; i++)
	{
		_stprintf_s(filename, _T("./Pictures/Images/girl/gd%d.png"), i);
		loadimage(&imgDown[i], filename);
	}

	

	loadimage(&im_bk, _T("./Pictures/bg.png"));

	int imageWidth = imgRight[0].getwidth();
	int imageHeight = imgDown[0].getheight();
	i = 0;
	bool tmp = false;
	BeginBatchDraw();
	while (1)
	{
		putimage(0, 0, &im_bk);
		switch (dir) {
		case DOWN:
		{
			putimagePng(x, y, &imgDown[i]);
			break;
		}
		case UP:
		{
			putimagePng(x, y, &imgUp[i]);
	
			break;
		}
		case RIGHT:
		{
			putimagePng(x, y, &imgRight[i]);
		
			break;
		}
		case LEFT:
		{
			putimagePng(x, y, &imgLeft[i]);

			break;
		}
		default:
			break;
		}

		if (_kbhit())
		{
			char key;
			key = _getch();
			if (tmp != false)
			{
				if (counter == key) dir_change = false;
				else dir_change = true;
			}
			counter = key;
			tmp=true;
		

			if (GetAsyncKeyState(VK_UP))
			{
				y -= speed;
				if (y < 0) y = 0;
				dir = UP;
				i++;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				y += speed;
				if (y + imageHeight > HEIGHT) y = HEIGHT - imageHeight;
				dir = DOWN;
				i++;
			}
			if (GetAsyncKeyState(VK_LEFT))
			{
				x -= speed;
				if (x < 0) x = 0;
				dir = LEFT;
				i++;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				x += speed;
				if (x + imageWidth > WIDTH) x = WIDTH - imageWidth;
				dir = RIGHT;
				i++;
			}
		}
		if (i > 7||!dir_change)i = 0;
		FlushBatchDraw();
	}

	_getch();
	return 0;
}

