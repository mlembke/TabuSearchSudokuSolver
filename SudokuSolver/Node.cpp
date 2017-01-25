#include "Node.h"

Node::Node() : startingNode(false)
{
}

Node::Node(unsigned int value, bool startingNode) : value(value), startingNode(true)
{
}


Node::~Node()
{
}
