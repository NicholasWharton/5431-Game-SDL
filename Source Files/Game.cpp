#include "Game.h"
#include "TextureManager.h"
#include "map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
//create entity
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
	
	//Set 1 for full screen mode
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer Created" << std::endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	//Creating Map
	map = new Map();

	//Creating Game Object
/*	tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(150, 150, 32, 32, 2 );
	tile2.addComponent<ColliderComponent>("grass"); */

	player.addComponent<TransformComponent>(100.0f, 100.0f, 64, 64, 1.5 );
	player.addComponent<SpriteComponent>("assets/titan_4.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(32.0f,464.0f, 1984, 16, 1);
	wall.addComponent<SpriteComponent>("assets/lighttile.png");
	wall.addComponent<ColliderComponent>("wall");
}

//Event Handleing Function for Loop
void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	for (auto cc : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	//Add stuff to render
	map->DrawMap();
	manager.draw();

	SDL_RenderPresent(renderer);
}

//Quit Function
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Closed" << std::endl;
}

void Game::AddTile(int id, int x, int y) {

}