#pragma once
#include "tile.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "saw.h"
#include "spike_trap.h"
#include "shuriken_spawner.h"
#include "skeleton.h"

class scene
{
public:
	scene();
	bool load_scene(const char scene_path[], std::vector<saw>& saws, std::vector<spike_trap>& spike_traps, std::vector<skeleton>& skeletons, std::vector<tile>& tiles, shuriken_spawner& shuriken_spawner_);
	


	static const int scene_width = 180;
	static const int scene_height = 33;

private:
	int map_[33][180];

};
