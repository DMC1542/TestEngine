#include "TextElement.h"
#include <iostream>
#include "SFML/Graphics.hpp"

TextElement::TextElement()
{
	// Set default location
	location = Vector2f(0, 0);

	// set default flags
	isFocused = false;
	intLock = false;

	font.loadFromFile("fonts/KOMIKAP_.ttf");

	textPrefix.setFont(font);
	textPrefix.setString("Value: ");
	textPrefix.setPosition(location);

	textBody.setFont(font);
	textBody.setString("Empty.");
	textBody.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);

	rect.setFillColor(Color(0, 0, 0, 128));
	rect.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	rect.setSize(sf::Vector2f(textBody.getGlobalBounds().width, 40));

	// Set default char cap
	charCap = 15;
}

bool TextElement::checkForClick(Vector2i mousePos)
{
	if (textBody.getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y)) ||
		textPrefix.getGlobalBounds().contains(Vector2f(mousePos.x, mousePos.y)))
	{
		return true;
	}
	else
		return false;
}

void TextElement::addLetter(Uint32 unicodeValue)
{
	//Checking to see if it is within the ascii range
	if (unicodeValue < 128)
	{
		// Check to see if we reached the char cap
		if (charCap <= textBody.getString().getSize())
		{
			textBody.setString(textBody.getString().substring(0, charCap));
			return;
		}

		// Check for intLock, add letter/number accordingly
		if (intLock && unicodeValue >= 48 && unicodeValue <= 57)
			textBody.setString(textBody.getString() + static_cast<String>(unicodeValue));

		if (!intLock)
			textBody.setString(textBody.getString() + static_cast<String>(unicodeValue));
	}
}

void TextElement::removeLetter()
{
	//A backwards way of setting the string to itself minus one character,
	//or its length - 1
	if (textBody.getString().getSize() > 0)
		textBody.setString(textBody.getString().substring(0, textBody.getString().getSize() - 1));
}

void TextElement::update()
{
	textBody.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	rect.setSize(sf::Vector2f(textBody.getGlobalBounds().width, 40));

	if (isFocused)
	{
		textBody.setFillColor(Color::Blue);
	}
	else
	{
		textBody.setFillColor(Color::White);
	}
}

void TextElement::draw(RenderWindow& window)
{
	if (isFocused)
		window.draw(rect);
	window.draw(textPrefix);
	window.draw(textBody);
}

void TextElement::setCharCap(int num)
{
	charCap = num;
}

void TextElement::setFocused(bool focused)
{
	isFocused = focused;
}

void TextElement::setPrefix(String text)
{
	textPrefix.setString(text);
}

void TextElement::setLocation(Vector2f loc)
{
	location = loc;
	textPrefix.setPosition(location);
	textBody.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	rect.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	rect.setSize(Vector2f(textBody.getGlobalBounds().width, 40));
}

void TextElement::setIntLock(bool lock)
{
	intLock = lock;
}

String TextElement::getText()
{
	return textBody.getString();
}
