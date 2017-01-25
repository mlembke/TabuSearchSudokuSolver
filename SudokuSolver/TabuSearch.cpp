#include "TabuSearch.h"
#include "Sudoku.h"


TabuSearch::TabuSearch()
{
}


TabuSearch::~TabuSearch()
{
}

Sudoku TabuSearch::sudokuSolver(Sudoku inputSudoku)
{
	Sudoku currentSolution = inputSudoku;
	currentSolution.fillHolesRandomly();


	return Sudoku();
}
