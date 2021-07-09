#include "Game15.h"

Game::Game()
{
	MixMap();
}

void Game::MoveRight()
{
	Point p = FindPlayer();
	if (p.x < width - 1)
		Swap(*GetCellPtr(p.x, p.y), *GetCellPtr(p.x + 1, p.y));
}

void Game::MoveLeft()
{
	Point p = FindPlayer();
	if (p.x > 0)
		Swap(*GetCellPtr(p.x, p.y), *GetCellPtr(p.x - 1, p.y));
}

void Game::MoveUp()
{
	Point p = FindPlayer();
	if (p.y > 0)
		Swap(*GetCellPtr(p.x, p.y), *GetCellPtr(p.x, p.y - 1));
}

void Game::MoveDown()
{
	Point p = FindPlayer();
	if (p.y < width - 1)
		Swap(*GetCellPtr(p.x, p.y), *GetCellPtr(p.x, p.y + 1));
}

bool Game::IsWin() const
{
	for (int i = 0; i < width * width - 1; i++)
		if (map[i] > map[i + 1]) return false;
	return true;
}

Point Game::FindPlayer() const
{
	constexpr int player = width * width;
	for (int i = 0; i < player; i++)
		if (map[i] == player)
			return Point(i % width, i / width);
}

void Game::Swap(int8_t& p1, int8_t& p2)
{
	p1 = p1 ^ p2;
	p2 = p1 ^ p2;
	p1 = p1 ^ p2;
}

void Game::MixMap()
{
	for (int n = 0; n < 500; n++)
	{
		int com = random(4);
		if (com == 0)
			MoveRight();
		else if (com == 1)
			MoveLeft();
		else if (com == 2)
			MoveUp();
		else if (com == 3)
			MoveDown();
	}
}
