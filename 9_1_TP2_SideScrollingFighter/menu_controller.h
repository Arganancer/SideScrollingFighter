#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H
#include "menu_factory.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "game.h"

class menu_controller
{
#pragma region Singleton pattern
public:
	static menu_controller *get_menu_controller();
	static void release();
private:
	menu_controller();
	menu_controller(const menu_controller&);
	void operator=(const menu_controller&);
	static menu_controller *menu_controller_;
#pragma endregion 
public:
	game::game_state update();
	void draw(sf::RenderWindow& main_win) const;

private:
	void change_menu(menu_factory::menu_factory::type_menu new_menu_type);
	void delete_menu();

	menu_factory::menu_factory::type_menu current_menu_type_;
	menu *current_menu_;

	game::game_state current_game_state_;
};
#endif