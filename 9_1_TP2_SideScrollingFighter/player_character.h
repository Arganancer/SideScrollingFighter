#pragma once
#include "character.h"

class player_character : public character
{
public:
	// Overload Constructor
	explicit player_character(Vector2f position, int player_id);

	// Mutators
	/// <summary>
	/// Initialise les textures statiques du personnage.
	/// </summary>
	/// <returns>Retourne vrai ou faux, dépendant du chargement des textures.</returns>
	static bool load_textures(const char character_texture_path[], const char texture_blank_path[]);
	void visual_adjustments();
	void set_texture();
	void update(RenderWindow& main_win);
	void jump(Vector2f left_joystick_pos);
	void start_respawn_delay();
	void update_respawn_delay();
	bool get_is_respawning();
	bool get_is_active();
	void set_is_active(bool is_active);
	int get_player_id();
	bool get_shuriken_button_pressed();
	void set_shuriken_button_pressed(bool shuriken_button_pressed);
	bool get_character_facing_left();
	void set_has_shuriken(bool has_shurikens);
	bool get_has_shuriken();
	void draw(RenderWindow& main_win);

private:
	int player_id_;
	bool is_active_;
	bool is_respawning_;
	int respawn_delay_;
	int respawn_delay_remaining_;
	int fire_rate_;
	int fire_rate_counter_;

	static Texture texture_blank_;
	Sprite character_sprite_;
	static Texture texture_character_;

	// Physics Variables
	float jump_acceleration_;
	Vector2f max_sprint_velocity_;
	Vector2f max_regular_velocity_;

	// Action Variables
	bool shuriken_button_pressed_;
	bool second_jump_used_;
	bool preparing_to_jump_;
	bool jump_button_still_held_;
	int nb_of_frames_that_jump_is_held_;

	// Animation Variables
	int jump_animation_frames_;
	bool animation_facing_left_;
	int nb_frames_since_last_change_;
	int current_frame_;
	int current_anim_;
};
