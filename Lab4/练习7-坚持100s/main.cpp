/*
实现功能:
1.基础功能：子弹和火箭的碰撞，右上角心形血量条，左上角显示坚持时间，爆炸贴图，背景音乐和受伤音乐。
2.进阶功能：在坚持超过50s后飞碟出现，玩家碰到飞碟就会立即死亡。
*/


#include <graphics.h>  
#include <conio.h>
#include <time.h>
#include "EasyXPng.h"  // 用于显示带透明通道的png图片
#include<iostream>

using namespace std;
#define  WIDTH 560 // 画面宽度
#define  HEIGHT 800 // 画面高度
#define MAXBULLETLEN	200	//最多子弹个数

#pragma comment(lib,"Winmm.lib")

class Rocket  // 定义火箭类
{
public:
	IMAGE im_rocket;             // 火箭图像
	float x, y;                  // 火箭坐标
	float width, height;         // 火箭图片的宽度、高度
	float im_x, im_y;
	int life;	

	void draw()                  // 显示火箭相关信息	
	{
		im_x = x - width / 2;
		im_y = y - height / 2;
		putimagePng(im_x,im_y, &im_rocket);
		// 游戏中显示火箭
	}

	void update(float mx, float my) // 根据输入的坐标更新火箭的位置
	{
		x = mx;
		y = my;
	}
};

class Bullet	//定义子弹类
{
public:
	IMAGE im_bullet;	//子弹图像
	float x, y;			//子弹坐标
	float vx, vy;		//子弹速度
	float radius;		//接近球体的子弹半径大小
	bool cld;	//子弹是否撞到火箭

	void draw()
	{
		putimagePng(x - radius, y - radius, &im_bullet);
	}

	void update()
	{
		x += vx;
		y += vy;
		if (x <= 0 || x >= WIDTH)
			vx = -vx;
		if (y <= 0 || y >= HEIGHT)
			vy = -vy;
	}
};

class Ufo	//定义飞碟
{
public:
	IMAGE im_ufo;
	float x, y;
	float width, height;
	float v;
	bool app;

	void draw()
	{
		putimagePng(x, y, &im_ufo);
	}

	void update(float rocketX, float rocketY)
	{
		if (x - rocketX >= 0)
			x-=v;
		else
			x+=v;
		if (y - rocketY >= 0)
			y-=v;
		else
			y+=v;
		if (x <= 0)
			x = 0;
		if (x >= WIDTH)
			x = WIDTH;
		if (y <= 0)
			y = 0;
		if (y >= HEIGHT)
			y = HEIGHT;
	}
};

IMAGE im_bk, im_rocket,im_bullet,im_life,im_bomb,im_ufo;  // 定义图像对象	
Rocket rocket;  // 定义火箭对象
Bullet bullet[MAXBULLETLEN];	//定义子弹对象
Ufo ufo;

int bulletNum = 0;	//记录已有子弹个数
int times = 0;

