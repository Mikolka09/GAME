#pragma once

struct Snake
{
	int x;
	int y;
	int score;
	int xtail[100] = { 0 };
	int ytail[100] = { 0 };
	int ntail;
};
