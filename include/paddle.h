#ifndef PADDLE_H
#define PADDLE_H

#include <font.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Paddle
{
	RectangleShape	sprite;
	::Font			font;
	Text			scoreSprite;
	uint8_t			speed;
	bool			keyDirection;
	uint8_t			score;

	public:

	//------------ BEGIN INTERFAZ ------------//

	void init();

	inline void	addPoint() { scoreSprite.setString(to_string(++score).c_str()); }
	inline void	resetScore() { scoreSprite.setString(to_string(score = 0)); }
	inline void	setKeyDirection(bool const &flag) { keyDirection = flag; }

	inline RectangleShape	&getSprite() { return sprite; }
	inline Text				&getDrawableScore() { return scoreSprite; }
	inline bool const		&keyDirectionIsPressed() { return keyDirection; }
	inline uint8_t const	&getSpeed() { return speed; }

	Paddle();
	virtual ~Paddle();

	//------------ END INTERFAZ ------------//
};

#endif	//PADDLE_H