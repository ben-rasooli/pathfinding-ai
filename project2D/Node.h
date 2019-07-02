#pragma once
#include <string>
#include "List.h"

using namespace std;

enum NodeType
{
	Normal,
	Wall
};

template <class T>
struct NodeNeighbor;

template <class T>
struct Node
{
	string Id;
	NodeType Type = NodeType::Normal;
	List<NodeNeighbor<T>*> Neighbors;
	T Value;
	Node<T>* Origin;
	int GCost = 0;
	int HCost = 0;
	int FCost() { return GCost + HCost; }
};

template <class T>
struct NodeNeighbor
{
	Node<T>* Node;
	int Cost;
};
