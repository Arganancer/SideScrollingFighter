#ifndef SCORE_MODEL_H
#define SCORE_MODEL_H
#include <string>
#include <vector>

class score_model
{
public:	
	/// <summary>
	/// Initializes this instance.
	/// </summary>
	/// <returns></returns>
	static bool init();
	
	/// <summary>
	/// Gets the high score.
	/// </summary>
	/// <returns></returns>
	static std::vector<std::pair<std::string, std::string>> get_high_score();

	/// <summary>
	/// Gets my high score.
	/// </summary>
	/// <param name="username">The username.</param>
	/// <returns></returns>
	static std::vector<std::pair<std::string, std::string>> get_my_high_score(std::string username);
	
	/// <summary>
	/// Sorts the vector.
	/// </summary>
	static void sort_vector();
	
	/// <summary>
	/// Saves the new score.
	/// </summary>
	/// <param name="username">The username.</param>
	/// <param name="score">The score.</param>
	/// <returns></returns>
	static bool save_new_score(std::string username, std::string score);
	
	/// <summary>
	/// Deletes the score related to the account.
	/// </summary>
	/// <param name="username">The username.</param>
	/// <returns></returns>
	static bool delete_account_score(std::string username);
	
	/// <summary>
	/// Gets the nb score.
	/// </summary>
	/// <returns></returns>
	static int get_nb_score();
		
	/// <summary>
	///Gets the line into a pair vector.
	/// </summary>
	/// <returns></returns>
	static std::vector<std::pair<std::string, std::string>> line_to_pair_vector();
	
	/// <summary>
	/// Gets the current search.
	/// </summary>
	/// <returns></returns>
	static std::string get_current_search();
	
	/// <summary>
	/// Sets the current search.
	/// </summary>
	/// <param name="search">The search.</param>
	static void set_current_search(std::string search);
private:
	static int nb_score_;
	static std::vector<std::pair<std::string, std::string>> pair_vector_;
	static std::vector<std::string> array_score_;
	static std::vector<std::string> sorted_array_score_;
	static std::string file_name_;
	static std::string temp_file_name_;
	static std::string current_search_;
};

#endif