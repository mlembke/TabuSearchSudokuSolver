#include "Sudoku.h"

#include <vector>

Sudoku::Sudoku()
{
}


Sudoku::~Sudoku()
{
}

bool Sudoku::swap(unsigned int blockNo, unsigned int x, unsigned int y)
{
	return false;
}

void Sudoku::fillHolesRandomly()
{
	for (unsigned int blockNo = 0; blockNo < 9; ++blockNo)
	{
		std::vector<unsigned int> valuesToInput{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		for (unsigned int fieldNo = 0; fieldNo < 9; ++fieldNo)
		{

		}


	}
}