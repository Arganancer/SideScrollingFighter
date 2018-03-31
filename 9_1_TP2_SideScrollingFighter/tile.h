#ifndef TILE_H
#define TILE_H
#include "entity.h"

const enum tile_type
{
	empty,
	platform,
};

class tile : public entity
{
public:	
	// Overload Constructor
	/// <summary>
	/// Initialise une nouvelle instance de la classe <see cref="tile"/>.
	/// </summary>
	/// <param name="position">La position.</param>
	/// <param name="tile">Le type de la tuile.</param>
	/// <param name="size">La taille de la tuile.</param>
	tile(Vector2f position, tile_type tile);
	
	// Mutators
	/// <summary>
	/// Initialise les textures statiques des tuiles.
	/// </summary>
	/// <returns>Retourne vrai ou faux, dépendant du chargement des textures.</returns>
	static bool load_textures(const char texture_path[]);

	void visual_adjustments();

	/// <summary>
	/// Définit la texture de la tuile.
	/// </summary>
	void set_texture(int *map, int scene_width, int scene_height);

	/// <summary>
	/// Définit le type de la tuile.
	/// </summary>
	/// <param name="tile">Le type de tuile.</param>
	void set_tile_type(tile_type tile);

	// Accessors
	/// <summary>
	/// Retourne le type de tuile.
	/// </summary>
	/// <returns>Le type de tuile.</returns>
	tile_type get_tile_type() const;

private:
	static Texture texture_;
	IntRect* int_rects_rock_tiles_;
	tile_type tile_type_;
	Vector2f position_;
};

#endif
