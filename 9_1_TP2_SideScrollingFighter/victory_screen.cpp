#include "victory_screen.h"
#include "game.h"
#include "score_controller.h"
#include "account_controller.h"

victory_screen::~victory_screen()
{

}

victory_screen::victory_screen()
{
	title_ = text("Victory!", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	score_str_ = std::to_string(game::get_score());

	save_score_ = button("Save Score", sf::Vector2f(30, 70), text::normal);
	save_score_.set_position(sf::Vector2f(game::view_width / 2 - save_score_.get_text_size() / 2, game::view_height / 2 + 90));

	score_ = text(score_str_, sf::Vector2f(0, 0), text::normal);
	score_.set_position(sf::Vector2f(game::view_width / 2 - score_.get_text_size() / 2, game::view_height / 2 - 30));

	back_ = button("Back", sf::Vector2f(30, 70), text::normal);
	back_.set_position(sf::Vector2f(game::view_width / 2 - back_.get_text_size() / 2, game::view_height / 2 + 60));
}


void victory_screen::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	save_score_.draw(main_win);
	score_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu victory_screen::update()
{
	if(save_score_.update())
	{
		score_controller::request_save_new_score(score_controller::request_username_internal(), score_str_);
		return menu_factory::menu_factory::main_menu_e;
	}
	if (back_.update())
	{
		return menu_factory::menu_factory::main_menu_e;
	}
	return menu_factory::menu_factory::victory_screen_e;
}
