#ifndef SCORE_H
#define SCORE_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class score : public menu
{
public:
	~score();
	score();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;

private:
	text title_;
	button my_score_;
	button high_score_;
	button search_high_score_;
	button back_;
};

#endif
