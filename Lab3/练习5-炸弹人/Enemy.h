#pragma once


#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define BLOCKWIDTH 50


#include<stdlib.h>
//敌人类
class Enemy {
public:
	void CreateEnemy(int x, int y, bool flag);
	int GetEnemy_x();
	int GetEnemy_y();
	bool GetEnemyLife();
	void DeleteEnemy();
	void EnemyMove(int w, int speed, int r, bool Box[][17], int player_x, int player_y);
private:
	bool enemyFlag = false;
	int x = -1;
	int y = -1;
};

void Enemy::CreateEnemy(int x, int y, bool flag)
{
	this->x = x;
	this->y = y;
	this->enemyFlag = flag;
}

int Enemy::GetEnemy_x()
{
	return x;
}

int Enemy::GetEnemy_y()
{
	return y;
}

bool Enemy::GetEnemyLife()
{
	return enemyFlag;
}

void Enemy::DeleteEnemy()
{
	enemyFlag = false;
	x = 2000;
	y = 2000;
}

void Enemy::EnemyMove(int w, int speed, int r, bool Box[][17], int player_x, int player_y)
{
	//移动前与玩家的距离
	int delta_x = abs(x - player_x);
	int delta_y = abs(y - player_y);

	//随机方向
	int dir = (rand() % 4) + 1;

	//如果移动后离玩家更远，则取消这次移动
	switch (dir)
	{
	case UP:
	{
		if (((x - 25) % 100 == 0) && Box[x / BLOCKWIDTH][(y - speed - r) / BLOCKWIDTH] == false)
		{
			y -= speed;
			if (y <= r) y = r + 5;
			if (abs(y - player_y) < delta_y)
				break;
			else
				y += speed;
		}
		break;
	}
	case DOWN:
	{
		if (((x - 25) % 100 == 0) && Box[x / BLOCKWIDTH][(y + speed + r) / BLOCKWIDTH] == false)
		{
			y += speed;
			if (y >= w - r) y = w - r - 5;
			if (abs(y - player_y) < delta_y)
				break;
			else
				y -= speed;
		}
		break;
	}
	case LEFT:
	{
		if (((y - 25) % 100 == 0) && Box[(x - speed - r) / BLOCKWIDTH][y / BLOCKWIDTH] == false)
		{
			x -= speed;
			if (x <= r) x = r + 5;
			if (abs(x - player_x) < delta_x)
				break;
			else
				x += speed;
		}
		break;
	}
	case RIGHT:
	{
		if (((y - 25) % 100 == 0) && Box[(x + speed + r) / BLOCKWIDTH][y / BLOCKWIDTH] == false)
		{
			x += speed;
			if (x >= w - r) x = w - r - 5;
			if (abs(x - player_x) < delta_x)
				break;
			else
				x -= speed;
		}
		break;
	}
	default:
		break;
	}

}