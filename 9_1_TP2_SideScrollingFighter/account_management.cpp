#include "account_management.h"
#include "game.h"

account_management::account_management()
{
	title_ = text("Account Management", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	create_account_ = button("Create Account", sf::Vector2f(0, 0), text::normal);
	create_account_.set_position(sf::Vector2f(game::view_width / 2 - create_account_.get_text_size()/2, game::view_height / 2));
	
	delete_account_ = button("Delete Account", sf::Vector2f(0, 0), text::normal);
	delete_account_.set_position(sf::Vector2f(game::view_width / 2 - delete_account_.get_text_size() / 2, game::view_height / 2 + 30));
	
	modify_password_ = button("Modify Account", sf::Vector2f(0, 0), text::normal);
	modify_password_.set_position(sf::Vector2f(game::view_width / 2 - modify_password_.get_text_size() / 2, game::view_height / 2 + 60));
	
	back_ = button("Back", sf::Vector2f(0, 0), text::normal);
	back_.set_position(sf::Vector2f(game::view_width / 2 - back_.get_text_size() / 2, game::view_height / 2 + 120));
}

void account_management::draw(sf::RenderWindow& main_win)
{
	title_.draw(main_win);
	create_account_.draw(main_win);
	delete_account_.draw(main_win);
	modify_password_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu account_management::update()
{
	if(create_account_.update())
	{
		return menu_factory::menu_factory::create_account_e;
	}
	if (delete_account_.update())
	{
		return menu_factory::menu_factory::delete_account_e;
	}
	if (modify_password_.update())
	{
		return menu_factory::menu_factory::modify_account_e;
	}
	if (back_.update())
	{
		return menu_factory::menu_factory::log_in_e;
	}
	return menu_factory::menu_factory::account_management_e;
}
