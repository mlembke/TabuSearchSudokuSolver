#pragma once

class PossibleMove		// Class representing possible moves done by Tabu search algorithm
{
private:
	unsigned int blockNo;
	unsigned int x;
	unsigned int y;

public:
	PossibleMove();
	~PossibleMove();
};

