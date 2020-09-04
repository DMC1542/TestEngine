#include "TextElement.h"
#include <iostream>

TextElement::TextElement()
{
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	text.setFont(font);
	text.setString("No text given.");
	text.setPosition(location);
}

bool TextElement::checkForClick(Vector2i mousePos)
{
	if (text.getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void TextElement::addLetter(Uint32 unicodeValue)
{
	std::cout << static_cast<char>(unicodeValue) << std::endl;
	std::cout << unicodeValue << std::endl;

	//Checking to see if it is within the ascii range
	if (unicodeValue < 128)
	{
		text.setString(text.getString() + static_cast<char>(unicodeValue));
	}
	else
	{
		//dont add it, its weird
	}
}

void TextElement::removeLetter()
{
	//An abstract way of setting the string to itself minus one character,
	//or its length - 1
	text.setString(text.getString().substring(0, text.getString().getSize() - 1));
}

void TextElement::update()
{
	text.setPosition(location);
}