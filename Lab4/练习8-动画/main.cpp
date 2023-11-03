#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"  // 用于显示带透明通道的png图片

#pragma comment(lib,"Winmm.lib")

#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4996)

#define  WIDTH  560 // 画面宽度
#define  HEIGHT 800 // 画面高度

IMAGE im_bk;

int main()
{
	initgraph(WIDTH, HEIGHT);
	loadimage(&im_bk, _T("./Pictures/background.png"));

	int i = 0;
	TCHAR filename[20];
	IMAGE img[10];
	for (i = 0; i <8; i++)
	{
		_stprintf(filename, _T("./Pictures/man%d.png"), i);
		loadimage(&img[i], filename);
	}

	mciSendString(_T("open SoloInD.mp3 alias bkmusic"), NULL, 0, NULL);
	//打开背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	// 循环播放

	i = 0;

	while (1)
	{
		putimage(0, 0, &im_bk);	// 显示背景	
		putimagePng(0, 0, &img[i]);
		Sleep(200);
		i += 1;
		if (i ==7 ) i = 0;
		cleardevice();
	}
	_getch();
	return 0;
}