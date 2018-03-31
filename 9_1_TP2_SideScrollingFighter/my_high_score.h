#ifndef MY_HIGH_SCORE_H
#define MY_HIGH_SCORE_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"

class my_high_score : public menu
{
public:
	~my_high_score();
	my_high_score();
	void draw(sf::RenderWindow& main_win) override;
	menu_factory::menu_factory::type_menu update() override;
private:
	text title_;
	text error_;
	button back_;
	std::vector<std::pair<std::string, std::string>> score_vector_;
	std::vector<text> score_vector_label_;
	int nb_score_;
};
#endif
