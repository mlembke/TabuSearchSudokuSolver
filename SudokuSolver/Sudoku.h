#pragma once

class Sudoku		// Class representing the sudoku map
{
private:
	Node map[9][9];

public:
	Sudoku();
	~Sudoku();

	bool swap(unsigned int blockNo, unsigned int x, unsigned int y);

};

