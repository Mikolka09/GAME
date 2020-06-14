#include "Record.h"

void Record::SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void Record::loadGame()
{
	ifstream fin("top10.bin", ios::binary | ios::in);
	if (fin.is_open())
	{
		fin.read((char*)&sizeTop, sizeof(sizeTop));
		top10 = new Record[sizeTop];
		for (size_t i = 0; i < sizeTop; i++)
		{
			fin.read((char*)&top10[i], sizeof(Record));
		}
	}
	fin.close();
}

void Record::addIgrok()
{
	system("cls");
	string S(44, '-');
	cout << "\n\n\n";
	SetColor(12, 0);
	cout << "\t\t\tÄîáàâëåíèå èãðîêà â ðåéòèíã" << endl;
	SetColor(15, 0);
	cout << "\t\t" << S << endl;
	Record r;
	cout << endl;
	SetColor(9, 0);
	do
	{
		cout << "\t\tÂâåäèòå Âàøå èìÿ (íå áîëåå 8 áóêâ): ";
		cin >> r.name;
		cin.ignore();
	} while (findName(top10, sizeTop, r.name) != -1);
	r.rating = ((rscore / timer) * 10) + (rscore / 10);
	r.Length = Length;
	r.time = round(timer * 10) / 10;
	addElemArray(top10, sizeTop, r);
	cout << endl;
	SetColor(15, 0);
	cout << "\t\t" << S << endl;
	cout << endl;
	SetColor(12, 0);
	cout << "  \t\t\tÈãðîê äîáàâëåí!" << endl;
	cout << endl;
	SetColor(15, 0);
	system("pause");
}

void Record::resultIgrok()
{
	rating = ((rscore / timer) * 10) + (rscore / 10);
	if (sizeTop == 0)
		addIgrok();
	else
	{
		if (rating >= minRating(top10, sizeTop)
			|| findRating(top10, sizeTop, minRating(top10, sizeTop)) < 20)
		{
			addIgrok();
		}
		else
			exit(0);
	}
	saveGame();
}

void Record::sortTop10(Record** top, int sizeTop)
{
	for (size_t i = 0; i < sizeTop; i++)
	{
		for (size_t j = 0; j < sizeTop - i - 1; j++)
		{
			if (top[j]->rating < top[j + 1]->rating)
				swap(top[j], top[j + 1]);
		}
	}
}

void Record::printTop10()
{
	system("cls");
	string S(38, '-');
	Record** top = new Record * [sizeTop];
	for (size_t i = 0; i < sizeTop; i++)
		top[i] = &top10[i];
	if (sizeTop > 1)
		sortTop10(top, sizeTop);
	cout << "\n\n\n";
	SetColor(12, 0);
	cout << "\t\t  TOP 10 ÈÃÐÛ 'ÏÈÒÎÍ'\n" << endl;
	SetColor(15, 0);
	cout << "\t" << S << endl;
	SetColor(12, 0);
	cout << "\t" << setw(4) << " Íîìåð" << setw(7) << "Èìÿ" << setw(10) << "Ðåéòèíã" << setw(7)
		<< "Äëèíà" << setw(8) << "Âðåìÿ" << endl;
	SetColor(15, 0);
	cout << "\t" << S << endl;
	SetColor(9, 0);
	for (size_t i = 0; i < sizeTop && i < 10; i++)
	{
		cout << "\t" << setw(4) << i + 1 << setw(10) << top[i]->name << setw(8) << top[i]->rating << setw(6)
			<< top[i]->Length << setw(10) << top[i]->time << endl;
	}
	SetColor(15, 0);
	cout << "\t" << S << endl;
	cout << endl;
	system("pause");
}

void Record::printFile()
{
	ofstream out("top10.txt");
	if (out.is_open())
	{
		string S(38, '-');
		Record** top = new Record * [sizeTop];
		for (size_t i = 0; i < sizeTop; i++)
			top[i] = &top10[i];
		if (sizeTop > 1)
			sortTop10(top, sizeTop);
		out << "\n\n\n";
		out << "\t\t  TOP 10 ÈÃÐÛ 'ÏÈÒÎÍ'\n" << endl;
		out << "\t" << S << endl;
		out << "\t" << setw(4) << " Íîìåð" << setw(7) << "Èìÿ" << setw(10) << "Ðåéòèíã" << setw(7)
			<< "Äëèíà" << setw(8) << "Âðåìÿ" << endl;
		out << "\t" << S << endl;
		for (size_t i = 0; i < sizeTop && i < 10; i++)
		{
			out << "\t" << setw(4) << i + 1 << setw(10) << top[i]->name << setw(8) << top[i]->rating << setw(6)
				<< top[i]->Length << setw(10) << top[i]->time << endl;
		}
		out << "\t" << S << endl;
	}
	out.close();
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\n";
	SetColor(4, 0);
	cout << setw(40) << "ÒÀÁËÈÖÀ ÐÅÉÒÈÍÃÀ ÑÎÕÐÀÍÅÍÀ Â ÔÀÉË!" << endl;
	Sleep(2000);
}


void Record::saveGame()
{
	ofstream fout("top10.bin", ios::binary | ios::out);
	if (fout.is_open())
	{
		fout.write((char*)&sizeTop, sizeof(sizeTop));
		for (size_t i = 0; i < sizeTop; i++)
		{
			fout.write((char*)&top10[i], sizeof(Record));
		}
	}
	fout.close();
}
