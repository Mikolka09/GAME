#pragma once

#include"Function.h"
#include"Snake.h"
#include"Record.h"

struct Game
{
	Snake piton;
	Uprav dir;
	Record rec;
	const int height = 33;
	const int width = 70;
	int xrabbit;
	int yrabbit;
			
	
	void SetColor(int text, int background);
	void Setup();
	void gotoxy(int x, int y);
	void DrawMap();
	void Input();
	bool Logic();
	void menu();
	void regulatGame();
	void GameOver();
	
};
