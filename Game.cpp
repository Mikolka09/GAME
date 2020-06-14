#include "Game.h"

void Game::SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Game::Setup()
{
	dir = STOP;
	piton.x = width / 2;
	piton.y = height / 2;
	xrabbit = rand() % (width - 2);
	yrabbit = rand() % (height - 1);
	piton.score = 0;
	piton.ntail = 0;
	rec.t.reset();
}

void Game::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Game::DrawMap()
{
	setlocale(0, "");
	gotoxy(0, 0);
	cout << endl;
	SetColor(5, 0);
	cout << "\t\t\tÈÃÐÀ 'ÏÈÒÎÍ'" << endl;
	SetColor(15, 0);
	cout << "\t\t\t-----------" << endl;
	SetColor(12, 0);
	cout << " Ââåðõ - PgUp; Âíèç - PgDn; Âëåâî - PgLeft; Âïðàâî - PgRt; Âûõîä - ESC" << endl;
	setlocale(0, "C");
	for (int i = 0; i < width + 1; i++)
	{
		SetColor(8, 0);
		cout << char(254);
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				SetColor(8, 0);
				cout << char(219);
			}
			if (i == piton.y && j == piton.x)
			{
				SetColor(6, 0);
				cout << char(64);
			}
			else
			{
				if (i == yrabbit && j == xrabbit)
				{
					SetColor(11, 0);
					cout << char(206);
				}
				else
				{
					bool print = false;
					for (int t = 0; t < piton.ntail; t++)
					{
						if (piton.xtail[t] == j && piton.ytail[t] == i)
						{
							print = true;
							SetColor(10, 0);
							cout << char(253);
						}
					}
					if (!print)
						cout << " ";
				}
			}

		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++)
	{
		SetColor(8, 0);
		cout << char(254);
	}
	setlocale(0, "");
	cout << endl;
	SetColor(4, 0);
	cout << "\tC×ÅÒ = " << piton.score << setw(15) << " ÄËÈÍÀ = " << piton.ntail
		<< setw(15) << "ÂÐÅÌß = " << rec.t.elapsed() << endl;
}

void Game::Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 72:
			if (dir != DOWN)
				dir = UP;
			break;
		case 80:
			if (dir != UP)
				dir = DOWN;
			break;
		case 77:
			if (dir != LEFT)
				dir = RIGHT;
			break;
		case 75:
			if (dir != RIGHT)
				dir = LEFT;
			break;
		case 27:
			dir = EXIT;
			break;
		}
	}
}

bool Game::Logic()
{
	int dx = piton.xtail[0];
	int dy = piton.ytail[0];
	int d2x, d2y;
	piton.xtail[0] = piton.x;
	piton.ytail[0] = piton.y;
	for (int i = 1; i < piton.ntail; i++)
	{
		d2x = piton.xtail[i];
		d2y = piton.ytail[i];
		piton.xtail[i] = dx;
		piton.ytail[i] = dy;
		dx = d2x;
		dy = d2y;
	}
	switch (dir) {
	case LEFT:
		piton.x--;
		Sleep(80);
		break;
	case RIGHT:
		piton.x++;
		Sleep(80);
		break;
	case UP:
		piton.y--;
		Sleep(100);
		break;
	case DOWN:
		piton.y++;
		Sleep(100);
		break;
	case EXIT:
		return 0;
	}
	if (piton.x > width - 2 || piton.x < 0 || piton.y > height - 1 || piton.y < 0)
		return false;
	for (int i = 0; i < piton.ntail; i++)
	{
		if (piton.xtail[i] == piton.x && piton.ytail[i] == piton.y)
			return false;
	}
	if (xrabbit > width - 2 || xrabbit < 0 || yrabbit > height - 1 || yrabbit < 0)
	{
		xrabbit = rand() % (width - 2);
		yrabbit = rand() % (height - 1);
	}
	if (piton.x == xrabbit && piton.y == yrabbit)
	{
		piton.score = piton.score + 100;
		rec.rscore = piton.score;
		xrabbit = rand() % (width - 2);
		yrabbit = rand() % (height - 1);
		piton.ntail++;
		rec.Length = piton.ntail;
	}
	return true;
}

