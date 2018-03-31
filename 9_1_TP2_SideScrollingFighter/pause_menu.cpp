#include "pause_menu.h"
#include "game.h"

pause_menu::pause_menu()
{
	title_ = text("Game Paused", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	return_to_game_ = button("Return to Game", sf::Vector2f(30, 10), text::normal);
	return_to_game_.set_position(sf::Vector2f(game::view_width / 2 - return_to_game_.get_text_size() / 2, game::view_height / 2));

	options_ = button("Options", sf::Vector2f(30, 40), text::normal);
	options_.set_position(sf::Vector2f(game::view_width / 2 - options_.get_text_size() / 2, game::view_height / 2 + 30));

	return_to_main_menu_ = button("Return to Main Menu", sf::Vector2f(30, 70), text::normal);
	return_to_main_menu_.set_position(sf::Vector2f(game::view_width / 2 - return_to_main_menu_.get_text_size() / 2, game::view_height / 2 + 60));

	exit_ = button("Exit", sf::Vector2f(30, 130), text::normal);
	exit_.set_position(sf::Vector2f(game::view_width / 2 - exit_.get_text_size() / 2, game::view_height / 2 + 120));
}

void pause_menu::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	return_to_game_.draw(main_win);
	options_.draw(main_win);
	return_to_main_menu_.draw(main_win);
	exit_.draw(main_win);
}

menu_factory::menu_factory::type_menu pause_menu::update()
{
	if (return_to_game_.update())
	{
		return menu_factory::menu_factory::play_singleplayer_e;
	}
	if(options_.update())
	{
		return menu_factory::menu_factory::options_e;
	}
	if(return_to_main_menu_.update())
	{
		return menu_factory::menu_factory::main_menu_e;
	}
	if(exit_.update())
	{
		return menu_factory::menu_factory::exit_e;
	}
	return menu_factory::menu_factory::pause_menu_e;
}


pause_menu::~pause_menu()
{
}
