#include "button.h"
#include "input_manager.h"


button::button()
{
}

button::button(std::string text, sf::Vector2f position, style_text style) : text(text, position, style)
{
	//button_hitbox_.top = position.y;
	//button_hitbox_.left = position.x;
	//button_hitbox_.height = char_size_;
	//button_hitbox_.width = char_size_ * int(text.length());
	button_hitbox_ = text_.getGlobalBounds();
}

bool button::update()
{
	// Evaluate if mouse is hovering over button
	if (button_hitbox_.contains(sf::Vector2f(input_manager::get_input_manager()->get_mouse_position())))
	{
		text_.setFillColor(color_highlight_);
		// Evaluate if mouse left button is pressed while hovering over button.
		if(input_manager::get_input_manager()->get_mouse_l_click())
		{
			return true;
		}
	}
	else
	{
		text_.setFillColor(color_);
	}
	return false;
}

void button::set_position(sf::Vector2f new_position)
{
	text::set_position(new_position);
	button_hitbox_ = text_.getGlobalBounds();
}
