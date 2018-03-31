#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include "text.h"

class button : public text
{
public:
	button();
	button(std::string text, sf::Vector2f position, style_text style);
	bool update();
	void set_position(sf::Vector2f new_position);

private:
	sf::FloatRect button_hitbox_;
};

#endif