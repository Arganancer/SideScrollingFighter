#ifndef PLAY_H
#define PLAY_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class play : public menu
{
public:
	play();
	~play();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private :
	text title_;
	button singleplayer_;
	button multiplayer_;
	button back_;
};

#endif
