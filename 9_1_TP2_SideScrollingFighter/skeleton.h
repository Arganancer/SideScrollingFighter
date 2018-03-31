#ifndef SKELETON_H
#define SKELETON_H
#include "npc.h"

class skeleton : public npc
{
public:
	skeleton(Vector2f position, float speed, bool is_moving_left);
	static bool load_textures(const char skeleton_texture_path[], const char texture_blank_path[]);
	void visual_adjustments();
	void set_texture();
	void update();
	void turn_around();
	void check_hero_is_in_proximity(Vector2f hero_position);
	bool skeleton::get_attack_intersects_movable(movable movable);
	void draw(RenderWindow& main_win);

private:
	int attack_delay_;
	int frames_since_started_attacking_;
	int attack_rate_;
	int frames_since_last_attack_;
	bool skeleton_is_moving_left_;
	bool is_attacking_;
	FloatRect attack_hit_box_;
	bool attack_hit_box_is_active_;
	bool attack_is_resolving_;
	int hit_box_active_frames_;
	int frames_since_hit_box_became_active_;

	int idle_counter_;
	bool is_idle_;

	int current_frame_;
	int current_anim_;
	int nb_frames_since_last_change_;

	static Texture texture_blank_;
	Sprite character_sprite_;
	static Texture texture_character_;
};

#endif