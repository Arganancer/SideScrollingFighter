#include "play.h"
#include "game.h"

play::play()
{
	title_ = text("Play", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	singleplayer_ = button("Single Player", sf::Vector2f(0, 0), text::normal);
	singleplayer_.set_position(sf::Vector2f(game::view_width / 2 - singleplayer_.get_text_size() / 2, game::view_height / 2));

	multiplayer_ = button("Multiplayer", sf::Vector2f(0, 0), text::normal);
	multiplayer_.set_position(sf::Vector2f(game::view_width / 2 - multiplayer_.get_text_size() / 2, game::view_height / 2 + 30));

	back_ = button("Back", sf::Vector2f(0, 0), text::normal);
	back_.set_position(sf::Vector2f(game::view_width / 2 - back_.get_text_size() / 2, game::view_height / 2 + 90));
}

void play::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	singleplayer_.draw(main_win);
	multiplayer_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu play::update()
{
	if(singleplayer_.update())
	{
		return menu_factory::menu_factory::play_singleplayer_e;
	}
	if(multiplayer_.update())
	{
		return menu_factory::menu_factory::multiplayer_e;
	}
	if (back_.update())
	{
		return menu_factory::menu_factory::main_menu_e;
	}
	return menu_factory::menu_factory::play_e;
}

play::~play()
{
}
