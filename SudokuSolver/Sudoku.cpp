#include "Sudoku.h"

#include <utility>
#include <algorithm>
#include <random>

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

std::pair<unsigned int, unsigned int> Sudoku::getMapCoords(unsigned int blockNo, unsigned int fieldNo)
{
	unsigned int blockX = blockNo % 3;
	unsigned int blockY = blockNo / 3;
	unsigned int fieldX = fieldNo % 3;
	unsigned int fieldY = fieldNo / 3;
	return std::make_pair(blockX * 3 + fieldX, blockY * 3 + fieldY);
}

std::vector<Node> Sudoku::getBlockNodes(unsigned int blockNo)
{
	std::vector<Node> blockNodes;
	unsigned int mapX = (blockNo % 3) * 3;
	unsigned int mapY = (blockNo / 3) * 3;
	for (auto curMapX = mapX; curMapX < mapX + 3; ++curMapX)
	{
		for (auto curMapY = mapY; curMapY < mapY + 3; ++curMapY)
		{
			blockNodes.push_back(map[curMapX][curMapY]);
		}
	}
	return blockNodes;
}

void Sudoku::fillHolesRandomly()
{
	for (unsigned int blockNo = 0; blockNo < 9; ++blockNo)
	{
		std::vector<unsigned int> valuesToInput{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		// Deleting existing values from valuesToInput
		std::vector<Node> blockNodes = getBlockNodes(blockNo);
		for (Node node : blockNodes)
		{
			if (node.isStartingNode())
			{
				valuesToInput.erase(std::remove(valuesToInput.begin(), valuesToInput.end(), node.getValue()), valuesToInput.end());
			}
		}

		// Fill non-starting nodes with the values;
		auto randEngine = std::default_random_engine{};
		std::shuffle(std::begin(valuesToInput), std::end(valuesToInput), randEngine);
		for (Node node : blockNodes)
		{
			if (!node.isStartingNode())
			{
				node.setValue(valuesToInput[valuesToInput.size()-1]);
				valuesToInput.pop_back();
			}
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
			j = (j + 1) % nCols;
			i = j == 0 ? i + 1 : i;
		}
	}

	return true;
}

