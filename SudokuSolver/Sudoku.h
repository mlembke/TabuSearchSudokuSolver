#pragma once
#include "Node.h"
#include "PossibleMove.h"

#include <utility>
#include <string>
#include <vector>

class Sudoku // Class representing the sudoku map
{
	class Proxy
	{
	public:
		explicit Proxy(Node* mapColumn) : mapColumn(mapColumn)
		{
		}

		Node& operator[](int index) const
		{
			return mapColumn[index];
		}

	private:
		Node* mapColumn;
	};

public:
	static const unsigned BOXSIZE = 3;
	static constexpr unsigned nCols = BOXSIZE * BOXSIZE;
	static constexpr unsigned nRows = BOXSIZE * BOXSIZE;

private:
	Node map[nCols][nRows];

public:
	Sudoku();
	~Sudoku();
	
	bool swap(PossibleMove possibleMove);

	std::pair<unsigned int, unsigned int> getMapCoords(unsigned int blockNo, unsigned int fieldNo);

	std::vector<Node*> getBlockNodes(unsigned int blockNo);

	void fillHolesRandomly();

	bool loadFromTxt(std::string fileName);

	std::vector<std::pair<PossibleMove, Sudoku>> getNeighbourhood();

	bool isMoveLegal(PossibleMove possibleMove);

	void print(std::ostream& os) const;

	Proxy operator[](int index);

	unsigned getNumberOfCollisions() const;

	friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

