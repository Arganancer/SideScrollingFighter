#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H
#include "menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "button.h"
#include "text.h"

class high_score : public menu
{
public:
	~high_score();
	high_score();
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
