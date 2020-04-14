#ifndef GAME_H
#define GAME_H

#include <font.h>
#include <disk.h>
#include <paddle.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <vector>

using namespace sf;

class Game
{
public:

	//------------ BEGIN PUBLIC ------------//

	Game (Game const &original) = delete;
	Game &operator = (Game const &original) = delete;
	virtual ~Game();

	static Game *createInstance();							//CREATE INSTANCE
	static Game *getInstance();								//GETTER INSTANCE

	bool const init();
	bool const isColliding(Paddle &player, Disk &disk) const;

	void run();
	void handleEvents(Event &e);
	void update();
	void render();
	

	//------------ END PUBLIC ------------//

private:

	//------------ BEGIN PRIVATE ------------//

	static Game *instance;	//UNIQUE INSTANCE

	RenderWindow *renderWindow;
	Image iconWindow;
	SoundBuffer soundBuffer;
	Sound sound;
	::Font font;
	Text pauseSprite;
	Text pressSpaceSprite;
	bool pause;
	Disk disk;
	Paddle player1;
	Paddle player2;
	
	vector<Drawable*> drawables;

	Game();

	//------------ BEGIN PRIVATE ------------//
};

#endif	//GAME_H