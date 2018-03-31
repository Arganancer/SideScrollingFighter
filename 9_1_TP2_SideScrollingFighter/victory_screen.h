#ifndef VICTORY_SCREEN_H
#define OPTIONS_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class victory_screen : public menu
{
public:


	~victory_screen();
	explicit victory_screen();	

	/// <summary>
	/// Draws the specified main win.
	/// </summary>
	/// <param name="main_win">The main win.</param>
	
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
	std::string score_str_;
	text title_;
	text score_;
	button save_score_;
	button back_;
};

#endif