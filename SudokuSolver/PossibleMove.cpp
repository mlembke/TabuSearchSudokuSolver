#include "PossibleMove.h"



PossibleMove::PossibleMove()
{
}

PossibleMove::PossibleMove(unsigned int blockNo, unsigned int node1idx, unsigned int node2idx) : blockNo(blockNo), node1idx(node1idx), node2idx(node2idx)
{
}


PossibleMove::~PossibleMove()
{
}

bool PossibleMove::operator==(const PossibleMove& rhs) const
{
	return !(*this != rhs);
}

bool PossibleMove::operator!=(const PossibleMove& rhs) const
{
	return blockNo != rhs.blockNo || node1idx != rhs.node1idx || node2idx != rhs.node2idx;
}