#pragma once
#include "Sudoku.h"
#include "PossibleMove.h"
#include <list>

class TabuSearch
{
private:
	const unsigned int maxTabuListSize;
	const unsigned int maxIterations;
	std::list<PossibleMove> tabuList;

public:
	unsigned int iterationsCount = 0;
	 
	TabuSearch(unsigned int maxTabuListSize, unsigned int maxIterations);
	~TabuSearch();

	Sudoku sudokuSolver(const Sudoku& inputSudoku);

	bool isMoveOnTabuList(const PossibleMove& move);
};

