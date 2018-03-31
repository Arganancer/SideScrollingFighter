#ifndef ACCOUNT_MODEL_H
#define ACCOUNT_MODEL_H
#include <SFML/System/String.hpp>
#include <vector>

class account_model
{
public:
	static bool init();

	/// <summary>
	/// Adds the given account to the account.txt file.
	/// </summary>
	/// <param name="account_and_password">The account and password.</param>
	static void add_account(sf::String account_and_password);

	/// <summary>
	/// Gets the account if it exists.
	/// </summary>
	/// <param name="account_name">The name of the account.</param>
	/// <param name="account_password">The name of the account.</param>
	/// <returns>
	/// account_password: Since it is a reference, the original is modified.
	///		account_password = the password if it exists, otherwise account_password = "".
	///		The account validation is then done in account_controller, not in the model.
	/// bool: returns true if the account name is present, otherwise returns false.
	/// </returns>
	static bool get_account(sf::String account_name, sf::String& account_password, sf::String& internal_representation);

	/// <summary>
	/// Gets all of the accounts formatted intro pairs (username, password).
	/// Pairs are then stored in a vector.
	/// </summary>
	/// <returns>Vector of pairs, each pair containes (username, password).</returns>
	static std::vector<sf::String> get_accounts();

	/// <summary>
	/// Deletes the account entry from the account txt file, and calls the delete scores for the specified account in the score_controller.
	/// </summary>
	/// <param name="account_name">Name of the account.</param>
	static void delete_account(sf::String account_name);

	static void modify_account_password(sf::String internal_representation, sf::String new_password);

	/// <summary>
	/// Modifies the account screen name (the internal representation does not change.
	/// </summary>
	/// <param name="new_screen_name">New screen name for the account.</param>
	static void modify_account_username(sf::String internal_representation, sf::String new_screen_name);

	static sf::String get_current_user_screen_name();

	static sf::String get_current_user_internal_representation();

	static void set_current_user(sf::String current_user_screen_name, sf::String current_user_internal_representation);

	static void log_out_current_user();

	static sf::String get_screen_name_from_internal(sf::String);

	static sf::String get_internal_from_screen_name(sf::String);

	static sf::String get_next_internal_value();

	static int account_model::get_nb_of_accounts();

private:
	/// <summary>
	/// The current user's internal representation.
	/// For it's use throughout the program, this code is stored as a string.
	/// However, the internal representation is an integer that is generated at the time the account is created.
	/// </summary>
	static sf::String current_user_internal_representation_;

	/// <summary>
	/// The current user's screen name. The screen name is used for log-in purposes, 
	/// as well as the visual representation of the account in the game.
	/// </summary>
	static sf::String current_user_screen_name_;

	static std::string accounts_file_location_;
	account_model() = delete;
};

#endif