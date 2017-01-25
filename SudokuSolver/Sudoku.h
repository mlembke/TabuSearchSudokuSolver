#pragma once
#include "Node.h"

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

		explicit Proxy(const Proxy&) = delete;

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

	bool swap(unsigned int blockNo, unsigned int x, unsigned int y);

	std::pair<unsigned int, unsigned int> getMapCoords(unsigned int blockNo, unsigned int fieldNo);

	std::vector<Node> getBlockNodes(unsigned int blockNo);
	void fillHolesRandomly();

	bool loadFromTxt(std::string fileName);

	void print(std::ostream& os) const;

	Proxy operator[](int index);

	friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
};

