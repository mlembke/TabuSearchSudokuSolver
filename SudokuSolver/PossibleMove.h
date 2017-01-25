#pragma once

class PossibleMove		// Class representing possible moves done by Tabu search algorithm
{
public:
	unsigned int blockNo;
	unsigned int node1idx;
	unsigned int node2idx;

	PossibleMove(unsigned int blockNo, unsigned int node1idx, unsigned int node2idx);
	~PossibleMove();
};