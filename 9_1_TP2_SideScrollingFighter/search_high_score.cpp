#include  "search_high_score.h"
#include "score_controller.h"
#include "game.h"
#include "account_controller.h"
#include "account_model.h"


search_high_score::~search_high_score()
{
}

search_high_score::search_high_score()
{
	back_ = button("Back", sf::Vector2f(30, 70), text::normal);
	error_ = text("", sf::Vector2f(game::view_width / 2 - error_.get_text_size() / 2, game::view_height / 2 ), text::normal);
	
	username_ = textbox("Username", Vector2f(0, 0), text::normal);
	username_.set_position(Vector2f(game::view_width / 2 - username_.get_box_length() / 2, game::view_height / 2 - 40));
	username_.selected();
	active_textbox_ = &username_;

	search_ = button("Search", Vector2f(0, game::view_height / 2 + 30), text::normal_plus);
	search_.set_position(Vector2f(game::view_width / 2 - search_.get_text_size() / 2, game::view_height / 2 + 40));


}

void search_high_score::draw(sf::RenderWindow& main_win)
{
	main_win.clear();

	if (score_controller::request_current_search() == " ")
	{
		username_.draw(main_win);
		search_.draw(main_win);
	}

	else if(nb_score_ > 0)
	{
		for (int i = 0; i < nb_score_; i++)
		{
			score_vector_label_[i].draw(main_win);
		}
	}
	error_.draw(main_win);
	back_.draw(main_win);
}

menu_factory::menu_factory::type_menu search_high_score::update()
{
	if (input_manager::get_input_manager()->get_mouse_l_click_2())
	{
		if (username_.is_selected())
		{
			active_textbox_ = &username_;
			username_.selected();
		}
		else
		{
			active_textbox_ = nullptr;
			username_.unselected();
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
	//search attempt
	if (search_.update() || input_manager::get_input_manager()->get_enter_key())
	{
		score_controller::request_set_current_search(search_.get_text_string());
		if (score_controller::request_current_search() != " ")
		{

			score_vector_ = score_controller::request_my_high_score(account_model::get_internal_from_screen_name(username_.get_text_string()));
			nb_score_ = score_controller::request_nb_score();
			if (nb_score_ > 0)
			{
				error_.set_string("");
				for (int i = 0; i < nb_score_; i++)
				{
					sf::Vector2f initial_pos = sf::Vector2f(30, 10);
					if (i <= 10)
					{
						std::string username = account_model::get_screen_name_from_internal(account_model::get_internal_from_screen_name(username_.get_text_string()));
						std::string score = score_vector_[i].first + " : " + username;
						text temp_label = text(score, sf::Vector2f(initial_pos.x, initial_pos.y + (30 * i)), text::normal);
						temp_label.set_position(sf::Vector2f(game::view_width / 2 - temp_label.get_text_size() / 2, game::view_height / 2 + (30 * i)));

						score_vector_label_.push_back(temp_label);
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				error_.set_string("Ce compte n'existe pas ou n'a pas de score enregisté.");
			}
		}
		return menu_factory::menu_factory::search_high_score_e;
	}
	if(back_.update())
	{
		score_controller::request_set_current_search(" ");
		return menu_factory::menu_factory::main_menu_e;
	}
	return menu_factory::menu_factory::search_high_score_e;
}

