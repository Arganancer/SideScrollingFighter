#include "score_controller.h"
#include "score_model.h"
#include "account_model.h"

std::vector<std::pair<std::string, std::string>> score_controller::request_my_high_score(std::string username)
{
	return score_model::get_my_high_score(username);
}

std::vector<std::pair<std::string, std::string>> score_controller::request_high_score()
{
	return score_model::get_high_score();
}

bool score_controller::request_delete_account_high_score(std::string internal_username)
{
	return score_model::delete_account_score(internal_username);
}

bool score_controller::request_save_new_score(std::string username, std::string score)
{
	return score_model::save_new_score(username, score);
}

int score_controller::request_nb_score()
{
	return score_model::get_nb_score();
}


std::string score_controller::request_username_internal()
{
	return account_model::get_current_user_internal_representation();
}

std::string score_controller::request_username(std::string internal )
{
	return account_model::get_screen_name_from_internal(internal);
}

std::string score_controller::request_current_search()
{
	return score_model::get_current_search();
}

void score_controller::request_set_current_search(std::string search)
{
	score_model::set_current_search(search);
}
