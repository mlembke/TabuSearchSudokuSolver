#include "Sudoku.h"

#include <vector>

#include <fstream>
#include <iostream>

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

bool Sudoku::loadFromTxt(std::string fileName)
{
	std::ifstream file(fileName);

	if(file.is_open())
	{
		std::string cell;
		unsigned i = 0;
		unsigned j = 0;
		while(file >> cell)
		{
			if(cell != ".")
			{
				map[i][j] = Node(std::stoi(cell), true);
			}
			i = (i + 1) % nCols;
			j = i == 0 ? j + 1 : j;
		}
	}

	return true;
}

