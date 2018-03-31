#include  "score.h"
#include "game.h"


score::score()
{
	title_ = text("Score", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	my_score_ = button("My High Scores", sf::Vector2f(30, 10), text::normal);
	my_score_.set_position(sf::Vector2f(game::view_width / 2 - my_score_.get_text_size() / 2, game::view_height / 2));

	high_score_ = button("All High Scores", sf::Vector2f(30, 40), text::normal);
	high_score_.set_position(sf::Vector2f(game::view_width / 2 - high_score_.get_text_size() / 2, game::view_height / 2 + 30));

	search_high_score_ = button("Search High Scores", sf::Vector2f(30, 100), text::normal);
	search_high_score_.set_position(sf::Vector2f(game::view_width / 2 - search_high_score_.get_text_size() / 2, game::view_height / 2 + 60));

	back_ = button("Back", sf::Vector2f(30, 100), text::normal);
	back_.set_position(sf::Vector2f(game::view_width / 2 - back_.get_text_size() / 2, game::view_height / 2 + 90));
}

void score::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	my_score_.draw(main_win);
	high_score_.draw(main_win);
	search_high_score_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu score::update()
{
	if(my_score_.update())
	{
		return menu_factory::menu_factory::my_high_score_e;
	}
	if(high_score_.update())
	{
		return menu_factory::menu_factory::high_score_e;
	}
	if(search_high_score_.update())
	{
		return menu_factory::menu_factory::search_high_score_e;
	}
	if (back_.update())
	{
		// TODO: Manage accessing score screen from the end-game screen, and how we adjust functionality accordingly.
		return menu_factory::menu_factory::main_menu_e;
	}
	return menu_factory::menu_factory::score_e;
}


score::~score()
{
}
