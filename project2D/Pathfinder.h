#pragma once
#include "Path.h"
#include "Grid.h"
#include "List.h"
#include "Settings.h"
#include <string>
#include <cmath>

using namespace std;

class Pathfinder
{
public:
	Pathfinder(List<Node<Vector2>*>* nodes);
	~Pathfinder();

	/*------------------------------------------------------
	Returns a path from a GridNode to another one containing
	all the connecting GridNodes in between.

	@param from: origin GridNode
	@param from: destination GridNode
	------------------------------------------------------*/
	Path* FindPath(string from, string to);

private:
	List<Node<Vector2>*>* _nodes;;
	List<Node<Vector2>*> _openSet;
	List<Node<Vector2>*> _closedSet;
	int _diagnalMovementCost;
	int _straightMovementCost;

	int calculateHCost(Node<Vector2>* from, Node<Vector2>* to);
	int findDiagnalMovementCost(Node<Vector2>* node);
	int findStraightMovementCost(Node<Vector2>* node);
};

