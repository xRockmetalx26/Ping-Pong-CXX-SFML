#include <game.h>
#include <SFML/Window/Event.hpp>
#include <iostream>

Game *Game::instance = nullptr;	//DEFINITION

Game::Game() : renderWindow(nullptr), pause(false) {
	std::cout << "OK Game()." << std::endl;
}

bool const Game::init()
{
	//------------ WINDOW ------------//

	renderWindow = new RenderWindow(VideoMode(720, 480), "Pong xRockmetalx", Style::Close | Style::Titlebar);
	renderWindow->setVerticalSyncEnabled(true);

	if(!renderWindow) {
		std::cout << "ERROR RenderWindow()." << std::endl;
		return false;
	}
	
	std::cout << "OK RenderWindow()." << std::endl;

	//------------ ICON WINDOW ------------//

	if(!iconWindow.loadFromFile("assets/iconWindow.png"))
	{
		std::cout << "ERROR loadFromFile(\"assets/iconWindow.png\")." << std::endl;
		return false;
	}

	std::cout << "OK loadFromFile(\"assets/iconWindow.png\")." << std::endl;
	renderWindow->setIcon(128, 128, iconWindow.getPixelsPtr());

	//------------ SOUND ------------//

	if(!soundBuffer.loadFromFile("assets/pongSound.wav")) {
		std::cout << "ERROR loadFromFile(\"assets/pongSound.wav\")." << std::endl;
		return false;
	}
	
	std::cout << "OK loadFromFile(\"assets/pongSound.wav\")." << std::endl;
	sound.setBuffer(soundBuffer);

	//------------ TEXT ------------//

	if(!font.setFont("res/font.ttf")) {
		cerr << "ERROR setFont(\"res/font.ttf\")." << endl;
		exit(EXIT_FAILURE);
	}

	cout << "OK setFont(\"res/font.ttf\")." << endl;
	pauseSprite.setFont(font.getFont());
	pauseSprite.setString("PAUSE");
	pauseSprite.setPosition( 320, 200);
	pauseSprite.setCharacterSize(16);

	pressSpaceSprite.setFont(font.getFont());
	pressSpaceSprite.setString("PRESS SPACE");
	pressSpaceSprite.setPosition( 272, 200);
	pressSpaceSprite.setCharacterSize(16);

	//------------ DISK ------------//

	disk.resetDisk();

	//------------ PLAYER1 ------------//

	player1.init();
	player1.getSprite().setPosition(0, 480 / 2 - 40);
	player1.getDrawableScore().setPosition(100, 60);

	//------------ PLAYER2 ------------//

	player2.init();
	player2.getSprite().setPosition(720 - 10, 480 / 2 - 40);
	player2.getDrawableScore().setPosition(720 - 100 - 20, 60);

	//------------ ADD DRAWABLES ------------//

	drawables.push_back(&disk.getSprite());
	drawables.push_back(&player1.getSprite());
	drawables.push_back(&player2.getSprite());
	drawables.push_back(&player1.getDrawableScore());
	drawables.push_back(&player2.getDrawableScore());

	return true;
}

void Game::run()
{
	while(renderWindow->isOpen())
	{
		Event e;

		handleEvents(e);

		if(!pause)
			update();

		render();
	}
}

void Game::handleEvents(Event &e)
{
	while(renderWindow->pollEvent(e))
	{
		if(e.type == Event::Closed)
			renderWindow->close();

		if(e.type == Event::KeyPressed && e.key.code == Keyboard::Escape && disk.isActive())
			pause = !pause;

		if(!pause && !disk.isActive())
			if(e.type == Event::KeyPressed && e.key.code == Keyboard::Space)
				disk.activateDisk();
	}
}

void Game::update()
{
	if(Keyboard::isKeyPressed(Keyboard::S))
		if(player1.getSprite().getPosition().y + player1.getSprite().getLocalBounds().height < 480)
			player1.getSprite().move(0, +player1.getSpeed());

	if(Keyboard::isKeyPressed(Keyboard::W))
		if(player1.getSprite().getPosition().y > 0)
			player1.getSprite().move(0, -player1.getSpeed());

	if(Keyboard::isKeyPressed(Keyboard::Down))
		if(player2.getSprite().getPosition().y + player2.getSprite().getLocalBounds().height < 480)
			player2.getSprite().move(0, +player2.getSpeed());
	
	if(Keyboard::isKeyPressed(Keyboard::Up))
		if(player2.getSprite().getPosition().y > 0)
			player2.getSprite().move(0, -player2.getSpeed());
	
	if(isColliding(player1, disk)) {
		sound.play();
		disk.switchDirectionX();
		disk.getSprite().setPosition(10 /*Paddle*/, disk.getSprite().getPosition().y);
	}
	else if(isColliding(player2, disk)) {
		sound.play();
		disk.switchDirectionX();
		disk.getSprite().setPosition(720 - 10 /*Paddle*/- 20 /*Disk*/, disk.getSprite().getPosition().y);
	}

	if(disk.getSprite().getPosition().y <= 0
		|| disk.getSprite().getPosition().y + disk.getSprite().getRadius() * 2 >= 480
	)
		disk.switchDirectionY();

	if(disk.getSprite().getPosition().x + disk.getSprite().getRadius() * 2 <= 0) {
		player2.addPoint();
		disk.resetDisk();
	}
	else if(disk.getSprite().getPosition().x >= 720) {
		player1.addPoint();
		disk.resetDisk();
	}

	if(disk.isActive())
		disk.move();
}

void Game::render()
{
	renderWindow->clear(Color::Black);

	for(auto drawable : drawables)
		renderWindow->draw(*drawable);

	if(pause)
		renderWindow->draw(pauseSprite);

	else if(!disk.isActive())
		renderWindow->draw(pressSpaceSprite);

	renderWindow->display();
}

bool const Game::isColliding(Paddle &player, Disk &disk) const {
	if(player.getSprite().getGlobalBounds().intersects(disk.getSprite().getGlobalBounds()))
		return true;

	return false;
}

Game *Game::createInstance()
{
	if(!instance)
		return instance = new Game();

	std::cerr << "ERROR createInstance(), First instance has been created." << std::endl;

	exit(EXIT_FAILURE);
}

Game *Game::getInstance()
{
	if(!instance)
	{
		std::cerr << "ERROR getInstance(), First instance has not been created."
					"First call createInstance() to create an instance." << std::endl;

		exit(EXIT_FAILURE);
	}

	return instance;
}

Game::~Game() 
{
	delete renderWindow;

	std::cout << "OK ~RenderWindow()." << std::endl;
	std::cout << "OK ~Game()." << std::endl;
}