/*
* 实现功能：
* 1、敌机发射子弹，且子弹和敌机在超出屏幕时自动删除
* 2、血量系统：初始血量为5，在碰到敌机或者敌机子弹时扣除1点
* 3、敌机和敌机子弹的碰撞
* 4、玩家不能移动到屏幕外
* 5、BOSS：消灭10个敌机出现BOSS，BOSS血量为50、在下方显示血条、消灭BOSS后游戏胜利
* 6、BOSS左右移动，每两秒发射十颗速度随机的子弹。
* 7、敌机左右移动
*/
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <list>
#include <iostream>
#include<typeinfo>
#include"Boss.h"

using namespace std;


Node myPlane(260, 740,false);
int tmp_x, tmp_y;
//消灭敌机计数
int enemyEraseCounts = 0;
//玩家有五条命
int playerLife = 5;
list<Node> enemyPlaneList;
list<Node> bulletList;
list<Node> enemyBulletList;
list<Node> bossBulletList;
Boss one;


//模板函数：敌方单位与我方的碰撞
template<class T1, class T2, class T3>
void Collision(T1& p1, T2& a, T3& width, T3& height)
{
	p1 = a.begin();
	while (p1 != a.end())
	{
		if ((*p1).x + width >= myPlane.x && (*p1).x <= myPlane.x + MY_PLANE_WIDTH && (*p1).y + height >= myPlane.y && (*p1).y && (*p1).y <= myPlane.y + MY_PLANE_HEIGHT)
		{
			a.erase(p1);
			playerLife--;
			break;
		}
		else
			p1++;
	}
}

//模板函数：删除超出屏幕的实体
template<class T1, class T2, class T3>
void DeleteOutScreen(T1& p1, T2& li, T3& dir, T3& max)
{
	p1 = li.begin();
	while (p1 != li.end())
	{
		//向下超出
		if (dir == 0)
		{
			if ((*p1).y > max)
			{
				li.erase(p1);
				break;
			}
			else
				p1++;
		}

		//向上超出
		else if (dir == 1)
		{
			if ((*p1).y < max)
			{
				li.erase(p1);
				break;
			}
			else
				p1++;
		}
	}
}

//	Detection of keyboard pressing
void IsPressKey()
{
	if (_kbhit())			//	If a key is pressed
	{
		char key;
		key = _getch();		//	Obtain key info

		if (GetAsyncKeyState(VK_UP))     //Up
		{
			myPlane.y -= 8;
			if (myPlane.y < 0)
				myPlane.y = 0;
		}
		if (GetAsyncKeyState(VK_DOWN))   //Down
		{
			myPlane.y += 8;
			if (myPlane.y + MY_PLANE_HEIGHT > WIN_HEIGHT)
				myPlane.y = WIN_HEIGHT - MY_PLANE_HEIGHT;
		}
		if (GetAsyncKeyState(VK_LEFT))   //Left
		{
			myPlane.x -= 6;
			if (myPlane.x < 0)
				myPlane.x = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT))  //Right
		{
			myPlane.x += 6;
			if (myPlane.x + MY_PLANE_WIDTH > WIN_WIDTH)
			{
				myPlane.x = WIN_WIDTH - MY_PLANE_WIDTH;
			}
		}
	}
}


//绘制Boss血条
void DrawBossLife()
{
	int x = one.GetLife();
	setfillcolor(RED);
	setlinecolor(WHITE);
	fillrectangle(150, 750, 150 + x * 6, 780);
}

