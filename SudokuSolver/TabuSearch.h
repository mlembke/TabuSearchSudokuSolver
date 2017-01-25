#pragma once
#include "Sudoku.h"

class TabuSearch
{
public:
	TabuSearch();
	~TabuSearch();

	Sudoku sudokuSolver(Sudoku inputSudoku);
};

