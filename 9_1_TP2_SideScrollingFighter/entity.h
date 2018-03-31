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
	/// Vérifie si le sprite actuel croise un sprite passé en paramètre.
	/// </summary>
	/// <param name="drawable">Le deuxième sprite à vérifier.</param>
	/// <returns>Retourne vrai si les formes se croisent.</returns>
	bool intersects(Sprite* sprite) const;

	bool contains(Vector2f point) const;

	// Mutators
};
