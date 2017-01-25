#pragma once

class Node		// Class representing a single field on the sudoku map
{

private:
	unsigned int value;		// Field value(1-9)
	bool startingNode;		// Is this field a starting field (so it can't be changed)


public:
	Node();
	Node(unsigned int value, bool startingNode);
	~Node();
};

