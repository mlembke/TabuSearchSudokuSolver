#pragma once
#include "Sudoku.h"
#include "PossibleMove.h"
#include <list>

class TabuSearch
{
private:
	const unsigned int maxTabuListSize;
	std::list<PossibleMove> tabuList;

public:
	TabuSearch(unsigned int maxTabuListSize);
	~TabuSearch();

	Sudoku sudokuSolver(const Sudoku& inputSudoku);

	bool TabuSearch::isMoveOnTabuList(const PossibleMove& move);
};

