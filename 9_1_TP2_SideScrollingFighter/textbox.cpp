#include "textbox.h"
#include "input_manager.h"

textbox::textbox()
{
}

textbox::textbox(sf::String placeholder_text, const Vector2f position, style_text style) : 
text("",Vector2f(position.x + 3, position.y), style)
{
	const auto height = char_size_ + 10;
	limit_ = 25;
	box_.setSize(Vector2f(limit_ * char_size_, height));
	box_.setFillColor(Color::Black);
	box_.setOutlineColor(color_);
	box_.setOutlineThickness(2);
	box_.setPosition(position);
	placeholder_text_ = text(placeholder_text, Vector2f(position.x + 3, position.y), placeholder);
	set_text_style(style);
}

/// <summary>
/// Fait juste changer la couleur du cadre.
/// </summary>
void textbox::selected()
{
	box_.setOutlineColor(color_highlight_);
	text_.setFillColor(color_highlight_);
}

void textbox::unselected()
{
	box_.setOutlineColor(color_);
	text_.setFillColor(color_);
}

/// <summary>
/// Vérifie si une position is_selected au textbox
/// </summary>
bool textbox::is_selected() const
{
	const auto coord = box_.getGlobalBounds();

	if (input_manager::get_input_manager()->get_mouse_position().x > 
		coord.left && input_manager::get_input_manager()->get_mouse_position().x < 
		coord.left + coord.width &&
		input_manager::get_input_manager()->get_mouse_position().y > 
		coord.top && input_manager::get_input_manager()->get_mouse_position().y < 
		coord.top + coord.height)
	{
		return true;
	}
	return false;
}

/// <summary>
/// Le text_ est inséré et remplace le précédent.
/// </summary>
/// <param name="text_to_insert">The le text_.</param>
void textbox::insert_text(String text_to_insert)
{
	//Si trop long on concatène
	if (text_to_insert.getSize() > limit_)
	{
		text_to_insert = text_to_insert.substring(0, limit_);
	}

	text_.setString(text_to_insert);
	visual_adjustments();
}


void textbox::add_text(String text_to_add)
{
	sf::String new_string = text_.getString() + text_to_add;
	//Si trop long on concatène
	if (new_string.getSize() > limit_)
	{
		new_string = new_string.substring(0, limit_);
	}
	text_.setString(new_string);
	visual_adjustments();
}

/// <summary>
/// On ajoute un caractère à la string, si on est pas à la length maximale
/// </summary>
void textbox::add_char(const char char_to_add)
{
	if (text_.getString().getSize() >= limit_) return;

	text_.setString(text_.getString() + char_to_add);
	visual_adjustments();
}

/// <summary>
/// On retire un caractère à la string, si on est pas à la length 0
/// </summary>
void textbox::remove_char()
{
	if (text_.getString().getSize() == 0) return;

	text_.setString(text_.getString().substring(0, text_.getString().getSize() - 1));
	visual_adjustments();
}

/// <summary>
/// Ajustements visuels: le text_ est toujours centré sur la position de la box_.
/// </summary>
void textbox::visual_adjustments()
{
	text_.setOrigin(Vector2f(0, 0));
	text_.setPosition(box_.getPosition());
}

void textbox::draw(sf::RenderWindow& main_win) const
{
	main_win.draw(box_);
	text::draw(main_win);
	if (text_.getString().getSize() == 0)
	{
		placeholder_text_.draw(main_win);
	}
}

void textbox::set_placeholder_text(sf::String placeholder_text)
{
	placeholder_text_.set_string(placeholder_text);
}

int textbox::get_box_length()
{
	return box_.getSize().x;
}

void textbox::set_position(Vector2f new_position)
{
	text::set_position(Vector2f(new_position.x + 3, new_position.y));
	box_.setPosition(new_position);
	placeholder_text_.set_position(Vector2f(new_position.x + 3, new_position.y));
}
