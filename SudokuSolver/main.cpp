#include <iostream>
#include <fstream>
#include <sstream>

#include "Sudoku.h"
#include "PossibleMove.h"
#include "TabuSearch.h"


void loadSudokuFromTxtTest()
{
	const std::string fileName = "Data/sudoku.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);
	std::cout << sudoku << "\n";
	std::cout << sudoku.getNumberOfCollisions() << "\n";

}

void getSudokuNeighbourhoodTest()
{
	std::ofstream file("Data/neighbours.txt");
	const std::string fileName = "Data/sudoku.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);
	sudoku.fillHolesRandomly();
	std::cout << sudoku << "\n\n";
	auto sudokuNeighbourHood = sudoku.getNeighbourhood();
	for(auto pair : sudokuNeighbourHood)
	{
		PossibleMove move = pair.first;
		Sudoku neighbour = pair.second;

		file << "Move: " << move.blockNo << " " << move.node1idx << " " << move.node2idx << "\n";
		file << neighbour << std::endl;
	}
}

void singleSwapTest()
{
	const std::string fileName = "Data/sudoku.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);
	sudoku.fillHolesRandomly();
	std::cout << sudoku << "\n\n";
	PossibleMove move(0, 0, 1);
	sudoku.swap(move);
	std::cout << sudoku << "\n\n";
}

void tabuSearchTest()
{
	TabuSearch tabuSearch(10, 1000);
	const std::string fileName = "Data/sudoku_65_0.txt";
	Sudoku sudoku;
	sudoku.loadFromTxt(fileName);
	sudoku.fillHolesRandomly();
	Sudoku resultSudoku = tabuSearch.sudokuSolver(sudoku);
	std::cout << "Solution found after " << tabuSearch.iterationsCount << " iterations (collisions: " << resultSudoku.getNumberOfCollisions() << ").\n";
	std::cout << resultSudoku;
}

void multipleSudokusTabuSearchTest()
{
	TabuSearch tabuSearch(10, 1000);
	std::vector<std::pair<unsigned int, unsigned int>> results;
	for(unsigned int revealedFieldsCount = 20; revealedFieldsCount < 76; revealedFieldsCount += 5)
	{
		for(unsigned int sudokuNo = 0; sudokuNo < 10; ++sudokuNo)
		{
			Sudoku sudoku;
			std::ostringstream stringStream;
			stringStream << "Data/sudoku_" << revealedFieldsCount << "_" << sudokuNo << ".txt";
			sudoku.loadFromTxt(stringStream.str());
			sudoku.fillHolesRandomly();
			Sudoku resultSudoku = tabuSearch.sudokuSolver(sudoku);
			results.push_back(std::make_pair(tabuSearch.iterationsCount, revealedFieldsCount));
		}
	}
	std::ofstream resultOutputFile("Data/multiple_sudokus_test_result.txt");
	for(auto result : results)
	{
		resultOutputFile << result.first << " " << result.second << "\n";
	}
}

int main(int argc, char *argv[])
{
	multipleSudokusTabuSearchTest();

	system("pause");
	return 0;
}
