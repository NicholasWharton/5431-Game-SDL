#pragma once
#include "Game.h"

class Map {

public:
	Map();
	~Map();

	void LoadMap(int arr[32][128]);
	void DrawMap();

private:
	SDL_Rect src;
	SDL_Rect dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[32][128];
};