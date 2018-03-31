#ifndef SHURIKEN_H
#define SHURIKEN_H
#include <string>
#include "movable.h"

class shuriken : public movable
{
public:
	shuriken();
	void update();
	static bool load_textures(const std::string texture_path);
	void set_textures();
	void visual_adjustments();
	bool contains(Vector2f point);
	void shoot(Vector2f position, int id_player, Vector2f velocity, bool is_facing_left);


	//mutators
	void set_position(Vector2f position);
	void set_is_alive(bool isactive);
	void set_shuriken_player_id(int player_id);
	void set_initial_velocity(Vector2f velocity);
	//accessors
	bool get_is_alive();
	int get_shuriken_player_id();
private:
	static Texture texture_;

	int shuriken_player_id_;
	Vector2f center_of_shuriken_;
};
#endif