void Game::menu()
{
	rec.loadGame();
	cout << "\n\n\n\n\n\n\n\n\n\n";
	SetColor(5, 0);
	cout << setw(40) << " ÄÎÁÐÎ ÏÎÆÀËÎÂÀÒÜ Â ÈÃÐÓ 'ÏÈÒÎÍ'" << endl;
	Sleep(3000);
	do
	{
		system("cls");
		cout << "\n\n\n\n\n\n";
		SetColor(12, 0);
		cout << "\t\t\tÌÅÍÞ ÈÃÐÛ:\n" << endl;
		SetColor(9, 0);
		cout << "\t\t\t1. ÍÎÂÀß ÈÃÐÀ\n" << endl;
		cout << "\t\t\t2. ÏÐÀÂÈËÀ ÈÃÐÛ\n" << endl;
		cout << "\t\t\t3. ÑÎÕÐÀÍÈÒÜ ÒÎÏ-10 Â ÔÀÉË\n" << endl;
		cout << "\t\t\t4. ÒÎÏ-10 ÐÅÉÒÈÍÃÀ ÍÀ ÝÊÐÀÍ\n" << endl;
		cout << "\t\t\t5. ÂÛÕÎÄ ÈÇ ÈÃÐÛ\n\n" << endl;
		SetColor(12, 0);
		cout << "\t\tÂÀØ ÂÛÁÎÐ:";
		int vib;
		cin >> vib;
		SetColor(15, 0);
		switch (vib)
		{
		case 1:
			system("cls");
			Setup();
			while (Logic())
			{
				DrawMap();
				Input();
				Logic();
			}
			GameOver();
			break;
		case 2:
			regulatGame();
			break;
		case 3:
			rec.printFile();
			break;
		case 4:
			rec.printTop10();
			break;
		case 5:
			exit(0);
		default:
			break;
		}

	} while (true);
}

void Game::regulatGame()
{
	system("cls");
	cout << "\n\n\n\n\n\n";
	SetColor(12, 0);
	cout << "\t\tÏÐÀÂÈËÀ ÈÃÐÛ 'ÏÈÒÎÍ':\n" << endl;
	SetColor(9, 0);
	cout << "\tÏðàâèëî èãðû çàêëþ÷àåòñÿ â ïîåäàíèè ÏÈÒÎÍÎÌ êðîëèêîâ.\n"
		<< "\tÏîñëå êàæäîãî ñúåäåííîãî êðîëèêà ó ÏÈÒÎÍÀ âûðîñòàåò  õâîñò.\n"
		<< "\tÏðè ýòî çàïðåøàåòñÿ âðåçàòñÿ â ñòåíû è â ñîáñòâåííûé õâîñò.\n"
		<< "\tÐåéòèíã ëó÷øåãî èãðîêà îïðåäåëÿåòñÿ äåëåíèåì î÷êîâ çà ñúåäåííûõ\n"
		<< "\têðîëèêîâ íà ïîòðà÷åííîå íà ýòî âðåìÿ, ïëþñ êîëè÷åñòâî ñúåäåíûõ\n"
		<< "\têðîëèêîâ â äåñÿòèêðàòíîì ðàçìåðå.\n" << endl;
	SetColor(12, 0);
	cout << "\t\t Óïðàâëåíèå ÏÈÒÎÍÎÌ:\n" << endl;
	SetColor(9, 0);
	cout << "\tÑòðåëêà Ââåðõ (PgUp) - äâèæåíèå ââåðõ.\n"
		<< "\tÑòðåëêà Âíèç (PgDown) - äâèæåíèå âíèç.\n"
		<< "\tÑòðåëêà Âïðàâî (PgRight) - äâèæåíèå âïðàâî.\n"
		<< "\tÑòðåëêà Âëåâî (PgLeft) - äâèæåíèå âëåâî.\n"
		<< "\tÊîïêà Escape (Esc) - âûõîä èç èãðû.\n" << endl;
	SetColor(15, 0);
	system("pause");
}

void Game::GameOver()
{
	if (!Logic())
	{
		rec.timer = rec.t.elapsed();
		system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		SetColor(4, 0);
		cout << setw(40) << "ÊÎÍÅÖ ÈÃÐÛ!" << endl;
		Sleep(3000);
	}
	SetColor(15, 0);
	if (piton.score != 0)
	{
		rec.resultIgrok();
	}
}
