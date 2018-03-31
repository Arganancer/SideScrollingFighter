#ifndef SAW_H
#define SAW_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "npc.h"

class saw : public npc
{
public:
	saw(Vector2f start_tile, Vector2f end_tile, float speed);

	/// <summary>
	/// Initialise les textures statiques du personnage.
	/// </summary>
	/// <returns>Retourne vrai ou faux, dépendant du chargement des textures.</returns>
	static bool load_textures(const char texture_path[]);

	void visual_adjustments();
	void set_texture();
	void update();

	bool contains(Vector2f point) const;

private:
	static Texture texture_;
	Vector2f start_position_;
	Vector2f end_position_;
	bool is_moving_towards_end_pos_;
	Vector2f center_of_saw_;
};

#endif
