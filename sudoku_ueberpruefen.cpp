#include <iostream>
#include <string>
using namespace std;

int main()
{
	int sudoku[9][9] = { };
	string eingabe[11] = { };
	int m = 0, z = 0;

	for (int i = 0; i < 11; i++)
	{
		if (i == 0)
			cout << "Bitte geben Sie das Sudoku ein:" << endl;

		getline(cin, eingabe[i]);
		m = 0;

		for (int k = 0; k < eingabe[i].size(); k++)
		{


			if ((eingabe[i].at(k) >= '1') && (eingabe[i].at(k) <= '9'))
			{
				sudoku[z][m] = (eingabe[i].at(k) - int('0'));
				m++;
			}

		}

		if (eingabe[i][0] == '.')
		{
			z++;
		}
	}

	cout << endl;

	for (int y = 0; y <= 8; y++)
	{
		if (y == 3)
		{
			cout << "=======//======//======" << endl;
		}
		if (y == 6)
		{
			cout << "=======//======//======" << endl;
		}

		for (int x = 0; x <= 8; x++)
		{
			if (x == 0)
			{
				cout << ";";
			}

			cout << sudoku[y][x];

			if (x >= 0 && x <= 7)
				cout << ";";
			if (x == 2)
				cout << "//";
			if (x == 5)
				cout << "//";
			if (x == 8)
				cout << endl;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////
	bool fehlerhaft = false;


	// SPALTE

	for (unsigned int x = 0; x < 9; x++)
	{
		bool gesehen[10] = { false }; // auf falsch

		for (unsigned int y = 0; y < 9; y++)
		{
			// Finde Duplikate, y2 wird hochgezaehlt um das jetzige y mit allen nachfolgenden Zahlen zu vergleichen
			for (unsigned int y2 = y + 1; y2 < 9; y2++)
			{
				if (sudoku[y][x] == sudoku[y2][x]) // Die Zahl "y" wird mit den nachfolgenden Zahlen y2+1 verglichen, wennsie gleich ist, kommt sie mehrfach vor
				{								
					cout << "Spalte " << x << ": Zahl " << sudoku[y][x] << " kommt mehrfach vor." << endl;
					fehlerhaft = true;
				}
			}

			// Vergleiche die Zahlen mit Array gesehen[10]
			if (!gesehen[sudoku[y][x]])
			{
				gesehen[sudoku[y][x]] = true;	// Wert 5 als erster Wert ? 5 wird in array gesehen[10] auf true gesetzt
			}
		}

		for (int i = 1; i <= 9; i++)
		{
			if (!gesehen[i])	// wurde ein Wert NICHT gesehen wird dies hier ausgesagt!
			{
				cout << "Spalte " << x << ": Zahl " << i << " kommt nicht vor." << endl;
				fehlerhaft = true;
			}
		}
	}

	// ZEILE

	for (unsigned int y = 0; y < 9; y++)
	{
		bool gesehen[10] = { false };

		for (unsigned int x = 0; x < 9; x++)
		{

			for (unsigned int x2 = x + 1; x2 < 9; x2++)
			{
				if (sudoku[y][x] == sudoku[y][x2]) // Die Zahl "x" wird mit den nachfolgenden .5.2.3. die 5 mit 2, dann 3 usw Zahlen verglichen
				{
					cout << "Zeile " << y << ": Zahl " << sudoku[y][x] << " kommt mehrfach vor." << endl;
					fehlerhaft = true;
				}
			}

			if (!gesehen[sudoku[y][x]])
			{
				gesehen[sudoku[y][x]] = true; // Wert 5 als erster Wert ? 5 wird in array gesehen[10] auf true gesetzt
			}
		}
		for (int i = 1; i <= 9; i++) // Array wird von 1 bis 9 durchlaufen
		{
			if (!gesehen[i]) // wurde ein Wert NICHT gesehen wird dies hier ausgesagt!
			{
				cout << "Zeile " << y << ": Zahl " << i << " kommt nicht vor." << endl;
				fehlerhaft = true;
			}
		}
	}


	// BLOCK

	unsigned int block_counter = 0;

	for (unsigned int y = 0; y < 9; y += 3)
	{
		for (unsigned int x = 0; x < 9; x += 3)
		{
			unsigned int block_zahlen[9];
			unsigned int counter = 0;

			for (unsigned y2 = y; y2 < y + 3; y2++) // Spalte vom Block wird erhöht
			{
				for (unsigned x2 = x; x2 < x + 3; x2++) // Zeile vom Block wird eingelesen
				{
					block_zahlen[counter] = sudoku[y2][x2]; // Der Array wird mit den Block Zahlen ausgefüllt
					counter++;
				}													// kompletter Block wird eingelesen

				if ((y2 + 1) % 3 == 0)	// wenn Block eingelesen, wird er überprüft z.B. 2+1 % 3 == 0 
				{
					unsigned int zahlenbereich[10] = { 0 };
					for (unsigned int i = 0; i < 9; i++)
					{
						zahlenbereich[block_zahlen[i]]++; // zahlenbereich[10] wird um jeweils 1 an der Stelle erhöht
					}

					for (unsigned int j = 1; j <= 9; j++) // wenn der Array an der Stelle groesser als 1 oder kleiner als 1 ist...
					{
						if (zahlenbereich[j] > 1) 
						{
							cout << "Block " << block_counter << ": Zahl " << j << " kommt mehrfach vor." << endl; // kommt die Zahl mehrfach vor ... 
							fehlerhaft = true;
						}
						else if (zahlenbereich[j] < 1)
						{
							cout << "Block " << block_counter << ": Zahl " << j << " kommt nicht vor." << endl; // oder garnicht
							fehlerhaft = true;
						}
					}
					counter = 0;
					block_counter++;
				}
			}
		}
	}

	if (!fehlerhaft)
	{
		cout << "Das Sudoku ist gueltig." << endl;
	}
	system("PAUSE");
	return 0;
}
