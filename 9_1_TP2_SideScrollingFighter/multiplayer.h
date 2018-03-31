#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class multiplayer : public menu
{
public:
	~multiplayer();
	multiplayer();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private:
	text title_;
	button versus_;
	button coop_;
	button back_;
};

#endif