void startup()  //  初始化函数
{
	srand(time(0)); // 初始化随机种子
	loadimage(&im_bk, _T("./Pictures/background.png")); // 导入背景图片
	loadimage(&im_rocket, _T("./Pictures/rocket.png")); // 导入火箭图片
	loadimage(&im_bullet, _T("./Pictures/bullet.png"));	//导入子弹图片
	loadimage(&im_life, _T("./Pictures/Life1.png"));	//导入生命值图片
	loadimage(&im_bomb, _T("./Pictures/blowup.png"));	//导入爆炸图片
	loadimage(&im_ufo, _T("./Pictures/ufo.png"));		//导入飞碟图片

	// 对rocket一些成员变量初始化
	rocket.im_rocket = im_rocket;  // 设置火箭图片
	rocket.width = im_rocket.getwidth(); // 设置火箭宽度
	rocket.height = im_rocket.getheight(); // 设置火箭高度
	rocket.life = 5;	//五条命

	//初始化Ufo;
	ufo.im_ufo = im_ufo;
	ufo.x = WIDTH / 2;
	ufo.y = -100;
	ufo.width = im_ufo.getwidth();
	ufo.height = im_ufo.getheight();
	ufo.v = 2;
	ufo.app = false;

	initgraph(WIDTH, HEIGHT,EX_SHOWCONSOLE); // 新开一个画面
	BeginBatchDraw(); // 开始批量绘制

	mciSendString(_T("open game_music.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
}

void show()  // 绘制函数
{
	putimage(0, 0, &im_bk);	// 显示背景	

	if (rocket.life <= 0)
	{
		putimagePng(rocket.x, rocket.y, &im_bomb);
	}
	else
	rocket.draw();  // 显示火箭及相关信息
	

	if(ufo.app)
		ufo.draw();

	for (int i = 0; i < bulletNum; i++)
		bullet[i].draw();
	
	//显示火箭生命值
	for (int i = 0; i < rocket.life; i++)
	{
		putimagePng(10 + 20 * i, 10, &im_life);
	}

	//右上角显示时间
	TCHAR s[20];
	setbkmode(TRANSPARENT);
	_stprintf_s(s, _T("%d秒"), times);
	settextstyle(50, 0, _T("Arial"));
	outtextxy(460, 10, s);


	if (times >= 1)
	{
		TCHAR s[20];
		setbkmode(TRANSPARENT);
		_stprintf_s(s, _T("YOU WIN!!!"));
		settextstyle(100, 0, _T("Arial"));
		outtextxy(20, 400, s);
		rocket.life = 5;
	}

	FlushBatchDraw(); // 批量绘制
	Sleep(10); // 暂停
}

void UpdateWithoutInput()
{
	static int lastSecond = 0;
	static int nowSecond = 0;
	static clock_t start = clock();
	clock_t now = clock();

	if(rocket.life>0)
	times = (int(now - start) / CLOCKS_PER_SEC);
	nowSecond = (int(now - start) / CLOCKS_PER_SEC);

	if (nowSecond > 50)
		ufo.app = true;

	if (nowSecond == lastSecond + 2)
	{
		lastSecond = nowSecond;

		if (bulletNum < MAXBULLETLEN)
		{
			bullet[bulletNum].x = WIDTH / 2;
			bullet[bulletNum].y = 10;
			float angle = (rand() / double(RAND_MAX) - 0.5) * 0.9 * PI;
			float scalar = 2 * rand() / double(RAND_MAX) + 2;
			bullet[bulletNum].vx = scalar * sin(angle);
			bullet[bulletNum].vy = scalar * cos(angle);
			bullet[bulletNum].im_bullet = im_bullet;
			bullet[bulletNum].radius = im_bullet.getwidth() / 2;
			bullet[bulletNum].cld = false;
		}
		bulletNum++;
	}

	for (int i = 0; i < bulletNum; i++)
	{
		bullet[i].update();
	}

	if(ufo.app)
	ufo.update(rocket.x,rocket.y);

}

void updateWithInput()               // 和输入相关的更新
{
	MOUSEMSG m;		                 // 定义鼠标消息
	while (MouseHit()&&rocket.life>0)               // 检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)  // 到鼠标移动时			
			rocket.update(m.x, m.y); // 火箭的位置等于鼠标所在的位置
	}

	//碰撞
	for (int i = 0; i < bulletNum; i++)
	{
		float bulletLeft = bullet[i].x - bullet[i].radius;
		float bulletRight = bullet[i].x + bullet[i].radius;
		float bulletTop = bullet[i].y - bullet[i].radius;
		float bulletDown = bullet[i].y + bullet[i].radius;
		if (bulletRight > rocket.im_x && bulletLeft < rocket.im_x + rocket.width && bullet[i].cld==false)
		{
			if (bulletTop<rocket.im_y + rocket.height && bulletDown>rocket.im_y)
			{
				rocket.life--;
				bullet[i].cld = true;
				bullet[i].im_bullet.Resize(1,1);	//没找到删除贴图的函数，用resize将就替代一下
				mciSendString(_T("open classic_hurt.mp3 alias htmusic"), NULL, 0, NULL);
				mciSendString(_T("play htmusic from 0"), NULL, 0, NULL);
			}
		}
	}

	//飞碟碰撞
	if (ufo.x + ufo.width/2 > rocket.im_x && ufo.x < rocket.im_x + rocket.width)
	{
		if (ufo.y - ufo.height / 2 < rocket.im_y + rocket.height && ufo.y + ufo.height / 2 > rocket.im_y)
		{
			rocket.life = 0;
			mciSendString(_T("open classic_hurt.mp3 alias htmusic"), NULL, 0, NULL);
			mciSendString(_T("play htmusic from 0"), NULL, 0, NULL);
		}
		
	}
	
}

int main() // 主函数
{
	startup();  // 初始化	
	while (1)  // 重复运行
	{
		show();  // 绘制
		UpdateWithoutInput();	//和输入无关的更新
		updateWithInput();  // 和输入相关的更新
	}
	return 0;
}