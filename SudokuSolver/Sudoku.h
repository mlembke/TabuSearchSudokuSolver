#pragma once
#include "Node.h"
#include <utility>

class Sudoku		// Class representing the sudoku map
{
private:
	Node map[9][9];

public:
	Sudoku();
	~Sudoku();

	bool swap(unsigned int blockNo, unsigned int x, unsigned int y);


	void fillHolesRandomly();	

};

