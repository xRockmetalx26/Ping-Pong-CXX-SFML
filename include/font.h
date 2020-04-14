#ifndef FONT_H
#define FONT_H

#include <SFML/Graphics/Font.hpp>
#include <iostream>

using namespace std;

class Font
{
public:

	//------------ BEGIN PUBLIC ------------//

	Font();
	Font(Font const &original) = delete;
	Font &operator = (Font const &original) = delete;
	virtual ~Font();

	bool const		setFont(string fontPath) { return font.loadFromFile(fontPath); }
	sf::Font const	&getFont() { return font; }

	//------------ END PUBLIC ------------//

private:

	//------------ BEGIN PRIVATE ------------//

	static sf::Font	font;
	static uint8_t	numberInstances;

	//------------ END PRIVATE ------------//
};

#endif	//FONT_H