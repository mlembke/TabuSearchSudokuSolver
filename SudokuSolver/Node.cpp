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
