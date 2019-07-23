#pragma once
#include "List.h"
#include "Node.h"
#include "Path.h"
#include "Renderer2D.h"
#include "Settings.h"
#include <sstream>
#include <string>
#include "Vector2.h"

class Grid
{
public:
	Grid();
	~Grid();

	void Draw(aie::Renderer2D* renderer);
	List<Node<Vector2>*>* Nodes() { return &_nodes; }
	void ShowPath(Path* path);
	void ClearPath();
	std::string ToString();

private:
	List<Node<Vector2>*> _nodes;
	Path* _path;

	void populateNodes();

	// This is used for ToString() method, so we can see the type
	// of the node instead of just a number
	string castNodeTypeToString(NodeType nodeType);
};

