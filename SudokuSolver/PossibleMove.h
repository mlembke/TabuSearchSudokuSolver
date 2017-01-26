#pragma once

class PossibleMove		// Class representing possible moves done by Tabu search algorithm
{
public:
	unsigned int blockNo;
	unsigned int node1idx;
	unsigned int node2idx;

	PossibleMove();
	PossibleMove(unsigned int blockNo, unsigned int node1idx, unsigned int node2idx);
	~PossibleMove();

	bool PossibleMove::operator==(const PossibleMove& rhs) const;

	bool PossibleMove::operator!=(const PossibleMove& rhs) const;
};