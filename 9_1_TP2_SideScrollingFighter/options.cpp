#include  "options.h"
#include "game.h"

options::options()
{
	title_ = text("Options", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	sound_ = button("Sound", sf::Vector2f(30, 10), text::normal);
	sound_.set_position(sf::Vector2f(game::view_width / 2 - sound_.get_text_size() / 2, game::view_height / 2));

	back_ = button("Back", sf::Vector2f(30, 70), text::normal);
	back_.set_position(sf::Vector2f(game::view_width / 2 - back_.get_text_size() / 2, game::view_height / 2 + 60));

}

void options::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	sound_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu options::update()
{
	if(sound_.update())
	{
		// TODO: Implement sound functionality.
	}
	if (back_.update())
	{
		// TODO: Manage the difference between returning from the options/pause_menu and the options/main_menu.
		return menu_factory::menu_factory::main_menu_e;
	}
	return menu_factory::menu_factory::options_e;
}

options::~options()
{
}
