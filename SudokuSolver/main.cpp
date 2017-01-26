#include <iostream>
#include <fstream>

#include "Sudoku.h"
#include "PossibleMove.h"


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

int main(int argc, char *argv[])
{
	getSudokuNeighbourhoodTest();
	loadSudokuFromTxtTest();

	system("pause");
	return 0;
}
