#include "TabuSearch.h"
#include "Sudoku.h"
#include <iostream>


TabuSearch::TabuSearch(unsigned int tabuListSize, unsigned int maxIterations) : maxTabuListSize(maxTabuListSize), maxIterations(maxIterations)
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
	
	while(iterationsCount < maxIterations || bestSolution.getNumberOfCollisions() != 0)
	{
		std::cout << "Starting iter. " << iterationsCount << "\n";
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
		std::cout << "Current solution (collisions): " << currentSolution.getNumberOfCollisions() << "\n";
		std::cout << currentSolution;
		std::cout << "Ending iter. " << iterationsCount << "\n";
		++iterationsCount;
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