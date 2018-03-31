#pragma once
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;

class entity : public sf::Sprite
{
public:
	// Overload Constructor
	explicit entity(Vector2f position);

	// Accessors
	/// <summary>
	/// V�rifie si le sprite actuel croise un sprite pass� en param�tre.
	/// </summary>
	/// <param name="drawable">Le deuxi�me sprite � v�rifier.</param>
	/// <returns>Retourne vrai si les formes se croisent.</returns>
	bool intersects(Sprite* sprite) const;

	bool contains(Vector2f point) const;

	// Mutators
};
