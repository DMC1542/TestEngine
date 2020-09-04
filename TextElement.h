#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

using namespace sf;

class TextElement
{
public:
	Font font;
	Text text;
	Vector2f location;

	TextElement();
	bool checkForClick(Vector2i mousePos);
	void addLetter(Uint32 unicodeValue);
	void removeLetter();
	void update();
};