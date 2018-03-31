#include "main_menu.h"
#include "game.h"

main_menu::main_menu()
{
	title_ = text("Main Menu", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	play_ = button("Play", sf::Vector2f(0, 0), text::normal);
	play_.set_position(sf::Vector2f(game::view_width / 2 - play_.get_text_size() / 2, game::view_height / 2));

	options_ = button("Options", sf::Vector2f(0, 0), text::normal);
	options_.set_position(sf::Vector2f(game::view_width / 2 - options_.get_text_size() / 2, game::view_height / 2 + 30));

	change_account_ = button("Change Account", sf::Vector2f(0, 0), text::normal);
	change_account_.set_position(sf::Vector2f(game::view_width / 2 - change_account_.get_text_size() / 2, game::view_height / 2 + 60));

	scores_ = button("Scores", sf::Vector2f(0, 0), text::normal);
	scores_.set_position(sf::Vector2f(game::view_width / 2 - scores_.get_text_size() / 2, game::view_height / 2 + 90));

	exit_ = button("Exit", sf::Vector2f(0, 0), text::normal);
	exit_.set_position(sf::Vector2f(game::view_width / 2 - exit_.get_text_size() / 2, game::view_height / 2 + 150));
}

void main_menu::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	play_.draw(main_win);
	options_.draw(main_win);
	change_account_.draw(main_win);
	scores_.draw(main_win);
	exit_.draw(main_win);
}

menu_factory::menu_factory::type_menu main_menu::update()
{
	if(play_.update())
	{
		return menu_factory::menu_factory::play_e;
	}
	if(options_.update())
	{
		return menu_factory::menu_factory::options_e;
	}
	if (change_account_.update())
	{
		return menu_factory::menu_factory::log_in_e;
	}
	if (scores_.update())
	{
		return menu_factory::menu_factory::score_e;
	}
	if(exit_.update())
	{
		return menu_factory::menu_factory::exit_e;
	}
	return menu_factory::menu_factory::main_menu_e;
}

main_menu::~main_menu()
{
}
