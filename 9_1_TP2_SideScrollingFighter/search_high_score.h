#ifndef SEARCH_HIGH_SCORE
#define SEARCH_HIGH_SCORE
#include "menu.h"
#include "text.h"
#include "button.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "textbox.h"

class search_high_score : public menu
{
public:
	~search_high_score();
	search_high_score();
	void draw(sf::RenderWindow&  main_win) override;
	menu_factory::menu_factory::type_menu update() override;
private:
	text title_;
	text error_;
	button back_;
	button search_;
	std::vector<std::pair<std::string, std::string>> score_vector_;
	std::vector<text> score_vector_label_;
	int nb_score_ = 0;
	textbox username_;
	textbox * active_textbox_ = nullptr;




};
#endif
