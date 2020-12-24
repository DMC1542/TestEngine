#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class TextElement
{
public:
	TextElement();
	bool checkForClick(Vector2i mousePos);
	void addLetter(Uint32 unicodeValue);
	void removeLetter();
	void update();
	void draw(RenderWindow& window);
	void setCharCap(int num);
	void setFocused(bool focused);
	void setPrefix(std::string text);
	void setLocation(Vector2f loc);
	void setIntLock(bool lock);
	void toggleBackgroundDisplay();
	std::string getText();

private: 
	Font font;
	Text textPrefix, textBody;
	Vector2f location;
	RectangleShape inputRect, backgroundRect;
	int charCap;
	bool isFocused, intLock, displayBackground;
};