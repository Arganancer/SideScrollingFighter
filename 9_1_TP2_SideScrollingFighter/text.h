#ifndef TEXT_H
#define TEXT_H
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class text
{
public:
	enum style_text
	{
		title,
		normal_plus,
		normal,
		placeholder,
		error,
	};
	// Constructors
	text();
	text(std::string text, sf::Vector2f position, style_text style);

	// Initialiser
	static bool init();

	// Mutators
	void draw(sf::RenderWindow& main_win) const;
	void set_string(std::string text);
	void set_position(sf::Vector2f new_position);

	// Accessors
	sf::String get_text_string() const;
	int get_text_size() const;

protected:
	void set_text_style(style_text style);
	sf::Text text_;
	sf::Color color_;
	sf::Color color_highlight_;
	int char_size_;
	static sf::Font font_bungee_;
	static sf::Font font_consolas_bold_;
	static sf::Font font_consolas_;
};

#endif