#include <iostream>
#include <game.h>

int main() {

	Game::createInstance();

	if(Game::getInstance()->init())
		Game::getInstance()->run();

	delete Game::getInstance();

	return EXIT_SUCCESS;
}