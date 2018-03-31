#ifndef OPTIONS_H
#define OPTIONS_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class options : public menu
{
public:
	~options();
	options();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;
private :
	text title_;
	button sound_;
	button back_;
};

#endif
