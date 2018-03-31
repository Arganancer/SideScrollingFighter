#ifndef ACCOUNT_CONTROLLER_H
#define ACCOUNT_CONTROLLER_H
#include <SFML/System/String.hpp>
#include <vector>

class account_controller
{
public:
	static bool init();
	static bool create_account(sf::String username, sf::String password);
	static bool log_in(sf::String username, sf::String password);
	static void log_out();
	static void delete_account(sf::String account_name);
	static bool modify_account_password(sf::String account_name, sf::String new_password);
	static bool modify_account_username(sf::String current_username, sf::String new_username);

	static void set_username_to_evaluate(sf::String username);
	static void set_password_to_evaluate(sf::String password);

	static int get_nb_of_accounts();
	static std::vector<sf::String> account_controller::get_accounts_screen_name();
	static sf::String get_username_to_evaluate();
	static sf::String get_password_to_evaluate();
private:
	static bool validate_password(sf::String password);
	static bool validate_username(sf::String username);
	static sf::String username_to_evaluate_;
	static sf::String password_to_evaluate_;
};

#endif