#include "modify_account.h"
#include "input_manager.h"
#include "game.h"
#include "account_controller.h"

modify_account::modify_account(): modifying_password_(false), modifying_username_(false), modify_confirmation_(false)
{
	// First part of the menu.
	title_1_ = text("Account Modification", sf::Vector2f(0, 0), text::title);
	title_1_.set_position(sf::Vector2f(game::view_width / 2 - title_1_.get_text_size() / 2, game::view_height/2 - 60));

	modify_username_ = button("Modify username", sf::Vector2f(30, 10), text::normal);
	modify_username_.set_position(sf::Vector2f(game::view_width / 2 - modify_username_.get_text_size() / 2, game::view_height/2));

	modify_password_ = button("Modify password", sf::Vector2f(30, 40), text::normal);
	modify_password_.set_position(sf::Vector2f(game::view_width / 2 - modify_password_.get_text_size() / 2, game::view_height/2 + 30));

	back_account_management_ = button("Back", sf::Vector2f(30, 100), text::normal);
	back_account_management_.set_position(sf::Vector2f(game::view_width / 2 - back_account_management_.get_text_size() / 2, game::view_height/2 + 90));

	// Second part of the menu
	title_2_ = text("Account Modification", sf::Vector2f(0, 0), text::title);
	title_2_.set_position(sf::Vector2f(game::view_width / 2 - title_2_.get_text_size() / 2, 60));

	nb_of_accounts_ = account_controller::get_nb_of_accounts();
	accounts_ = new button[nb_of_accounts_];
	const auto distance_between_buttons = 30;
	std::vector<sf::String> accounts = account_controller::get_accounts_screen_name();
	for (size_t i = 0; i < nb_of_accounts_; i++)
	{
		accounts_[i] = button(accounts[i], sf::Vector2f(0, 0), text::normal);
		accounts_[i].set_position(Vector2f(
			game::view_width / 2 - accounts_[i].get_text_size() / 2, 
			120 + distance_between_buttons * i));
	}
	back_modify_account_ = button( "Back", Vector2f(0,0), text::normal);
	back_modify_account_.set_position(sf::Vector2f(
		game::view_width/2 - back_modify_account_.get_text_size()/2, 
		180 + distance_between_buttons * nb_of_accounts_));

	// Third part of the menu.
	title_3_ = text("Account Modification", sf::Vector2f(0, 0), text::title);
	title_3_.set_position(sf::Vector2f(game::view_width / 2 - title_3_.get_text_size() / 2, game::view_height/2 - 60));

	const auto textbox_char_size = 20;
	const auto textbox_limit = 20;
	account_modification_message_ = text(
		"",
		Vector2f(0,0),
		text::normal);
	textbox_ = textbox(
		"",
		Vector2f(0, 0),
		text::normal);
	confirm_ = button(
		"confirm",
		Vector2f(0,0),
		text::normal);
	confirm_.set_position(
		sf::Vector2f(
			game::view_width / 2 - confirm_.get_text_size() - 20, 
			game::view_height / 2 + 80));
	cancel_ = button(
		"cancel",
		sf::Vector2f(
			game::view_width / 2 + 20,
			game::view_height / 2 + 80),
		text::normal);
	account_to_modify_ = "";
}

void modify_account::draw(sf::RenderWindow& main_win)
{
	// First menu.
	if (!modifying_password_ && !modifying_username_)
	{
		title_1_.draw(main_win);
		modify_password_.draw(main_win);
		modify_username_.draw(main_win);
		back_account_management_.draw(main_win);
	}
	// Third menu.
	else if(modify_confirmation_)
	{
		title_3_.draw(main_win);
		confirm_.draw(main_win);
		cancel_.draw(main_win);
		textbox_.draw(main_win);
		account_modification_message_.draw(main_win);
	}
	// Second menu.
	else
	{
		title_2_.draw(main_win);
		for (size_t i = 0; i < nb_of_accounts_; i++)
		{
			accounts_[i].draw(main_win);
		}
		back_modify_account_.draw(main_win);
	}
}

menu_factory::menu_factory::type_menu modify_account::update()
{
	// First menu.
	if (!modifying_password_ && !modifying_username_)
	{
		if(modify_password_.update())
		{
			modifying_password_ = true;
			textbox_.set_placeholder_text("New password");
			textbox_.set_position(Vector2f(game::view_width / 2 - textbox_.get_box_length()/2, game::view_height / 2 + 40));
			account_modification_message_.set_string("Type the new password for the account:");
			account_modification_message_.set_position(
				Vector2f(
					game::view_width / 2 - account_modification_message_.get_text_size() / 2, 
					game::view_height / 2));
		}
		else if(modify_username_.update())
		{
			modifying_username_ = true;
			textbox_.set_placeholder_text("New username");
			textbox_.set_position(Vector2f(game::view_width / 2 - textbox_.get_box_length() / 2, game::view_height / 2 + 40));
			account_modification_message_.set_string("Type the new username for the account:");
			account_modification_message_.set_position(
				Vector2f(
					game::view_width / 2 - account_modification_message_.get_text_size() / 2,
					game::view_height / 2));
		}
		else if(back_account_management_.update())
		{
			return menu_factory::menu_factory::account_management_e;
		}
	}
	// Third menu.
	else if(modify_confirmation_)
	{
		if (input_manager::get_input_manager()->get_mouse_l_click_2())
		{
			// Manage textbox selection.
			if (textbox_.is_selected())
			{
				textbox_.selected();
			}
			else
			{
				textbox_.unselected();
			}
		}
		if (input_manager::get_input_manager()->get_backspace_key())
		{
			textbox_.remove_char();
		}
		if (input_manager::get_input_manager()->get_text_entered_event())
		{
			textbox_.add_text(input_manager::get_input_manager()->get_last_key_sequence());
		}
		if(confirm_.update())
		{
			if(modifying_password_)
			{
				account_controller::modify_account_password(account_to_modify_, textbox_.get_text_string());
				return menu_factory::menu_factory::account_management_e;
			}
			if(modifying_username_)
			{
				account_controller::modify_account_username(account_to_modify_, textbox_.get_text_string());
				return menu_factory::menu_factory::account_management_e;
			}
		}
		if(cancel_.update())
		{
			modifying_username_ = false;
			modifying_password_ = false;
			modify_confirmation_ = false;
		}
	}
	// Second menu.
	else
	{
		for (size_t i = 0; i < nb_of_accounts_; i++)
		{
			if (accounts_[i].update())
			{
				account_to_modify_ = accounts_[i].get_text_string();
				modify_confirmation_ = true;
			}
		}
		if (back_modify_account_.update())
		{
			modifying_username_ = false;
			modifying_password_ = false;
			modify_confirmation_ = false;
		}
	}
	return menu_factory::menu_factory::modify_account_e;
}

modify_account::~modify_account()
{
}