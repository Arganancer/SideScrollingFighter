#include "create_account.h"
#include "input_manager.h"
#include "account_controller.h"
#include "game.h"

create_account::create_account()
{
	title_ = text("Account Creation", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 60));

	username_ = textbox("Username",Vector2f(30, 10), text::normal);
	username_.set_position(sf::Vector2f(game::view_width / 2 - username_.get_box_length() / 2, game::view_height / 2));
	username_.selected();
	active_textbox_ = &username_;

	password_ = textbox("Password", Vector2f(30, 50), text::normal);
	password_.set_position(sf::Vector2f(game::view_width / 2 - password_.get_box_length() / 2, game::view_height / 2 + 40));

	create_account_ = button("Create Account", Vector2f(30, 90), text::normal);
	create_account_.set_position(sf::Vector2f(game::view_width / 2 - create_account_.get_text_size() / 2, game::view_height / 2 + 80));

	back_ = button("Cancel", Vector2f(30, 120), text::normal);
	back_.set_position(sf::Vector2f(game::view_width / 2 - back_.get_text_size() / 2, game::view_height / 2 + 140));
}

void create_account::draw(RenderWindow& main_win)
{
	title_.draw(main_win);
	username_.draw(main_win);
	password_.draw(main_win);
	create_account_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu create_account::update()
{
	if (input_manager::get_input_manager()->get_mouse_l_click_2())
	{
		// Manage textbox selection via mouse click.
		if (username_.is_selected())
		{
			active_textbox_ = &username_;
			username_.selected();
			password_.unselected();
		}
		else if (password_.is_selected())
		{
			active_textbox_ = &password_;
			password_.selected();
			username_.unselected();
		}
		else
		{
			active_textbox_ = nullptr;
			username_.unselected();
			password_.unselected();
		}
	}

	// Manage textbox selection via tab button.
	if (input_manager::get_input_manager()->get_tab_is_pressed())
	{
		if (active_textbox_ == &username_)
		{
			active_textbox_ = &password_;
			password_.selected();
			username_.unselected();
		}
		else
		{
			active_textbox_ = &username_;
			username_.selected();
			password_.unselected();
		}
	}

	if (input_manager::get_input_manager()->get_backspace_key())
	{
		active_textbox_->remove_char();
	}

	if (active_textbox_ != nullptr && input_manager::get_input_manager()->get_text_entered_event())
	{
		active_textbox_->add_text(input_manager::get_input_manager()->get_last_key_sequence());
	}

	if (create_account_.update() || input_manager::get_input_manager()->get_enter_key())
	{
		account_controller::set_username_to_evaluate(username_.get_text_string());
		account_controller::set_password_to_evaluate(password_.get_text_string());
		return menu_factory::menu_factory::main_menu_e;
	}
	if (back_.update())
	{
		return menu_factory::menu_factory::account_management_e;
	}
	return menu_factory::menu_factory::create_account_e;
}

create_account::~create_account()
{
}
