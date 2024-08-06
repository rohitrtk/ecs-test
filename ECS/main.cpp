#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <chrono>

#include "Game.h"
#include "GameObject.h"
#include "Tile.h"
#include "Player.h"
#include "MapReader.h"

#include <vector>

Game& game = Game::getInstance();

int main(int argc, char** argv) {
	printf("Starting game...\n");

	MapReader mapReader;
	mapReader.parse("res/mapdata.txt");
	mapReader.print();

	SDL_Texture* tilesheet = IMG_LoadTexture(game.getRenderer(), "res/tiles.png");
	auto& metaData = mapReader.getMetaData();
	auto& tileData = mapReader.getTileData();
	auto width = metaData.at("Width");
	std::vector<Tile> tiles;

	for (auto i = 0; i < tileData.size(); i++) {
		int y = i / width;
		int x = i % width;

		tiles.push_back({
			tilesheet,
			x * 32.0f,
			y * 32.0f,
			tileData[i]
		});
	}

	Player player;

	auto stop = std::chrono::high_resolution_clock::now();

	game.getGameObjectManager().start();

	while (game.isRunning()) {
		auto start = std::chrono::high_resolution_clock::now();
		float deltaTime = (std::chrono::duration_cast<std::chrono::nanoseconds>(start - stop)).count() / 1000000000.0;
		stop = std::chrono::high_resolution_clock::now();

		float augmentedDeltaTime = deltaTime;
		if (augmentedDeltaTime > 1.0f / 10) {
			augmentedDeltaTime = 1.0f / 10;
		}

		game.readInput();
		game.getGameObjectManager().update(augmentedDeltaTime);
		game.update(augmentedDeltaTime);
		game.render();
	}

	return EXIT_SUCCESS;
}