//	Detection of Collision
void Shoot() {

	list<Node>::iterator pDj = enemyPlaneList.begin();
	list<Node>::iterator pZd = bulletList.begin();

	//	Iterate all planes 
	bool flag = false;
	while (pDj != enemyPlaneList.end()) {
		pZd = bulletList.begin();
		//	Iterate all bullets
		while (pZd != bulletList.end()) {
			//	Detection of Collision
			if ((*pZd).x >= ((*pDj).x - 10) && (*pZd).x <= ((*pDj).x + 50) &&
				(*pZd).y >= ((*pDj).y - 15) && (*pZd).y <= ((*pDj).y + 30)
				) {
				//	If collide, them eliminate both the plane and the bullet
				enemyPlaneList.erase(pDj);
				bulletList.erase(pZd);
				enemyEraseCounts++;
				flag = true;
				break;
			}
			else {
				++pZd;
			}
		}
		if (flag) {
			break;
		}
		++pDj;
	}

	//与BOSS碰撞
	Node tmp_boss = one.GetCoord();
	pZd = bulletList.begin();
	while (pZd != bulletList.end())
	{
		if ((*pZd).x + 5 > tmp_boss.x && (*pZd).x < tmp_boss.x + BOSS_WIDTH && (*pZd).y + 5 < tmp_boss.y + BOSS_HEIGHT)
		{
			one.SetLife();
			bulletList.erase(pZd);
			break;
		}
		else
			pZd++;
	}
}

//敌机、敌机子弹和玩家的碰撞
void EnemyCollision()
{
	bool flag = false;
	list<Node>::iterator pDj = enemyPlaneList.begin();
	list<Node>::iterator pEb = enemyBulletList.begin();
	list<Node>::iterator pBb = bossBulletList.begin();

	//敌机碰撞
	tmp_x = EPLANE_WIDTH;
	tmp_y = EPLANE_HEIGHT;
	Collision(pDj, enemyPlaneList, tmp_x, tmp_y);

	//Boss碰撞
	Node tmp_boss = one.GetCoord();
	if (myPlane.x + MY_PLANE_WIDTH > tmp_boss.x && myPlane.x < tmp_boss.x + BOSS_WIDTH && myPlane.y < tmp_boss.y + BOSS_HEIGHT)
		playerLife--;

	//敌机子弹碰撞
	tmp_x = 5, tmp_y = 5;
	Collision(pEb, enemyBulletList, tmp_x, tmp_y);

	tmp_x = 10, tmp_y = 10;
	Collision(pBb, bossBulletList, tmp_x, tmp_y);
}

//左上角绘制生命值、右上角绘制分数
void DrawText()
{
	TCHAR s[20], s1[20];
	_stprintf_s(s, _T("%d"), playerLife);
	_stprintf_s(s1, _T("%d"), enemyEraseCounts);
	settextstyle(30, 0, _T("Arial"));
	outtextxy(50, 30, s);
	outtextxy(550, 30, s1);
}

void DrawWinOrLose()
{
	TCHAR s[20];
	if (enemyEraseCounts >= BOSS_IN && one.GetLife() <= 0)
	{
		_stprintf_s(s, _T("WIN"));
		settextstyle(100, 0, _T("Arial"));
		outtextxy(300, 400, s);
	}
	if (playerLife <= 0)
	{
		_stprintf_s(s, _T("LOSE"));
		settextstyle(100, 0, _T("Arial"));
		outtextxy(300, 400, s);
	}
}

