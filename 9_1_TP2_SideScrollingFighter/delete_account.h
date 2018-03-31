#ifndef DELETE_ACCOUNT_H
#define DELETE_ACCOUNT_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"
#include "text.h"

class delete_account : public menu
{
public:
	~delete_account();
	delete_account();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private:
	text title_;
	text account_selection_text_;
	button * accounts_;
	int nb_of_accounts_;
	button back_;
	bool delete_confirmation_is_active_;
	text delete_confirmation_message_;
	sf::String account_to_delete_;
	button yes_;
	button no_;
};

#endif