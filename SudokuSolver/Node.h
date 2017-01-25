#pragma once

class Node		// Class representing a single field on the sudoku map
{

public:
	unsigned int value;		// Field value(1-9)
	bool startingNode;		// Is this field a starting field (so it can't be changed)


public:
	Node();
	Node(unsigned int value, bool startingNode);
	~Node();

	unsigned int getValue() { return value; }
	void setValue(unsigned int newValue) { value = newValue; }
	unsigned int isStartingNode() { return startingNode; }
};

