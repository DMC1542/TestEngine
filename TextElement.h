#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class TextElement
{
public:
	TextElement(std::string prefix = "Value: ",
		int charCap = 16,
		bool intLock = false,
		bool toggleBackground = true,
		bool isEditable = true,
		Vector2f location = Vector2f(0, 0));
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
	void setBodyText(std::string bodyText);
	std::string getText();
	bool isCurrentlyFocused();

private: 
	Font font;
	Text textPrefix, textBody;
	Vector2f location;
	RectangleShape inputRect, backgroundRect;
	int charCap;
	bool isFocused, intLock, displayBackground, isEditable;

	void removeNonIntegers();
};