#include "delete_account.h"
#include "input_manager.h"
#include "account_controller.h"
#include "game.h"

delete_account::delete_account()
{
	// Confirmation View
	delete_confirmation_message_ = text("", Vector2f(0, 0),	text::placeholder);

	yes_ = button( "Yes", Vector2f(0, 0),text::normal);
	yes_.set_position(sf::Vector2f(game::view_width / 2 - yes_.get_text_size() - 20, game::view_height / 2));

	no_ = button("no", Vector2f(0, 0),text::normal);
	no_.set_position(sf::Vector2f(game::view_width / 2 + 20, game::view_height / 2));

	// Account Selection view
	nb_of_accounts_ = account_controller::get_nb_of_accounts();
	accounts_ = new button[nb_of_accounts_];
	const auto distance_between_buttons = 30;

	title_ = text("Account Deletion", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, 60));

	account_selection_text_ = text("Select an account to delete from the following list:", sf::Vector2f(0, 0), text::placeholder);
	account_selection_text_.set_position(sf::Vector2f(game::view_width / 2 - account_selection_text_.get_text_size() / 2, 90));

	std::vector<sf::String> accounts = account_controller::get_accounts_screen_name();
	for (size_t i = 0; i < nb_of_accounts_; i++)
	{
		accounts_[i] = button(accounts[i], Vector2f(0, 0), text::normal);
		accounts_[i].set_position(Vector2f(game::view_width / 2 - accounts_[i].get_text_size() / 2, 150 + distance_between_buttons * i));
	}

	back_ = button("Back", sf::Vector2f(0, 0), text::normal_plus);
	back_.set_position(Vector2f(game::view_width / 2 - back_.get_text_size() / 2, 180 + distance_between_buttons * nb_of_accounts_));

	delete_confirmation_is_active_ = false;
	account_to_delete_ = "";
}

void delete_account::draw(sf::RenderWindow& main_win)
{
	if (delete_confirmation_is_active_)
	{
		yes_.draw(main_win);
		no_.draw(main_win);
		delete_confirmation_message_.draw(main_win);
	}
	else
	{
		title_.draw(main_win);
		account_selection_text_.draw(main_win);
		for (size_t i = 0; i < nb_of_accounts_; i++)
		{
			accounts_[i].draw(main_win);
		}
		back_.draw(main_win);
	}
}

menu_factory::menu_factory::type_menu delete_account::update()
{
	if (!delete_confirmation_is_active_)
	{
		for (size_t i = 0; i < nb_of_accounts_; i++)
		{
			if (accounts_[i].update())
			{
				account_to_delete_ = accounts_[i].get_text_string();
				delete_confirmation_message_.set_string("Are you sure you wish to delete the account " + account_to_delete_ + "?");
				delete_confirmation_message_.set_position(sf::Vector2f(
					game::view_width / 2 - delete_confirmation_message_.get_text_size() / 2, 
					game::view_height / 2 - 30));
				delete_confirmation_is_active_ = true;
			}
		}
		if (back_.update())
		{
			return menu_factory::menu_factory::account_management_e;
		}
	}
	if(delete_confirmation_is_active_)
	{
		if(yes_.update())
		{
			account_controller::delete_account(account_to_delete_);
			delete_confirmation_is_active_ = false;
			return menu_factory::menu_factory::account_management_e;
		}
		if (no_.update())
		{
			delete_confirmation_is_active_ = false;
		}
	}
	return menu_factory::menu_factory::delete_account_e;
}

delete_account::~delete_account()
{
}