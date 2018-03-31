#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"
#include "textbox.h"

class create_account : public menu
{
public:
	~create_account();
	create_account();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private:
	text title_;
	textbox username_;
	textbox password_;
	textbox * active_textbox_ = nullptr;
	button create_account_;
	button back_;
};

#endif