#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include <chrono>
#include<iomanip>
#include<string.h>


using namespace std;

enum ConsoleColor
{
	Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, LightGray = 7, DarkGray = 8,
	LightBlue = 9, LightGreen = 10, LightCyan = 11, LightRed = 12, LightMagenta = 13, Yellow = 14, White = 15
};


enum Uprav { STOP = 0, UP, DOWN, LEFT, RIGHT, EXIT };

class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

//Добавление элемента в конец одномерного динамического массива
template<class T>
void addElemArray(T*& p, int& size, T elem)
{
	T* t = new T[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		t[i] = p[i];
	}
	t[size] = elem;
	delete[]p;
	p = t;
	size++;
}

//Поиск по рейтингу
template<class T>
int findRating(T* t, int n, int rating)
{
	for (size_t i = 0; i < n; i++)
	{
		if (t[i].rating == rating)
			return i;
	}
	return -1;
}

//Поиск по имени
template<class T>
int findName(T* t, int n, char *name)
{
	for (size_t i = 0; i < n; i++)
	{
		if (strcmp(t[i].name, name) == 0)
			return i;
	}
	return -1;
}

//Нахождение минимального рейтинга
template<typename T>
int minRating(T* a, int size)
{
	int min = a[0].rating;
	for (int i = 0; i < size; i++)
	{
		if (a[i].rating < min)
			min = a[i].rating;
	}
	return min;
}

