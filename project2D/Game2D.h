#pragma once
#include "Game.h"
#include "Grid.h"
#include "Node.h"
#include "Pathfinder.h"
#include "Renderer2D.h"
#include <string> 

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	aie::Renderer2D* _2dRenderer;
	aie::Font* _font;
	Grid* _grid;
	Path* _path;
	Pathfinder* _pathfinder;
};