#include <font.h>
#include <iostream>

using namespace std;

sf::Font Font::font{};
uint8_t Font::numberInstances = 0;

Font::Font() {
	if(numberInstances++ == 0)
		cout << "OK Font()." << endl;
}

Font::~Font() {
	if(numberInstances-- == 1)
		cout << "OK ~Font()." << endl;
}