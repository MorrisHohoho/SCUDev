//练习3：刷新房子

#include <stdio.h>
#include <graphics.h>
#include "conio.h"
#include "EasyXPng.h"
#include<iostream>

using namespace std;

#define WIDTH  640
#define HEIGHT 480

int speed_1 = 2, speed_2 = 3;
int dx_1 = 0, dx_2 = 0, dx_3 = 0;

int x = WIDTH / 4;
int cnt;
// 绘图函数，补充透明度 AA
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();			// GetImageBuffer() 函数，用于获取绘图设备的显存指针， EasyX 自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(image);		// 获取 picture 的显存指针
	int imageWidth = image->getwidth();		// 获取图片宽度
	int imageHeight = image->getheight();	// 获取图片宽度
	int dstX = 0;							// 在 绘图区域 显存里像素的角标
	int srcX = 0;							// 在 image 显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			// 防止越界
			if (ix + pic_x >= 0 && ix + pic_x < imageWidth && iy + pic_y >= 0 && iy + pic_y < imageHeight &&
				ix + x >= 0 && ix + x < WIDTH && iy + y >= 0 && iy + y < HEIGHT)
			{
				// 获取像素角标
				int srcX = (ix + pic_x) + (iy + pic_y) * imageWidth;
				dstX = (ix + x) + (iy + y) * WIDTH;

				int sa = ((src[srcX] & 0xff000000) >> 24) * AA;			// 0xAArrggbb; AA 是透明度
				int sr = ((src[srcX] & 0xff0000) >> 16);				// 获取 RGB 里的 R
				int sg = ((src[srcX] & 0xff00) >> 8);					// G
				int sb = src[srcX] & 0xff;								// B

				// 设置对应的绘图区域像素信息
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

int main()
{
	IMAGE im_bk, im_house, im_hill;
	initgraph(WIDTH, HEIGHT,EX_SHOWCONSOLE);

	int i;
	TCHAR filename[64];
	IMAGE img[8];

	for (i = 0; i < 8; i++)
	{
		_stprintf_s(filename, _T("./Pictures/Images/Dragon/d%d.png"), i);
		loadimage(&img[i], filename);
	}

	loadimage(&im_bk, _T("./Pictures/Images/bg0.png"));
	loadimage(&im_house, _T("./Pictures/Images/house.png"));

	i = 0;
	BeginBatchDraw();
	
	while (1)
	{
		//天空
		putimage(0, 0, dx_1, 300, &im_bk, WIDTH - dx_1, 0, SRCCOPY);
		putimage(dx_1, 0, WIDTH - dx_1, 300, &im_bk, 0, 0, SRCCOPY);

		//草地
		putimage(0, 300, dx_2, 480, &im_bk, WIDTH - dx_2, 300, SRCCOPY);
		putimage(dx_2, 300, WIDTH - dx_2, 480, &im_bk, 0, 300, SRCCOPY);
		//房子
		drawAlpha(&im_house, 0, 300, dx_3, 200, im_house.getwidth()-dx_3, 0, 1);
		drawAlpha(&im_house, dx_3, 300, WIDTH - dx_3, 200, 0, 0, 1);

		putimagePng(WIDTH * 2 / 3, 260, &img[i]);
		i++;
		if (i > 7)
			i = 0;

		Sleep(30);
		FlushBatchDraw();

		dx_1 = dx_1 + speed_1;
		if (dx_1 >= WIDTH)
			dx_1 = speed_1;

		dx_2 = dx_2 + speed_2;
		if (dx_2 >= WIDTH)
			dx_2 = speed_2;

		dx_3 = dx_3 + speed_2;
		if (dx_3 >= im_house.getwidth())
			dx_3 = speed_2;

	}

	_getch();
	return 0;
}

