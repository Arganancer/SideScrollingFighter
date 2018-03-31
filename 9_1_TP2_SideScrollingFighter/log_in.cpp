#include "log_in.h"
#include "input_manager.h"
#include "account_controller.h"
#include "game.h"

log_in::log_in()
{
	title_ = text("Side Scrolling Fighter", sf::Vector2f(0, 0), text::title);
	title_.set_position(sf::Vector2f(game::view_width / 2 - title_.get_text_size() / 2, game::view_height / 2 - 100));

	username_ = textbox("Username", Vector2f(0, 0), text::normal);
	username_.set_position(Vector2f(game::view_width / 2 - username_.get_box_length() / 2, game::view_height / 2 - 40));
	username_.selected();
	active_textbox_ = &username_;

	password_ = textbox("Password", Vector2f(0, game::view_height / 2), text::normal);
	password_.set_position(Vector2f(game::view_width / 2 - password_.get_box_length() / 2, game::view_height / 2));

	log_in_ = button("Log In", Vector2f(0, game::view_height / 2 + 30), text::normal_plus);
	log_in_.set_position(Vector2f(game::view_width / 2 - log_in_.get_text_size() / 2, game::view_height / 2 + 40));

	manage_accounts_ = button("Manage Accounts", Vector2f(0, game::view_height / 2 + 60), text::normal);
	manage_accounts_.set_position(Vector2f(game::view_width / 2 - manage_accounts_.get_text_size() / 2, game::view_height / 2 + 70));

	exit_ = button("Exit", sf::Vector2f(0, game::view_height / 2 + 120), text::normal_plus);
	exit_.set_position(Vector2f(game::view_width / 2 - exit_.get_text_size() / 2, game::view_height / 2 + 130));

	debug_play_ = button("Debug Play", sf::Vector2f(0, game::view_height / 2 + 120), text::error);
	debug_play_.set_position(Vector2f(game::view_width / 2 - debug_play_.get_text_size() / 2, game::view_height / 2 + 190));
}

void log_in::draw(RenderWindow& main_win)
{
	title_.draw(main_win);
	username_.draw(main_win);
	password_.draw(main_win);
	log_in_.draw(main_win);
	manage_accounts_.draw(main_win);
	exit_.draw(main_win);
	debug_play_.draw(main_win);
}

menu_factory::menu_factory::type_menu log_in::update()
{
	// Manage textbox selection via mouse click.
	if (input_manager::get_input_manager()->get_mouse_l_click_2())
	{
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

	// Delete char from current textbox.
	if (input_manager::get_input_manager()->get_backspace_key())
	{
		active_textbox_->remove_char();
	}

	// Add text to active textbox if text entered event is true.
	if (active_textbox_ != nullptr && input_manager::get_input_manager()->get_text_entered_event())
	{
		active_textbox_->add_text(input_manager::get_input_manager()->get_last_key_sequence());
	}

	// Log-in attempt.
	if (log_in_.update()  || input_manager::get_input_manager()->get_enter_key())
	{
		account_controller::set_username_to_evaluate(username_.get_text_string());
		account_controller::set_password_to_evaluate(password_.get_text_string());
		return menu_factory::menu_factory::main_menu_e;
	}
	if (manage_accounts_.update())
	{
		return menu_factory::menu_factory::account_management_e;
	}
	if (exit_.update())
	{
		return menu_factory::menu_factory::exit_e;
	}

	if(debug_play_.update())
	{
		return menu_factory::menu_factory::play_singleplayer_e;
	}

	return menu_factory::menu_factory::log_in_e;
}

log_in::~log_in()
{
}
