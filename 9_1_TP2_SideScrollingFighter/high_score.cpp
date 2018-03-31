#include "high_score.h"
#include "score_controller.h"
#include "account_model.h"
#include "game.h"

high_score::~high_score()
{
}

high_score::high_score()
{
	back_ = button("Back", sf::Vector2f(30, 70), text::normal);

	// TODO: Implement global score screen.
	score_vector_ = score_controller::request_high_score();
	nb_score_ = score_controller::request_nb_score();
	error_ = text("Il n'y a pas de score enregistré", sf::Vector2f(game::view_width / 2 - error_.get_text_size() / 2, game::view_height / 2),
	              text::normal);
	for (int i = 0; i < nb_score_; i++)
	{
		sf::Vector2f initial_pos = sf::Vector2f(850, 400);
		if (i <= 9)
		{
			std::string username = account_model::get_screen_name_from_internal(score_vector_[i].second);
			std::string score = score_vector_[i].first + "   :   " + username;
			text temp_label = text(score, sf::Vector2f(initial_pos.x, initial_pos.y + (30 * i)), text::normal);
			temp_label.set_position(sf::Vector2f(game::view_width / 2 - temp_label.get_text_size() / 2,
			                                     game::view_height / 2 + (30 * i)));
			score_vector_label_.push_back(temp_label);
		}
		else
		{
			break;
		}
	}
}

void high_score::draw(sf::RenderWindow& main_win)
{
	back_.draw(main_win);
	if (nb_score_ > 0)
	{
		for (int i = 0; i < score_vector_label_.size(); i++)
		{
			score_vector_label_[i].draw(main_win);
		}
	}
	else
	{
		error_.draw(main_win);
	}
}

menu_factory::menu_factory::type_menu high_score::update()
{
	if (back_.update())
	{
		// TODO: Manage accessing score screen from the end-game screen, and how we adjust functionality accordingly.
		return menu_factory::menu_factory::main_menu_e;
	}
	return menu_factory::menu_factory::high_score_e;
}
