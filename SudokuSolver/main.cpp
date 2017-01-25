#include <iostream>
#include <string>

#include "Sudoku.h"


void loadSudokuFromTxtTest()
{
	const std::string fileName = "Data/sudoku.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);
	std::cout << sudoku << "\n";
}

int main(int argc, char *argv[])
{
	loadSudokuFromTxtTest();

	return system("pause");
}
