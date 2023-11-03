/*
* 练习4：贴图版飞机大战
* 实现功能：1、玩家飞机控制：方向键控制左右，空格发射导弹，一次只能发射一个
* 2、敌机生成：每两秒生成一座敌机，敌机位置随机，不会发射子弹（没写）
* 3、导弹和敌机碰撞：导弹可以消灭敌机。
* 4、敌机和玩家的碰撞：敌机撞到玩家也会消失。
*/

#include<stdio.h>
#include<graphics.h>
#include"conio.h"
#include"EasyXPng.h"
#include<list>
#include<time.h>
#include<iostream>

using namespace std;

#define WIDTH 640
#define HEIGHT 960

bool collision();

//定时器
DWORD t1, t2;

//图像
IMAGE im_bk, im_player, im_enemy,im_bulletup,im_bulletdown;


//玩家
int pW = 0, pH = 0;
int pX=0,pY=0;
int speed = 10;

//玩家子弹
int bX = 0,bY = 0;
int bW = 0, bH = 0;
bool bulletOut = false;
int bulletspeed = 20;

//敌人类
int eH = 0, eW = 0;
class E {
public:
	int x, y;
	E(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
};
list<E> enemy;

void init()
{
	IMAGE img;
	TCHAR filename[64];
	
	loadimage(&im_bk, _T("./Pictures/Images/bg.png"));
	loadimage(&im_player, _T("./Pictures/Images/Aircraft/player.png"));
	loadimage(&im_bulletup, _T("./Pictures/Images/Aircraft/bulletup.png"));
	loadimage(&im_enemy, _T("./Pictures/Images/Aircraft/enemy.png"));

	pW = im_player.getwidth();
	pH = im_player.getheight();
	pX = WIDTH / 2;
	pY = HEIGHT - pH;

	bW = im_bulletup.getwidth();
	bH = im_bulletup.getheight();

	eW = im_enemy.getwidth();
	eH = im_enemy.getheight();

	initgraph(WIDTH, HEIGHT,EX_SHOWCONSOLE);
}

void show()
{

	putimage(0, 0, &im_bk);
	putimage(0, 480, &im_bk);
	putimagePng(pX, pY, &im_player);

	//玩家发射子弹
	if (bulletOut == true)
	{
		putimagePng(bX, bY, &im_bulletup);
	}

	if (enemy.empty() == false)
	{
		auto pE = enemy.begin();
		while (pE != enemy.end())
		{
			cout << (*pE).x << endl;
			int tmpX = (*pE).x;
			int tmpY = (*pE).y;
			putimagePng(tmpX, tmpY, &im_enemy);
			pE++;
		}
	}

}

void updateWithC()
{
	if (_kbhit())
	{
		char key;
		key = _getch();

		if (GetAsyncKeyState(VK_UP))
		{
			pY-=speed;
			if (pY < 0) pY = 0;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			pY += speed;
			if (pY + pH > HEIGHT) pY = HEIGHT - pH;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			pX -= speed;
			if (pX < 0) pX = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			pX += speed;
			if (pX + pW > WIDTH) pX = WIDTH - pW;
		}
		if (GetAsyncKeyState(VK_SPACE)&&!bulletOut)
		{
			bX = pX+pW/2;
			bY = pY - bH - 10;
			bulletOut = true;
		}
	}
}

void updateWithoutC()
{
	t2 = GetTickCount();
	bool col = collision();
	if (bulletOut)
	{
		bY -= speed;
		if (bY < 0 || col)
			bulletOut = false;
	}

	//每隔两秒出现一架敌机
	if (t2 - t1 >= 2000) {
		cout << "过了2s" << endl;
		t1 = t2;
		enemy.push_back(E(rand() % (WIDTH - 50), 0));
	}

	//敌机坐标更新
	if (enemy.empty() == false)
	{
		auto pE = enemy.begin();
		while (pE != enemy.end())
		{
			if ((*pE).y + eH > HEIGHT)
			{
				enemy.erase(pE);
				break;
			}
			else
			{
				(*pE).y += speed;
				pE++;
			}
		}
	}
}

bool collision()
{
	if (enemy.empty() == false )
	{
		auto pE = enemy.begin();
		while (pE != enemy.end())
		{
			if (bX + bW > (*pE).x && bX < (*pE).x + eW && bY<(*pE).y + eH && bY + eH>(*pE).y)
			{
				bulletOut = false;
				enemy.erase(pE);
				return true;
			}
			if(pX + pW > (*pE).x && pX < (*pE).x + eW && pY<(*pE).y + eH && pY + pH>(*pE).y)
			{
				enemy.erase(pE);
				return false;
			}
			else
				pE++;
		}
	}
	return false;
}

int main()
{
	init();

	BeginBatchDraw();
	t1 = GetTickCount();
	while (1)
	{
		show();

		Sleep(30);
		FlushBatchDraw();


		updateWithC();

		updateWithoutC();
	}

}