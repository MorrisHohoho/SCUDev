#pragma once
struct BOMBITEM
{
	int existsTime;
	int bomb_x;
	int bomb_y;
};

//炸弹类
class Bomb {
public:
	void CreateBomb(int x, int y);
	void DeleteBomb(int i);
	int GetBombCounts();
	void SetBombLife(int i);
	void SetBombMax(int i);
	BOMBITEM GetBomb(int x);
private:
	int bombCounts = 0;
	int bombMax = 2;
	struct BOMBITEM item[8];
};


void Bomb::CreateBomb(int x, int y)
{
	//最多三个炸弹
	if (bombCounts < bombMax)
	{
		bombCounts++;
		int tmp = bombCounts;
		while (tmp>0)
		{
			if (item[tmp].existsTime != 0)
				tmp--;
			else
			{
				item[tmp] = {1,(x / BLOCKWIDTH) * BLOCKWIDTH + 25,(y / BLOCKWIDTH) * BLOCKWIDTH + 25};
				break;
			}
		}
	}
	else
		return;
}

void Bomb::DeleteBomb(int i)
{
	item[i] = {
		0,0,0
	};
	bombCounts--;
}

void Bomb::SetBombLife(int i)
{
	item[i].existsTime++;
}

BOMBITEM Bomb::GetBomb(int x)
{
	return item[x];
}

int Bomb::GetBombCounts()
{
	return bombCounts;
}

void Bomb::SetBombMax(int i)
{
	bombMax = i;
}