#pragma once
#include <SFML/Graphics.hpp>
#include "text.h"

using namespace sf;

/// <summary>
/// textbox de base, pleine de flaws, mais qui fera la job pour ce TP
/// Notez que on peut l'utiliser aussi comme text_ d'information.  Id�alement,
/// On aurait une structure TexteDeBase comme superclasse avec Label et textbox
/// Comme sous-classe.  Ceci dit je suis tr�s serr� dans le temps, alors je livre
/// vite quelque chose qui marche.
/// </summary>
class textbox : public text
{
	//DOC DES M�THODES DANS LE .CPP
public:
	// Constructors
	textbox();
	textbox(sf::String placeholder_text, const Vector2f position, style_text style);

	// Mutators
	void insert_text(String text_to_insert);
	void add_text(String text_to_add);
	void add_char(const char char_to_add);
	void remove_char();
	void selected();
	void unselected();
	bool is_selected() const;
	void draw(sf::RenderWindow& main_win) const;
	void set_placeholder_text(sf::String placeholder_text);
	void set_position(Vector2f new_position);

	// Accessors
	int get_box_length();

private:
	void visual_adjustments();
	/// <summary>
	/// Limite de caract�res que notre textbox tol�re.  Mettez 1 de limit par 20 pixels de largeur de votre box_
	/// Ainsi si vous entrez que des caract�res larges (comme W par exemple), tout va entrer
	/// </summary>
	int limit_;
	/// <summary>
	/// Graphiquement, la textbox est un simple rectangle.
	/// </summary>
	RectangleShape box_;
	text placeholder_text_;
};
