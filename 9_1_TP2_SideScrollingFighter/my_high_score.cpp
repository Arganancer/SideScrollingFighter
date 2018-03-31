#include  "my_high_score.h"
#include  "score_controller.h"
#include  "game.h"

my_high_score::~my_high_score()
{
}

my_high_score::my_high_score()
{
	back_ = button("Back", sf::Vector2f(30, 70), text::normal);

	score_vector_ = score_controller::request_my_high_score(score_controller::request_username_internal());
	nb_score_ = score_controller::request_nb_score();
	error_ = text("Vous n'avez pas de score enregistré.", sf::Vector2f(game::view_width / 2 - error_.get_text_size() / 2, game::view_height / 2), text::normal);
	for (int i = 0; i <nb_score_; i++)
	{
		sf::Vector2f initial_pos = sf::Vector2f(30, 10);
		if (i <= 10)
		{
			std::string username = score_controller::request_username(score_vector_[1].second);
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

void my_high_score::draw(sf::RenderWindow& main_win)
{
	back_.draw(main_win);
	if(nb_score_ >0)
	{
		for (int i = 0; i < nb_score_; i++)
		{
			score_vector_label_[i].draw(main_win);
		}
	}
	else
	{
		error_.draw(main_win);
	}
}

menu_factory::menu_factory::type_menu my_high_score::update()
{
	if (back_.update())
	{
		// TODO: Manage accessing score screen from the end-game screen, and how we adjust functionality accordingly.
		return menu_factory::menu_factory::main_menu_e;
	}
	return menu_factory::menu_factory::my_high_score_e;
}