int main()
{
	// Random seed
	srand((unsigned int)time(NULL));
	//	Create the screen
	initgraph(WIN_WIDTH, WIN_HEIGHT, EX_SHOWCONSOLE);

	DWORD t1, t2;			//	Speed of enemy planes
	DWORD tt1, tt2;			//	Speed of the bullets
	DWORD ebt1, ebt2;

	t1 = GetTickCount();			//	Starting time of the plane
	tt1 = GetTickCount();			//	Starting time of the bullet
	ebt1 = GetTickCount();

	while (1)
	{
		//BOSS出现，停止刷新小怪
		if (enemyEraseCounts < BOSS_IN)
		{
			//	Add an enemy plane every 1000ms
			t2 = GetTickCount();
			if (t2 - t1 >= 1000) {
				enemyPlaneList.push_back(Node(rand() % (WIN_WIDTH - 50), 0,rand()%(1-0+1)));
				t1 = t2;
			}
		}

		//敌机每两秒发射一颗子弹，BOSS每两秒发射10枚子弹
		ebt2 = GetTickCount();
		if (ebt2 - ebt1 >= 2000)
		{
			for (auto& p : enemyPlaneList)
			{
				enemyBulletList.push_back(Node(p.x + 15, p.y + 25,false));
			}

			for (int i = 0; i < 10; i++)
			{
				bossBulletList.push_back(Node(rand()% (one.GetCoord().x+200-one.GetCoord().x)+one.GetCoord().x, 110,false));
			}
			ebt1 = ebt2;
		}

		//	Add a bullet every 500ms
		tt2 = GetTickCount();
		if (tt2 - tt1 >= 500&&playerLife>0) {
			bulletList.push_back(Node(myPlane.x + 35, myPlane.y - 20,false));
			tt1 = tt2;
		}

		BeginBatchDraw();		  //Starting batchdraw
		cleardevice();

		//show our plane at (x=260, y=740)
		rectangle(myPlane.x, myPlane.y, myPlane.x + 32, myPlane.y + 18);

		//show our bullet
		for (auto& p : bulletList) {
			//Print the bullet
			circle(p.x, p.y, 5);
			//	moving upwards
			p.y-=5;
		}

		// Show the enemy plane
		for (auto& p : enemyPlaneList) {
			
			//Print the plane
			roundrect(p.x, p.y, p.x + 30, p.y + 20, 5, 5);
			if (!p.moveDir)
			{
				p.x += 3;
				if (p.x + EPLANE_WIDTH > WIN_WIDTH)
				{
					p.x = WIN_WIDTH - EPLANE_WIDTH;
					p.moveDir = true;
				}
			}
			if (p.moveDir)
			{
				p.x -= 3;
				if (p.x < 0)
				{
					p.moveDir = false;
					p.x = 0;
				}
			}
			p.y++;
		}

		//检测敌机与玩家的碰撞
		EnemyCollision();

		//消灭超过10个敌机,BOSS出现
		if (enemyEraseCounts >= BOSS_IN)
		{
			//BOSS坐标
			Node tmp(200, 10,false);
			one.CreateBoss(tmp, 200, 100, 50);
			if (one.GetLife()>0)
			{
				int boss_x = one.GetCoord().x;
				int boss_y = one.GetCoord().y;
				int boss_width = one.GetWidth();
				int boss_height = one.GetHeight();
				DrawBossLife();
				setfillcolor(LIGHTRED);
				fillrectangle(boss_x, boss_y, boss_x + boss_width, boss_y + boss_height);
				one.BossMove();
				for (auto& p : bossBulletList) {
					fillcircle(p.x, p.y, 10);
					p.y += rand()%(15);
				}
			}
		}
		//绘制敌机子弹
		for (auto& p : enemyBulletList) {

			setlinecolor(LIGHTRED);
			setfillcolor(LIGHTRED);
			fillcircle(p.x, p.y, 5);
			p.y += 3;
		}

		//删除超出屏幕物体
		//敌机子弹
		int tmp_dir = 0, tmp_max = 795;
		list<Node>::iterator pEb=enemyBulletList.begin();
		DeleteOutScreen(pEb,enemyBulletList,tmp_dir,tmp_max);

		//BOSS子弹
		tmp_dir = 0, tmp_max = 790;
		list<Node>::iterator pBb = bossBulletList.begin();
		DeleteOutScreen(pBb, bossBulletList, tmp_dir, tmp_max);
		DeleteOutScreen(pBb, bossBulletList, tmp_dir, tmp_max);

		//我的子弹
		tmp_dir = 1, tmp_max = 5;
		list<Node>::iterator pMb = bulletList.begin();
		DeleteOutScreen(pMb, bulletList, tmp_dir, tmp_max);

		//删除超出屏幕的敌机
		list<Node>::iterator pDj = enemyPlaneList.begin();
		tmp_dir = 0, tmp_max = 780;
		DeleteOutScreen(pDj, enemyPlaneList, tmp_dir, tmp_max);

		setlinecolor(WHITE);


		one.IsDeleteBoss();
		//左上角显示血量
		DrawText();

		DrawWinOrLose();


		Sleep(1);

		Shoot(); // detection of collision

		EndBatchDraw(); // end batchdraw

		if(playerLife>0)
		IsPressKey(); // detection of keyboard signal

	}

	getchar();

	return 0;
}