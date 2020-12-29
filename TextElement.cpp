#include "TextElement.h"
#include <iostream>
#include "SFML/Graphics.hpp"

TextElement::TextElement(std::string prefix,
	int charCap,
	bool intLock,
	bool toggleBackground,
	bool isEditable,
	Vector2f location)
{
	// This must be loaded first so that the flags can operate correctly. 
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	textPrefix.setFont(font);
	textPrefix.setString(prefix);
	textPrefix.setPosition(location);

	textBody.setFont(font);
	textBody.setString("Empty.");
	textBody.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);

	// Set default location
	this->location = location;

	// Set char cap
	setCharCap(charCap);

	// Set default background
	this->displayBackground = toggleBackground;

	// set default flags
	isFocused = false;
	setIntLock(intLock);

	inputRect.setFillColor(Color(0, 0, 0, 128));
	inputRect.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	inputRect.setSize(sf::Vector2f(textBody.getGlobalBounds().width, 40));

	backgroundRect.setFillColor(Color(0, 0, 0, 128));
	backgroundRect.setPosition(location);
	backgroundRect.setSize(sf::Vector2f(
		textPrefix.getGlobalBounds().width + textBody.getGlobalBounds().width, 40));
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
	String string = textBody.getString();

	if (string.getSize() > 0)
		textBody.setString(string.substring(0, string.getSize() - 1));
}

void TextElement::update()
{
	textBody.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	
	inputRect.setSize(sf::Vector2f(textBody.getGlobalBounds().width, 40));
	inputRect.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);

	backgroundRect.setSize(sf::Vector2f(
		textPrefix.getGlobalBounds().width + textBody.getGlobalBounds().width, 40));
	backgroundRect.setPosition(location);

	if (isFocused)
		textBody.setFillColor(Color::Blue);
	else
		textBody.setFillColor(Color::White);
}

void TextElement::draw(RenderWindow& window)
{
	if (displayBackground)
		window.draw(backgroundRect);
	else
	{
		if (isFocused)
			window.draw(inputRect);
	}

	window.draw(textPrefix);
	window.draw(textBody);
}

void TextElement::setCharCap(int num)
{
	charCap = num;

	if (charCap <= textBody.getString().getSize())
	{
		textBody.setString(textBody.getString().substring(0, charCap));
	}
}

void TextElement::setFocused(bool focused)
{
	isFocused = focused;
}

void TextElement::setPrefix(std::string text)
{
	textPrefix.setString(text);
	inputRect.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
}

void TextElement::setLocation(Vector2f loc)
{
	location = loc;
	textPrefix.setPosition(location);
	textBody.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	inputRect.setPosition(location.x + textPrefix.getGlobalBounds().width, location.y);
	inputRect.setSize(Vector2f(textBody.getGlobalBounds().width, 40));
}

void TextElement::setIntLock(bool lock)
{
	intLock = lock;

	if (intLock == true)
	{
		removeNonIntegers();
	}
}

void TextElement::toggleBackgroundDisplay()
{
	displayBackground = !displayBackground;
}

void TextElement::setBodyText(std::string bodyText)
{
	textBody.setString(bodyText);

	if (intLock)
	{
		removeNonIntegers();
	}

	if (textBody.getString().getSize() >= charCap)
	{
		textBody.setString(textBody.getString().substring(0, charCap));
	}
}

std::string TextElement::getText()
{
	return textBody.getString();
}

void TextElement::removeNonIntegers()
{
	std::string parsedString = "";
	std::string rawString = textBody.getString().toAnsiString();

	for (int i = 0; i < rawString.length(); i++)
	{
		if (isdigit(rawString.at(i)))
		{
			parsedString.push_back(rawString.at(i));
		}
	}

	if (parsedString.length() == 0)
		parsedString.append("0");

	textBody.setString(parsedString);
}

bool TextElement::isCurrentlyFocused()
{
	return isFocused;
}