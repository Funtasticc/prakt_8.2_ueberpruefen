#include <iostream>
#include <string>
using namespace std;

bool isValid(int i, int j, const int grid[][9]);


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

	// TODO

	bool fehlerhaft = false;


	for (unsigned int x = 0; x < 9; x++)
	{
		bool seen[10] = { false };

		for (unsigned int y = 0; y < 9; y++)
		{
			// Finde Duplikate
			for (unsigned int y2 = y + 1; y2 < 9; y2++)
			{
				if (sudoku[y][x] == sudoku[y2][x])
				{
					cout << "Spalte " << x << ": Zahl " << sudoku[y][x] << " kommt mehrfach vor." << endl;
					fehlerhaft = true;
				}
			}

			// Merke die Zahlen
			if (!seen[sudoku[y][x]])
			{
				seen[sudoku[y][x]] = true;
			}
		}

		for (int i = 1; i <= 9; i++)
		{
			if (!seen[i])
			{
				cout << "Spalte " << x << ": Zahl " << i << " kommt nicht vor." << endl;
				fehlerhaft = true;
			}
		}
	}

	for (unsigned int y = 0; y < 9; y++)
	{
		bool seen[10] = { false };

		for (unsigned int x = 0; x < 9; x++)
		{

			for (unsigned int x2 = x + 1; x2 < 9; x2++)
			{
				if (sudoku[y][x] == sudoku[y][x2])
				{
					cout << "Zeile " << y << ": Zahl " << sudoku[y][x] << " kommt mehrfach vor." << endl;
					fehlerhaft = true;
				}
			}

			if (!seen[sudoku[y][x]])
			{
				seen[sudoku[y][x]] = true;
			}
		}
		for (int i = 1; i <= 9; i++)
		{
			if (!seen[i])
			{
				cout << "Zeile " << y << ": Zahl " << i << " kommt nicht vor." << endl;
				fehlerhaft = true;
			}
		}
	}

	// Block zu Block
	int block_cnt = 0;

	for (unsigned int y = 0; y < 9; y += 3)
	{
		for (unsigned int x = 0; x < 9; x += 3)
		{
			// Blöcke

			unsigned int block_zahlen[9];
			unsigned int cnt = 0;

			for (unsigned y2 = y; y2 < y + 3; y2++)
			{
				for (unsigned x2 = x; x2 < x + 3; x2++)
				{
					block_zahlen[cnt] = sudoku[y2][x2];
					cnt++;
				}

				if ((y2 + 1) % 3 == 0)
				{
					unsigned int zahlenbereich[10] = { 0 };
					for (unsigned int i = 0; i < 9; i++)
					{
						zahlenbereich[block_zahlen[i]]++;
					}

					for (unsigned int j = 1; j <= 9; j++)
					{
						if (zahlenbereich[j] > 1)
						{
							cout << "Block " << block_cnt << ": Zahl " << j << " kommt mehrfach vor." << endl;
							fehlerhaft = true;
						}
						else if (zahlenbereich[j] < 1)
						{
							cout << "Block " << block_cnt << ": Zahl " << j << " kommt nicht vor." << endl;
							fehlerhaft = true;
						}
					}
					cnt = 0;
					block_cnt++;
				}
			}
		}
	}

	if (!fehlerhaft)
	{
		cout << "Das Sudoku ist gueltig." << endl;
	}


	system("pause");
	return 0;
}





