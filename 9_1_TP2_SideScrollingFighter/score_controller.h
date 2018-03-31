#ifndef SCORE_CONTROLLER_H
#define SCORE_CONTROLLER_H
#include "menu_factory.h"
#include <SFML/Graphics/RenderWindow.hpp>

class score_controller
{
public:
	//requeste
	
	/// <summary>
	/// Requests my high score.
	/// </summary>
	/// <param name="username">The username.</param>
	/// <returns></returns>
	static std::vector<std::pair<std::string, std::string>> request_my_high_score(std::string username);	

	/// <summary>
	/// Requests the high scores.
	/// </summary>
	/// <returns></returns>
	static std::vector<std::pair<std::string, std::string>> request_high_score();
	
	/// <summary>
	/// Requests delete account high score.
	/// </summary>
	/// <param name="internal_username">The internal username.</param>
	/// <returns></returns>
	static bool request_delete_account_high_score(std::string internal_username);
	
	/// <summary>
	/// Requests save new score.
	/// </summary>
	/// <param name="username">The username.</param>
	/// <param name="score">The score.</param>
	/// <returns></returns>
	static bool request_save_new_score(std::string username, std::string score);
	
	/// <summary>
	/// Requests nb score.
	/// </summary>
	/// <returns></returns>
	static int request_nb_score();
	
	/// <summary>
	/// Requests the current search.
	/// </summary>
	/// <returns></returns>
	static std::string request_current_search();
		
	/// <summary>
	/// Requests the username internal.
	/// </summary>
	/// <returns></returns>
	static std::string request_username_internal();
	
	/// <summary>
	/// Requests the username.
	/// </summary>
	/// <param name="internal">The internal.</param>
	/// <returns></returns>
	static std::string request_username(std::string internal);
	
	/// <summary>
	/// Sets the current search
	/// </summary>
	/// <param name="search">The search.</param>
	static void request_set_current_search(std::string search);
};


#endif