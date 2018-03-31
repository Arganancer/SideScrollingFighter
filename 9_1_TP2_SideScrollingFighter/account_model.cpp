#include "account_model.h"
#include <fstream>
#include <tuple>

std::string account_model::accounts_file_location_;
sf::String account_model::current_user_internal_representation_;
sf::String account_model::current_user_screen_name_;

using namespace std;

bool account_model::init()
{
	current_user_internal_representation_ = "";
	current_user_screen_name_ = "";
	accounts_file_location_ = "Data\\accounts.txt";
	return true;
}

void account_model::add_account(sf::String internal_and_account_and_password)
{
	const string temp_sf_to_std = internal_and_account_and_password + "\n";
	ofstream output_file(accounts_file_location_, std::ios_base::app | std::ios_base::out);
	output_file << temp_sf_to_std;
}

bool account_model::get_account(sf::String account_name, sf::String& account_password, sf::String& internal_representation)
{
	ifstream ifs(accounts_file_location_);
	string line;
	string username = "";
	string password = "";
	while (getline(ifs, line))
	{
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				username = line.substr(pos + 1, pos2 - pos - 1); // username is in between both pipes.
				if (username == account_name)
				{
					internal_representation = line.substr(0, pos); // internal representation is before the first pipe.
					account_password = line.substr(pos2 + 1); // password is after the second pipe.
					return true;
				}
			}
		}
	}
	return false;
}

sf::String account_model::get_screen_name_from_internal(sf::String internal)
{
	ifstream ifs(accounts_file_location_);
	string line;
	string internal_representation = "";
	string username = "";
	while (getline(ifs, line))
	{
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				internal_representation = line.substr(0, pos); // internal representation is before the first pipe.
				if (internal_representation == internal)
				{
					username = line.substr(pos + 1, pos2 - pos - 1); // username is in between both pipes.
					return username;
				}
			}
		}
	}
	return username;
}

// Returns " " if username not found.
sf::String account_model::get_internal_from_screen_name(sf::String username)
{
	ifstream ifs(accounts_file_location_);
	string line;
	string internal_representation = "";
	string username_2 = "";
	while (getline(ifs, line))
	{
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				username_2 = line.substr(pos + 1, pos2 - pos - 1); // username is in between both pipes.
				if (username_2 == username)
				{
					internal_representation = line.substr(0, pos); // internal representation is before the first pipe.
					return internal_representation;
				}
			}
		}
	}
	return " ";
}

sf::String account_model::get_next_internal_value()
{
	int highest_internal = 0;
	ifstream ifs(accounts_file_location_);
	string line;
	while (getline(ifs, line))
	{
		string internal = "";
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				internal = line.substr(0, pos); // internal representation is before the first pipe.
				if (highest_internal < stoi(internal))
				{
					highest_internal = stoi(internal);
				}
			}
		}
	}
	return to_string(highest_internal + 1);
}

int account_model::get_nb_of_accounts()
{
	auto nb_of_accounts = 0;
	ifstream ifs(accounts_file_location_);
	string line;
	while (getline(ifs, line))
	{
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				nb_of_accounts++;
			}
		}
	}
	return nb_of_accounts;
}

std::vector<sf::String> account_model::get_accounts()
{
	std::vector<sf::String> accounts;
	ifstream ifs(accounts_file_location_);
	string line;
	while (getline(ifs, line))
	{
		string username = "";
		string internal = "";
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				username = line.substr(pos + 1, pos2 - pos - 1); // username is in between both pipes.
				accounts.push_back(username);
			}
		}
	}
	return accounts;
}

void account_model::delete_account(sf::String internal)
{
	sf::String internal_representation = "";
	ifstream ifs(accounts_file_location_);
	ofstream temp("Data\\temp.txt");
	string line;
	while (getline(ifs, line))
	{
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			internal_representation = line.substr(0, pos); // internal representation is before the first pipe.
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				if(internal_representation != internal)
				{
					temp << line << endl;
				}
			}
		}
	}
	ifs.close();
	temp.close();
	if(remove(accounts_file_location_.c_str()) == 0)
	{
		rename("Data\\temp.txt", accounts_file_location_.c_str());
	}
	else
	{
		remove("Data\\temp.txt");
	}
}

void account_model::modify_account_password(sf::String internal, sf::String new_password)
{
	sf::String internal_representation = "";
	sf::String username = "";
	ifstream ifs(accounts_file_location_);
	ofstream temp("Data\\temp.txt");
	string line;
	while (getline(ifs, line))
	{
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			internal_representation = line.substr(0, pos); // internal representation is before the first pipe.
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				if (internal_representation == internal)
				{
					username = line.substr(pos + 1, pos2 - pos - 1); // username is in between both pipes.
					const std::string new_line = internal + "|" + username + "|" + new_password;
					temp << new_line << endl;
				}
				else
				{
					temp << line << endl;
				}
			}
		}
	}
	ifs.close();
	temp.close();
	if (remove(accounts_file_location_.c_str()) == 0)
	{
		rename("Data\\temp.txt", accounts_file_location_.c_str());
	}
	else
	{
		remove("Data\\temp.txt");
	}
}

void account_model::modify_account_username(sf::String internal, sf::String new_screen_name)
{
	sf::String internal_representation = "";
	sf::String password = "";
	ifstream ifs(accounts_file_location_);
	ofstream temp("Data\\temp.txt");
	string line;
	while (getline(ifs, line))
	{
		const auto pos = line.find('|'); // Find first occurence of the separating character.
		if (pos != string::npos)
		{
			internal_representation = line.substr(0, pos); // internal representation is before the first pipe.
			const auto pos2 = line.find('|', pos + 1);// Find second occurence of the separating character.
			if (pos2 != string::npos)
			{
				if (internal_representation == internal)
				{
					password = line.substr(pos2 + 1); // password is after the second pipe.
					const std::string new_line = internal + "|" + new_screen_name + "|" + password;
					temp << new_line << endl;
				}
				else
				{
					temp << line << endl;
				}
			}
		}
	}
	ifs.close();
	temp.close();
	if (remove(accounts_file_location_.c_str()) == 0)
	{
		rename("Data\\temp.txt", accounts_file_location_.c_str());
	}
	else
	{
		remove("Data\\temp.txt");
	}
}

sf::String account_model::get_current_user_screen_name()
{
	return current_user_screen_name_;
}

sf::String account_model::get_current_user_internal_representation()
{
	return current_user_internal_representation_;
}

void account_model::set_current_user(sf::String current_user_screen_name,
	sf::String current_user_internal_representation)
{
	current_user_screen_name_ = current_user_screen_name;
	current_user_internal_representation_ = current_user_internal_representation;
}

void account_model::log_out_current_user()
{
	current_user_screen_name_ = "";
	current_user_internal_representation_ = "";
}