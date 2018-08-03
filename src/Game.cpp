#include "Game.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Player.h"
#include "Tilemap.h"

Player *player;
Tilemap *tilemap;
SDL_Event Game::event;
SDL_Renderer *Game::renderer = nullptr;

// DEVELOPMENT OPTIONS FOR WINDOW RESOLUTIONS
const int windowWidth = 1024;
const int windowHeight = 576;


Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Failed to initialize SDL" << std::endl;
		SDL_Delay(5000);
	}
	else {
		this->window = SDL_CreateWindow("RPG Development", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
		this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );

		// May have to change this depending on your project layout
		player = new Player("SDL-RPG-Game/assets/playerspritesheet.png");
		tilemap = new Tilemap("SDL-RPG-Game/maps/test.lvl");
		this->isRunning = true;
	}
}

Game::~Game() {
	delete player;
	delete tilemap;
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
}

void Game::processEvents() {
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		isRunning = false;
	}

	// Handle input
	player->handleInput();
	
}

void Game::updateGame() {
	player->update();
}

void Game::renderGame() {
	SDL_RenderClear(this->renderer);
	tilemap->drawMap();
	player->render();
	SDL_RenderPresent(this->renderer);

}