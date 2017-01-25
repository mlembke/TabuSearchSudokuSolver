#pragma once
#include "Node.h"

#include <utility>
#include <string>

class Sudoku		// Class representing the sudoku map
{
private:
	static const unsigned BOXSIZE = 3;
	static constexpr unsigned nCols = BOXSIZE * BOXSIZE;
	static constexpr unsigned nRows = BOXSIZE * BOXSIZE;

	Node map[nCols][nRows];

public:
	Sudoku();
	~Sudoku();

	bool swap(unsigned int blockNo, unsigned int x, unsigned int y);

	void fillHolesRandomly();

	bool loadFromTxt(std::string fileName);

};

