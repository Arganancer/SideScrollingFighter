#include "multiplayer.h"
#include "game.h"

multiplayer::multiplayer()
{
	title_ = text("Multiplayer", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));
	
	versus_ = button("Versus", sf::Vector2f(30, 10), text::normal);
	versus_.set_position(sf::Vector2f(game::view_width / 2 - versus_.get_text_size() / 2, game::view_height / 2));

	coop_ = button("Co-op", sf::Vector2f(30, 40), text::normal);
	coop_.set_position(sf::Vector2f(game::view_width / 2 - coop_.get_text_size() / 2, game::view_height / 2 + 30));

	back_ = button("Back", sf::Vector2f(30, 100), text::normal);
	back_.set_position(sf::Vector2f(game::view_width / 2 - back_.get_text_size() / 2, game::view_height / 2 + 90));

}

void multiplayer::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	versus_.draw(main_win);
	coop_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu multiplayer::update()
{
	if(versus_.update())
	{
		// TODO: Implement versus functionality.
	}
	if(coop_.update())
	{
		// TODO: Implement coop functionality.
	}
	if (back_.update())
	{
		return menu_factory::menu_factory::play_e;
	}
	return menu_factory::menu_factory::multiplayer_e;
}


multiplayer::~multiplayer()
{
}
