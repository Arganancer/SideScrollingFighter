#include "account_controller.h"
#include "account_model.h"
#include "score_controller.h"

sf::String account_controller::username_to_evaluate_;
sf::String account_controller::password_to_evaluate_;

bool account_controller::init()
{
	username_to_evaluate_ = "";
	password_to_evaluate_ = "";
	return true;
}

bool account_controller::create_account(sf::String username, sf::String password)
{
	// ACCOUNT LIMIT VERIFICATION
	if(account_model::get_nb_of_accounts() > 25) // A maximum of 26 accounts can exist simultaneously.
	{
		return false;
	}
	// Username Verification
	if (validate_username(username)) { return false; }
	sf::String stored_password;
	sf::String stored_internal;
	if (account_model::get_account(username, stored_password, stored_internal)) // Check to see if account name already exists.
	{
		return false;
	}
	// Password Verification
	if (validate_password(password)) { return false; }
	// Register new user
	const auto account_save_log = account_model::get_next_internal_value() + "|" + username + "|" + password;
	account_model::add_account(account_save_log);
	return true;

}

bool account_controller::validate_password(sf::String password)
{
	// PASSWORD VALIDATION
	if (password.getSize() < 5 || password.getSize() > 15)
	{
		return false;
	}
	if (!std::any_of(password.begin(), password.end(), islower))
	{
		return false;
	}
	if (!std::any_of(password.begin(), password.end(), isupper))
	{
		return false;
	}
	if (!std::any_of(password.begin(), password.end(), isdigit))
	{
		return false;
	}
	if (!std::any_of(password.begin(), password.end(), ispunct))
	{
		return false;
	}
	return true;
}

bool account_controller::validate_username(sf::String username)
{
	// USERNAME VALIDATION
	if (username.getSize() < 3 || username.getSize() > 25)
	{
		return false;
	}
	return true;
}

bool account_controller::log_in(sf::String username, sf::String password)
{
	sf::String stored_password;
	sf::String stored_internal;
	if (account_model::get_account(username, stored_password, stored_internal))
	{
		if (password == stored_password)
		{
			account_model::set_current_user(username, stored_internal);
			return true;
		}
		else
		{
			// TODO: Manage "Password does not match account".
		}
	}
	else
	{
		// TODO: Manage "Account does not exist".
	}
	return false;
}

void account_controller::log_out()
{
	account_model::log_out_current_user();
}

void account_controller::delete_account(sf::String account_name)
{
	sf::String stored_password;
	sf::String stored_internal;
	if (account_model::get_account(account_name, stored_password, stored_internal))
	{
		account_model::delete_account(stored_internal);
		score_controller::request_delete_account_high_score(stored_internal);
	}
}

bool account_controller::modify_account_password(sf::String account_name, sf::String new_password)
{
	if (validate_password(new_password)) { return false; } // Validate new password.
	sf::String stored_password;
	sf::String stored_internal;
	if (account_model::get_account(account_name, stored_password, stored_internal))
	{
		account_model::modify_account_password(stored_internal, new_password);
	}
	return true;
}

bool account_controller::modify_account_username(sf::String account_name, sf::String new_username)
{
	if (validate_username(new_username)) { return false; } // Validate new username.
	sf::String stored_password;
	sf::String stored_internal;
	if (!account_model::get_account(new_username, stored_password, stored_internal)) // Check first to see if the new user name already exists.
	{
		if (account_model::get_account(account_name, stored_password, stored_internal)) // Check then to see if the account we want to modify exists.
		{
			account_model::modify_account_username(stored_internal, new_username);
		}
	}
	return true;
}

void account_controller::set_username_to_evaluate(sf::String username)
{
	username_to_evaluate_ = username;
}

void account_controller::set_password_to_evaluate(sf::String password)
{
	password_to_evaluate_ = password;
}

sf::String account_controller::get_username_to_evaluate()
{
	return username_to_evaluate_;
}

sf::String account_controller::get_password_to_evaluate()
{
	return password_to_evaluate_;
}

std::vector<sf::String> account_controller::get_accounts_screen_name() // return screen_name
{
	return account_model::get_accounts();
}

int account_controller::get_nb_of_accounts()
{
	return account_model::get_nb_of_accounts();
}
