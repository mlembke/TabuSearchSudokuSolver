#pragma once
#include "Node.h"

#include <utility>
#include <string>
#include <vector>

class Sudoku		// Class representing the sudoku map
{
public:
	static const unsigned BOXSIZE = 3;
	static constexpr unsigned nCols = BOXSIZE * BOXSIZE;
	static constexpr unsigned nRows = BOXSIZE * BOXSIZE;

private:
	Node map[nCols][nRows];

public:
	Sudoku();
	~Sudoku();

	bool swap(unsigned int blockNo, unsigned int x, unsigned int y);

	std::pair<unsigned int, unsigned int> getMapCoords(unsigned int blockNo, unsigned int fieldNo);

	std::vector<Node> getBlockNodes(unsigned int blockNo);
	void fillHolesRandomly();

	bool loadFromTxt(std::string fileName);

	void print(std::ostream& os) const;

	friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);

};

