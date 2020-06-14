#pragma once
#include"Function.h"
#include "Snake.h"


struct Record
{
	char name[8];
	int rating;
	int Length;
	double time;
	int rscore;
	Record* top10 = nullptr;
	int sizeTop = 0;
	double timer;
	Timer t;

	void addIgrok();
	void resultIgrok();
	void sortTop10(Record** top, int sizeTop);
	void printTop10();
	void printFile();
	void loadGame();
	void saveGame();
	void SetColor(int text, int background);

};