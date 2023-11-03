#pragma once


#define WIN_WIDTH	600
#define	WIN_HEIGHT	800
#define MY_PLANE_WIDTH 32
#define MY_PLANE_HEIGHT 18
#define EPLANE_WIDTH 30
#define EPLANE_HEIGHT 20
#define BOSS_WIDTH 200
#define BOSS_HEIGHT 100
#define BOSS_IN 10

class Node {
public:
	Node() {
		x = 0;
		y = 0;
		moveDir = false;
	};
	Node(int xx, int yy,bool dir) {
		x = xx;
		y = yy;
		moveDir = dir;
	}
	int x;
	int y;
	bool moveDir;
};


class Boss {
public:
	Boss();
	bool CreateBoss(Node a, int w, int h, int l);
	Node GetCoord();
	int GetWidth();
	int GetHeight();
	int GetLife();
	void SetLife();
	void BossMove();
	void IsDeleteBoss();
private:
	Node coord;
	int width;
	int height;
	int life;
	bool bossMoveDir;
};

Boss::Boss()
{
	coord.x = 0;
	coord.y = 0;
	width = 0;
	height = 0;
	life = -1;
	bossMoveDir = false;
}

bool Boss::CreateBoss(Node a, int w, int h, int l)
{
	if (life == -1)
	{
		coord = a;
		width = w;
		height = h;
		life = l;
		return true;
	}
	else
		return false;
}

Node Boss::GetCoord()
{
	return coord;
}

int Boss::GetWidth()
{
	return width;
}

int Boss::GetHeight()
{
	return height;
}

int Boss::GetLife()
{
	return life;
}

void Boss :: SetLife()
{
	life--;
}

void Boss::BossMove()
{
	if (bossMoveDir == false)
	{
		coord.x += 3;
		if (coord.x + 200 >= WIN_WIDTH)
		{
			bossMoveDir = true;
			coord.x = WIN_WIDTH - 200;
		}
	}
	if (bossMoveDir == true)
	{
		coord.x -= 3;
		if (coord.x <= 0)
		{
			bossMoveDir = false;
			coord.x = 0;
		}
	}
}

void Boss::IsDeleteBoss()
{
	if (life == 0)
	{
		coord.x = -200;
		coord.y = -100;
		width = 0;
		height = 0;
		life = 0;
	}
}