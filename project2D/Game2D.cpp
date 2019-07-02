#include "Application.h"
#include "Font.h"
#include "Game2D.h"
#include "Input.h"
#include <iostream>
#include "Player.h"
#include "Texture.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	_2dRenderer = new aie::Renderer2D();
	_font = new aie::Font("./font/consolas.ttf", 24);

	_grid = new Grid();
	_pathfinder = new Pathfinder(_grid->Nodes());
	_path = _pathfinder->FindPath("1_1", "10_15");
	_grid->ShowPath(_path);
	cout << endl << _grid->ToString();
}

Game2D::~Game2D()
{
	delete _font;
	delete _grid;
	delete _pathfinder;
	delete _path;
	delete _2dRenderer;
}

void Game2D::Update(float deltaTime)
{
	aie::Input* input = aie::Input::GetInstance();

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	_2dRenderer->Begin();

	_grid->Draw(_2dRenderer);

	// Draw some text.
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	_2dRenderer->DrawText2D(_font, fps, 15.0f, windowHeight - 32.0f);
	_2dRenderer->DrawText2D(_font, "Press ESC to quit!", 15.0f, windowHeight - 64.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	_2dRenderer->End();
}
