#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "menu.h"
#include "button.h"
#include <SFML/Graphics/RenderWindow.hpp>

class main_menu : public menu
{
public:
	~main_menu();
	main_menu();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private:
	text title_;
	button play_;
	button options_;
	button scores_;
	button change_account_;
	button exit_;
};

#endif