#include "Grid.h"

Grid::Grid()
{
	populateNodes();
	_path = nullptr;
}

Grid::~Grid()
{
	for (int i = 0; i < _nodes.Count(); i++)
	{
		for (int ii = 0; ii < _nodes[i]->Neighbors.Count(); ii++)
			delete _nodes[i]->Neighbors[ii];

		delete _nodes[i];
	}
}

void Grid::Draw(aie::Renderer2D * renderer)
{
	for (int i = 0; i < _nodes.Count(); i++)
	{
		int color = _nodes[i]->Type == NodeType::Normal ? 0xa9d6c6ff : 0xb39e4fff;

		if (_path)
			if (_path->Corners.HasValue(_nodes[i]->Value))
				color = 0x333333ff;

		renderer->SetRenderColour(color);
		renderer->DrawBox(_nodes[i]->Value.x + WindowDisplayOffset * 2, _nodes[i]->Value.y + WindowDisplayOffset, GRID_CELL_SIZE - 1, GRID_CELL_SIZE - 1);
	}
}

void Grid::ShowPath(Path* path)
{
	_path = path;
}

void Grid::ClearPath()
{
	_path = nullptr;
}

std::string Grid::ToString()
{
	ostringstream result;

	for (int i = 0; i < _nodes.Count(); i++)
	{
		auto node = _nodes[i];
		result << "ID: " << node->Id << " Type: " << node->Type << " " << "[x: " << node->Value.x << " " << "y: " << node->Value.y << "]" << endl;
		result << "Neighbors:" << endl;
		for (int ii = 0; ii < node->Neighbors.Count(); ii++)
			result << "\tID: " << node->Neighbors[ii]->Node->Id << " cost: " << node->Neighbors[ii]->Cost << endl;
		result << endl;
	}

	return result.str();
}

// It creates all the nodes, then finds their neighbors, and finally
// set the cost for each neighbor
void Grid::populateNodes()
{
	// setup initial cells
	for (int y = 0; y < GRID_HEIGHT; y++)
		for (int x = 0; x < GRID_WIDTH; x++)
		{
			Node<Vector2>* node = new Node<Vector2>();
			node->Id = std::to_string(x) + "_" + std::to_string(y);
			node->Value = Vector2(x * (float)GRID_CELL_SIZE, y * (float)GRID_CELL_SIZE);

			_nodes.PushBack(node);
		}

	// 1. setup neighbors for each cell (and walls)
	for (int i = 0; i < _nodes.Count(); i++)
	{
		// 1.1 south wall
		if (i >= 0 && i < GRID_WIDTH)
		{
			_nodes[i]->Type = NodeType::Wall;

			// [ ][ ][ ]
			// [ ][ ][ ]
			// [x][ ][ ]
			if (i == 0)
			{
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH], 0 }); // N
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH + 1], 0 }); // NE
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + 1], 0 }); // E
			}

			// [ ][ ][ ]
			// [ ][ ][ ]
			// [ ][ ][x]
			else if (i == GRID_WIDTH - 1)
			{
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - 1], 0 }); // W
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH - 1], 0 }); // NW
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH], 0 }); // N
			}

			// [ ][ ][ ]
			// [ ][ ][ ]
			// [ ][x][ ]
			else
			{
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - 1], 0 }); // W
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH - 1], 0 }); // NW
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH], 0 }); // N
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH + 1], 0 }); // NE
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + 1], 0 }); // E
			}
		}

		// 1.2 north wall
		else if (i >= GRID_WIDTH * (GRID_HEIGHT - 1) && i < GRID_WIDTH * GRID_HEIGHT)
		{
			_nodes[i]->Type = NodeType::Wall;

			// [x][ ][ ]
			// [ ][ ][ ]
			// [ ][ ][ ]
			if (i == GRID_WIDTH * (GRID_HEIGHT - 1))
			{
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + 1], 0 }); // E
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) + 1], 0 }); // SE
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - GRID_WIDTH], 0 }); // S
			}

			// [ ][ ][x]
			// [ ][ ][ ]
			// [ ][ ][ ]
			else if (i == (GRID_WIDTH * GRID_HEIGHT) - 1)
			{
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - 1], 0 }); // W
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - GRID_WIDTH], 0 }); // S
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) - 1], 0 }); // SW
			}

			// [ ][x][ ]
			// [ ][ ][ ]
			// [ ][ ][ ]
			else
			{
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - 1], 0 }); // W
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + 1], 0 }); // E
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) + 1], 0 }); // SE
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - GRID_WIDTH], 0 }); // S
				_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) - 1], 0 }); // SW
			}
		}

		// 1.3 west wall
		else if (i >= GRID_WIDTH && i < GRID_WIDTH * (GRID_HEIGHT - 1) && i % GRID_WIDTH == 0)
		{
			_nodes[i]->Type = NodeType::Wall;

			// [ ][ ][ ]
			// [x][ ][ ]
			// [ ][ ][ ]
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH], 0 }); // N
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH + 1], 0 }); // NE
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + 1], 0 }); // E
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) + 1], 0 }); // SE
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - GRID_WIDTH], 0 }); // S
		}

		// 1.4 east wall
		else if (i >= (GRID_WIDTH * 2) - 1 && i < (GRID_WIDTH * GRID_HEIGHT) - 1 && (i + 1) % GRID_WIDTH == 0)
		{
			_nodes[i]->Type = NodeType::Wall;

			// [ ][ ][ ]
			// [ ][ ][x]
			// [ ][ ][ ]
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH], 0 }); // N
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - GRID_WIDTH], 0 }); // S
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) - 1], 0 }); // SW
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - 1], 0 }); // W
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH - 1], 0 }); // NW
		}

		// 1.5 inside cells
		else
		{
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - 1], 0 }); // W
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH - 1], 0 }); // NW
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH], 0 }); // N
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + GRID_WIDTH + 1], 0 }); // NE
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i + 1], 0 }); // E
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) + 1], 0 }); // SE
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[i - GRID_WIDTH], 0 }); // S
			_nodes[i]->Neighbors.PushBack(new NodeNeighbor<Vector2>{ _nodes[(i - GRID_WIDTH) - 1], 0 }); // SW
		}
	}

	// 3. add obsticle
	for (int i = GRID_WIDTH * 3 + 2; i < GRID_WIDTH * 3 + 10; i++)
		_nodes[i]->Type = NodeType::Wall;

	// 2. setup neighbors costs for each cell
	for (int i = 0; i < _nodes.Count(); i++)
	{
		Node<Vector2>* node = _nodes[i];
		for (int ii = 0; ii < node->Neighbors.Count(); ii++)
		{
			Node<Vector2>* neighborNode = node->Neighbors[ii]->Node;
			int magnitude = (int)((neighborNode->Value - node->Value).magnitude());
			node->Neighbors[ii]->Cost = magnitude;
		}
	}
}