//	bool isValid(int i, int j, const int grid[][9]);
//	{
//
//		/*int i = 0, j = 0;*/
//		// Check whether grid[i][j] is valid at the i's row
//		for (int column = 0; column < 9; column++)
//			if (column != j && sudoku[i][column] == sudoku[i][j])
//				return false;
//
//		// Check whether grid[i][j] is valid at the j's column
//		for (int row = 0; row < 9; row++)
//			if (row != i && sudoku[row][j] == sudoku[i][j])
//				return false;
//
//		//check whether grid[i][j] is valid in the 3-by-3 box
//		for (int row = (i / 3) * 3; row < (i / 3) * 3 + 3; row++)
//			for (int col = (j / 3) * 3; col < (j / 3) * 3 + 3; col++)
//				if (row != i && col != j && sudoku[row][col] == sudoku[i][j])
//
//
//					return true; // the current value at grid[i][j] is valid
//	}
//
//	isValid(const int sudoku[][9]);
//	{
//		for (int i = 0; i < 9; i++)
//			for (int j = 0; j < 9; j++)
//				if (sudoku[i][j] < 0 || sudoku[i][j] > 9 || (sudoku[i][j] != 0 && !isValid(i, j, sudoku)))
//					return false;
//		return true; // The fixed cells are valid
//	}
//
//	if (!isValid(sudoku))
//		cout << "Invalid input" << endl;
//
//
//
//	//checks the numbers in the column to see if any match the user value
//	//for (int count = 0; count < 9; count++)
//	//{
//	//	if (sudoku[row][count] == value)
//	//	{
//	//		cout << "ERROR: Value \'" << value << "\' in square \'"
//	//			<< (char)toupper(coord1) << coord2 << "\' is invalid\n";
//	//	}
//	//}
//
//
//	//bool check_b();
//	//{
//	//	bool seen[10] = { false };  // 9+1 bools, dann brauchen wir keinen Offset beim Zugriff
//	//	for (int x = 0; x < 3; x++)
//	//	{
//	//		for (int y = 0; y < 3; y++)
//	//		{
//	//			if (seen[sudoku[x][y]] == true)
//	//				return false;
//	//			else
//	//				seen[sudoku[x][y]] = true;
//
//	//			/*cout << "Spalte " << y << ": Zahl " << x << "kommt " << check << " vor.";*/
//
//	//		}
//	//		return true;
//	//	}
//	//}
//
//	//check_b();
//	//if (seen[10] == true)
//	//{
//
//	//}
//
//	//bool function_check_zeile(int zahl, int zeile, int spalte);
//	//{
//	//	int zahl, zeile, spalte;
//
//	//	for (int i = 0; i < 9; i++)
//	//		if ((sudoku[i][spalte] == zahl) || (sudoku[zeile][i] == zahl))
//	//			return false;
//	//	return true;
//	//}
//
//	//function_check_zeile(sudoku[0], sudoku[])
//
//
//	
//
//	//check_win();
//
//	//cout << ""
//
//	//void row_verify(int sudoku[9][9]);
//	//{
//	//	char temp;
//	//	int count;
//	//	for (int i = 0; i < 9; i++) {
//	//		for (int j = 0; j < 3; j++) {
//	//			for (int k = 0; k < 3; k++) {
//	//				temp = sudoku[j + i][k + (i % 3) * 3];
//	//				count = 0;
//	//				if (temp != '.') { //my test for blanks
//	//					for (int m = 0; m < 3; m++) {
//	//						for (int n = 0; n < 3; n++) {
//	//							if (sudoku[m + i][n + (i % 3) * 3] == temp)
//	//								count++;
//	//						}
//	//					}
//	//				}
//	//			}
//	//			if (count >= 2) {
//	//				cout << "Reihe " << i + 1<< " is invalid." << endl; //using i+1 to fit in my numbering of box
//	//				break;
//	//			}
//	//		}
//	//	}
//	//}
//
//	//void subsq_verify(char x[9][9]);
//	//{
//	//	char temp;
//	//	int count;
//	//	for (int i = 0; i < 9; i++) {
//	//		for (int j = 0; j < 3; j++) {
//	//			for (int k = 0; k < 3; k++) {
//	//				temp = sudoku[j + i][k + (i % 3) * 3];
//	//				count = 0;
//	//				if (temp != '.') { //my test for blanks
//	//					for (int m = 0; m < 3; m++) {
//	//						for (int n = 0; n < 3; n++) {
//	//							if (sudoku[m + i][n + (i % 3) * 3] == temp)
//	//								count++;
//	//						}
//	//					}
//	//				}
//	//			}
//	//			if (count >= 2) {
//	//				cout << "Block " << i + 1 << ": Zahl " <<  " kommt " << "vor." << endl; //using i+1 to fit in my numbering of box
//	//				break;
//	//			}
//	//		}
//	//	}
//	//}
//		/*… die Zeilen des Blocks im Bereich
//		von zeile = block / 3 * 3 bis zeile <= block / 3 * 3 + 2
//
//		… die Spalten des Blocks im Bereich
//		von spalte = block % 3 * 3 bis spalte <= block % 3 * 3 + 2*/
//
//		//cout << "Spalte " << spalte << ": Zahl " << zahl << "kommt " << haeufigk << " vor."
//
//
//	
//	system("PAUSE");
//	return 0;
//}
//
//bool isValid(int i, int j, const int grid[][9])
//{
//	return false;
//}
