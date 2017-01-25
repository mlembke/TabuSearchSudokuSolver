#include "Node.h"

Node::Node() : value(0), startingNode(false)
{
}

Node::Node(unsigned int value, bool startingNode) : value(value), startingNode(true)
{
}


Node::~Node()
{
}

void Node::print(std::ostream& os) const
{
	os << value;
}

std::ostream& operator<<(std::ostream &os, const Node& node)
{
	node.print(os);
	return os;
}
