#ifndef LOG_IN_H
#define LOG_IN_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"
#include "textbox.h"

class log_in : public menu
{
public:
	~log_in();
	log_in();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private:
	button debug_play_;
	text title_;
	button log_in_;
	button manage_accounts_;
	button exit_;
	textbox username_;
	textbox password_;
	textbox * active_textbox_ = nullptr;
};

#endif