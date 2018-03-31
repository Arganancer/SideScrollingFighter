#ifndef MODIFY_ACCOUNT_H
#define MODIFY_ACCOUNT_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"
#include "text.h"
#include "textbox.h"

class modify_account : public menu
{
public:
	~modify_account();
	modify_account();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private:
	text title_1_;
	text title_2_;
	text title_3_;
	button * accounts_;
	int nb_of_accounts_;
	button back_account_management_;
	button back_modify_account_;
	button modify_username_;
	button modify_password_;
	button confirm_;
	button cancel_;
	bool modifying_password_;
	bool modifying_username_;
	bool modify_confirmation_;

	sf::String account_to_modify_;
	text account_modification_message_;
	textbox textbox_;
};

#endif