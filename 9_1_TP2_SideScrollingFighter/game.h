#pragma once

#include <SFML/Graphics.hpp>
#include "input_manager.h"
#include "player_character.h"
#include "scene.h"
#include "shuriken.h"
#include "skeleton.h"

using namespace sf;

class game
{
public:
	enum game_state
	{
		victory_screen,
		defeat_screen,
		exiting,
		paused,
		main_menu,
		singleplayer,
		coop,
		vs,
	};

	game();
	int run();

	static const int grid_size = 32;
	static const int view_width = 1920;
	static const int view_height = 1080;

	static game_state get_current_game_state();
	static int get_score();

private:

	/// <summary>
	/// Respawns the specified hero.
	/// </summary>
	/// <param name="respawning_hero">The respawning hero.</param>
	void respawn(player_character * respawning_hero) const;

	/// <summary>
	/// Initializes this instance.
	/// </summary>
	/// <returns></returns>
	bool init();

	/// <summary>
	/// Gets the inputs.
	/// </summary>
	void get_inputs();

	/// <summary>
	/// Updates this instance.
	/// </summary>
	void update();

	/// <summary>
	/// Draws this instance.
	/// </summary>
	void draw();

	/// <summary>
	/// Movables the and tile collision detection.
	/// </summary>
	/// <param name="movable">The movable.</param>
	void movable_and_tile_collision_detection(movable * movable) const;
	void movable_out_of_bounds(movable * movable);
	bool load_scene();

	bool character_outofbounds_left_;
	bool character_outofbounds_right_;
	bool load_new_level_;
	std::string scenes_[3];
	Vector2f current_respawn_point_;
	Vector2f default_respawn_point_;
	scene scene_;
	int current_scene_;

	float nb_of_frames_since_game_started_;
	int lives_remaining_;
	const int max_lives_ = 10;
	bool game_state_is_defaulted_;

	static int score_;

	std::vector<tile> tiles_;
	std::vector<player_character> heros_;
	std::vector<skeleton> skeletons_;
	std::vector<spike_trap> spike_traps_;
	std::vector<saw> saws_;
	shuriken_spawner shuriken_spawner_;

	shuriken shurikens_[50];

	int view_x_pos_last_frame_;
	RenderWindow main_win_;
	View view_game_;
	View view_menu_;
	Vector2f view_current_center_;
	Event event_;

	static game_state current_game_state_;
};