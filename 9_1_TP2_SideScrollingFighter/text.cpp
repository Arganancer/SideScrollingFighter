#include "text.h"

sf::Font text::font_bungee_;
sf::Font text::font_consolas_bold_;
sf::Font text::font_consolas_;

text::text()
{
}

bool text::init()
{
	if (!font_bungee_.loadFromFile("Fonts\\Bungee-Regular.ttf"))
	{
		return false;
	}
	if (!font_consolas_bold_.loadFromFile("Fonts\\consolab.ttf"))
	{
		return false;
	}
	if (!font_consolas_.loadFromFile("Fonts\\consola.ttf"))
	{
		return false;
	}
	return true;
}

text::text(std::string text, sf::Vector2f position, style_text style)
{
	text_ = sf::Text();
	text_.setString(text);
	text_.setPosition(position);
	set_text_style(style);
}

void text::draw(sf::RenderWindow& main_win) const
{
	main_win.draw(text_);
}

void text::set_text_style(style_text style)
{
	switch(style)
	{
	case title:
		text_.setFont(font_bungee_);
		color_ = sf::Color(110, 178, 0);
		color_highlight_ = sf::Color(157, 255, 0);
		char_size_ = 26;
		break;
	case normal_plus:
		text_.setFont(font_bungee_);
		color_ = sf::Color(49, 155, 0);
		color_highlight_ = sf::Color(111, 239, 52);
		char_size_ = 22;
		break;
	case normal:
		text_.setFont(font_consolas_);
		color_ = sf::Color(49, 155, 0);
		color_highlight_ = sf::Color(111, 239, 52);
		char_size_ = 20;
		break;
	case placeholder:
		text_.setFont(font_consolas_);
		color_ = sf::Color(25, 90, 0);
		color_highlight_ = sf::Color(25, 90, 0);
		char_size_ = 20;
		break;
	case error:
		text_.setFont(font_consolas_bold_);
		color_ = sf::Color(214, 92, 0);
		color_highlight_ = sf::Color(255, 172, 109);
		char_size_ = 20;
		break;
	}
	text_.setCharacterSize(24);
	text_.setFillColor(color_);
}


void text::set_string(std::string text)
{
	text_.setString(text);
}

sf::String text::get_text_string() const
{
	return text_.getString();
}


int text::get_text_size() const
{
	return text_.getGlobalBounds().width;
}

void text::set_position(sf::Vector2f new_position)
{
	text_.setPosition(new_position);
}
