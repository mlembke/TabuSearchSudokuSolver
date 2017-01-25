#include <iostream>
#include <string>

#include "Sudoku.h"

void loadSudokuFromTxtTest()
{
	const std::string fileName = "Data/sudoku.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);

}

int main(int argc, char *argv[])
{
	loadSudokuFromTxtTest();

	return 0;
}
