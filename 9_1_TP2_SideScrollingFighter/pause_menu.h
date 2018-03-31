#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class pause_menu : public menu
{
public:
	~pause_menu();
	pause_menu();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;
private:
	text title_;
	button return_to_game_;
	button options_;
	button return_to_main_menu_;
	button exit_;
};

#endif
