#include <paddle.h>
#include <iostream>

using namespace std;

Paddle::Paddle() : sprite(Vector2f(10, 80)), score(0), speed(12) {
	cout << "OK Paddle()." << endl;
}

void Paddle::init()
{
	scoreSprite.setFont(font.getFont());
	scoreSprite.setString(to_string(0));
	scoreSprite.setCharacterSize(20);
}

Paddle::~Paddle() {
	std::cout << "OK ~Paddle()." << std::endl;
}