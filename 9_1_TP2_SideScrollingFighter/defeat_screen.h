#ifndef DEFEAT_SCREEN_H
#define DEFEAT_SCREEN_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class defeat_screen: public menu
{
public:
	~defeat_screen();
	defeat_screen();	
	/// <summary>
	/// Draws the specified main win.
	/// </summary>
	/// <param name="main_win">The main win.</param>
	void draw(sf::RenderWindow& main_win) override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <returns></returns>
	menu_factory::menu_factory::type_menu update() override;
private:
	text title_;
	button back_;
};

#endif
