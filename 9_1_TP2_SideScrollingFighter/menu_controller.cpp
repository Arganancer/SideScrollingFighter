#include "menu_controller.h"
#include "menu.h"
#include "account_controller.h"

menu_controller *menu_controller::menu_controller_;

menu_controller::menu_controller()
{
	current_game_state_ = game::get_current_game_state();
	if (current_game_state_ == game::game_state::main_menu)
	{
		current_menu_type_ = menu_factory::menu_factory::log_in_e;
	}
	else if (current_game_state_ == game::game_state::paused)
	{
		current_menu_type_ = menu_factory::menu_factory::pause_menu_e;
	}
	else if (current_game_state_ == game::game_state::victory_screen)
	{
		current_menu_type_ = menu_factory::menu_factory::victory_screen_e;
	}
	else if (current_game_state_ == game::game_state::defeat_screen)
	{
		current_menu_type_ = menu_factory::menu_factory::defeat_screen_e;
	}
	current_menu_ = menu_factory::menu_factory::create_menu(current_menu_type_);
}

menu_controller* menu_controller::get_menu_controller()
{
	if (!menu_controller_)
		menu_controller_ = new menu_controller;
	return menu_controller_;
}

void menu_controller::release()
{
	if (menu_controller_ != nullptr)
	{
		delete menu_controller_;
		menu_controller_ = nullptr;
	}
}

game::game_state menu_controller::update()
{
	const auto new_menu_type = current_menu_->update();
	// Play Singleplayer mode.
	if (new_menu_type == menu_factory::menu_factory::play_singleplayer_e)
	{
		current_game_state_ = game::game_state::singleplayer;
	}
	// Play COOP mode.
	else if (new_menu_type == menu_factory::menu_factory::play_coop_e)
	{
		current_game_state_ = game::game_state::coop;
	}
	// Play VS mode.
	else if (new_menu_type == menu_factory::menu_factory::play_vs_e)
	{
		current_game_state_ = game::game_state::vs;
	}
	// Exit the game.
	else if (new_menu_type == menu_factory::menu_factory::exit_e)
	{
		current_game_state_ = game::game_state::exiting;
	}
	// Create new account.
	else if (new_menu_type == menu_factory::menu_factory::main_menu_e && current_menu_type_ == menu_factory::menu_factory::create_account_e)
	{
		if (account_controller::create_account(account_controller::get_username_to_evaluate(), account_controller::get_password_to_evaluate()))
		{
			account_controller::log_in(account_controller::get_username_to_evaluate(), account_controller::get_password_to_evaluate());
			current_menu_type_ = new_menu_type;
			change_menu(current_menu_type_);
		}
		account_controller::set_username_to_evaluate("");
		account_controller::set_password_to_evaluate("");
	}
	// Log in.
	else if (new_menu_type == menu_factory::menu_factory::main_menu_e && current_menu_type_ == menu_factory::menu_factory::log_in_e)
	{
		if (account_controller::log_in(account_controller::get_username_to_evaluate(), account_controller::get_password_to_evaluate()))
		{
			current_menu_type_ = new_menu_type;
			change_menu(current_menu_type_);
		}
		account_controller::set_username_to_evaluate("");
		account_controller::set_password_to_evaluate("");
	}
	// If game is paused, return to Pause Menu from the options menu.
	else if (new_menu_type == menu_factory::menu_factory::main_menu_e && 
		current_menu_type_ == menu_factory::menu_factory::options_e)
	{
		current_menu_type_ = menu_factory::menu_factory::pause_menu_e;
		change_menu(current_menu_type_);
	}
	// If returning to the Main Menu from the Paused menu, change the game state to "Main Menu".
	else if (new_menu_type == menu_factory::menu_factory::main_menu_e &&
		current_menu_type_ == menu_factory::menu_factory::pause_menu_e)
	{
		current_game_state_ = game::game_state::main_menu;
		current_menu_type_ = new_menu_type;
		change_menu(current_menu_type_);
	}
	// Transition from one menu to another.
	else if (current_menu_type_ != new_menu_type)
	{
		current_menu_type_ = new_menu_type;
		change_menu(current_menu_type_);
	}
	if (new_menu_type == menu_factory::menu_factory::main_menu_e && current_game_state_ != game::main_menu)
	{
		current_game_state_ = game::game_state::main_menu;
	}
	return current_game_state_;
}

void menu_controller::draw(sf::RenderWindow & main_win) const
{
	current_menu_->draw(main_win);
}

void menu_controller::change_menu(menu_factory::menu_factory::type_menu new_menu_type)
{
	if (current_menu_)
		delete_menu();
	current_menu_ = menu_factory::menu_factory::create_menu(new_menu_type);
}

void menu_controller::delete_menu()
{
	delete current_menu_;
	current_menu_ = nullptr;
}