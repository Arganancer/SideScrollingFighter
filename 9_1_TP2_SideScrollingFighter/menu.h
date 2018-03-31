#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "menu_factory.h"

class menu
{
public:
	virtual ~menu() = default;
	virtual void draw(sf::RenderWindow& main_win);
	virtual menu_factory::menu_factory::type_menu update();
};

#endif