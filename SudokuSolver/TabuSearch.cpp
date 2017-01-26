#include "TabuSearch.h"
#include "Sudoku.h"


TabuSearch::TabuSearch(unsigned int tabuListSize) : maxTabuListSize(maxTabuListSize)
{
}


TabuSearch::~TabuSearch()
{
}

Sudoku TabuSearch::sudokuSolver(const Sudoku& inputSudoku)
{
	Sudoku currentSolution = inputSudoku;
	currentSolution.fillHolesRandomly();
	Sudoku bestSolution = currentSolution;
	int iter = 0;
	int MAX_ITER_COUNT = 100;
	
	while(iter < MAX_ITER_COUNT || bestSolution.getNumberOfCollisions() == 0)
	{
		Sudoku bestCandidateSolution;
		PossibleMove bestCandidateMove;
		auto currentSolutionNeighbourhood = currentSolution.getNeighbourhood();
		for (auto candidate : currentSolutionNeighbourhood)
		{
			PossibleMove candidateMove = candidate.first;
			Sudoku candidateSolution = candidate.second;
			if (!isMoveOnTabuList(candidateMove) &&
				candidateSolution.getNumberOfCollisions() < bestCandidateSolution.getNumberOfCollisions())
			{
				bestCandidateSolution = candidateSolution;
				bestCandidateMove = candidateMove;
			}
		}

		if (bestCandidateSolution.getNumberOfCollisions() < bestSolution.getNumberOfCollisions())
		{
			bestSolution = bestCandidateSolution;
		}
		currentSolution = bestCandidateSolution;
		tabuList.push_front(bestCandidateMove);
		if (tabuList.size() > maxTabuListSize)
		{
			tabuList.pop_back();
		}
	}

	return bestSolution;
}

bool TabuSearch::isMoveOnTabuList(const PossibleMove& move)
{
	for (auto& tabuMove : tabuList)
	{
		if (move == tabuMove)
			return true;
	}
	return false;
}