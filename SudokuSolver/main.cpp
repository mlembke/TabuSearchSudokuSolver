#include <iostream>
#include <string>

#include "Sudoku.h"


void loadSudokuFromTxtTest()
{
	const std::string fileName = "Data/sudoku.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);
	std::cout << sudoku << "\n\n";
}

void fillSudokuRandomlyTest()
{
	const std::string fileName = "Data/sudoku.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);
	std::cout << sudoku << "\n\n";
	sudoku.fillHolesRandomly();
	std::cout << sudoku << "\n\n";
}

int main(int argc, char *argv[])
{
	fillSudokuRandomlyTest();

	return system("pause");
}
