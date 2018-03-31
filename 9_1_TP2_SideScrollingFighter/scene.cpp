#include "scene.h"
#include <string>
#include <fstream>	
#include "game.h"
#include <vector>

scene::scene()
{
}

bool scene::load_scene(const char scene_path[], std::vector<saw>& saws, std::vector<spike_trap>& spike_traps, std::vector<skeleton>& skeletons, std::vector<tile>& tiles, shuriken_spawner& shuriken_spawner_)
{
	//Load map
	{
		std::ifstream ifs(scene_path);
		if (ifs.is_open()) // Code reference: https://stackoverflow.com/questions/30475091/putting-text-file-content-into-a-2d-array
		{
			for (size_t y = 0; y < scene_height; ++y)
			{
				std::string line;
				if (getline(ifs, line))
				{
					for (size_t x = 0; x < scene_width; ++x)
					{
						map_[y][x] = line[x] - '0';
					}
				}
			}
		}
		else
		{
			return false;
		}
	}

	// Create Scene Objects
	for (size_t x = 0; x < scene_width; x++)
	{
		for (size_t y = 0; y < scene_height; y++)
		{
			if (map_[y][x] == 1)
			{
				tiles.push_back(tile(Vector2f(x * game::grid_size, y * game::grid_size), empty));
				tiles.back().visual_adjustments();
				tiles.back().set_texture(*map_, scene_width, scene_height);
				//tiles_.back().setColor(sf::Color(255, 172, 109));
			}
			if(map_[y][x] == 9)
			{
				shuriken_spawner_.set_position(Vector2f(x * game::grid_size, y * game::grid_size));
				shuriken_spawner_.visual_adjustments();
				shuriken_spawner_.set_textures();
			}
			if(map_[y][x] == 2)
			{
				skeletons.push_back(skeleton(Vector2f(x * game::grid_size, y * game::grid_size - 32), 1.5f, rand() % 1));
				skeletons.back().visual_adjustments();
				skeletons.back().set_texture();
			}
			if(map_[y][x] == 3)
			{
				int top = map_[y - 1][x];
				int left = map_[y][x-1];
				int bottom = map_[y + 1][x];
				int right = map_[y][x + 1];

				spike_traps.push_back(Vector2f(x * game::grid_size, y * game::grid_size));
				spike_traps.back().visual_adjustments();
				spike_traps.back().set_textures(*map_, scene_width, scene_height, top ,bottom,left,right);
			}
			if(map_[y][x] == 4) // 4 = start, 5 = path, 6 = end
			{
				auto searching_for_end = true;
				int last_y = y;
				int last_x = x;
				int y2 = y;
				int x2 = x;
				// Search until the end of the path is found:
				while(searching_for_end)
				{
					// Check up
					if(y2 - 1 != last_y /* Make sure we never go backwards */ && 
						(map_[y2 - 1][x2] == 5 || map_[y2 - 1][x2] == 6))
					{
						if (map_[y2 - 1][x2] == 5) { last_y = y2; last_x = x2; y2 -= 1; }
						if (map_[y2 - 1][x2] == 6) { y2 -= 1; searching_for_end = false; }
					}
					// Check down
					if (y2 + 1 != last_y /* Make sure we never go backwards */ &&
						(map_[y2 + 1][x2] == 5 || map_[y2 + 1][x2] == 6))
					{
						if (map_[y2 + 1][x2] == 5) { last_y = y2; last_x = x2; y2 += 1; }
						if (map_[y2 + 1][x2] == 6) { y2 += 1; searching_for_end = false; }
					}
					// Check left
					if (x2 - 1 != last_x /* Make sure we never go backwards */ &&
						(map_[y2][x2 - 1] == 5 || map_[y2][x2 - 1] == 6))
					{
						if (map_[y2][x2 - 1] == 5) { last_y = y2; last_x = x2; x2 -= 1; }
						if (map_[y2][x2 - 1] == 6) { x2 -= 1; searching_for_end = false; }
					}
					// Check right
					if (x2 + 1 != last_x /* Make sure we never go backwards */ &&
						(map_[y2][x2 + 1] == 5 || map_[y2][x2 + 1] == 6))
					{
						if (map_[y2][x2 + 1] == 5) { last_y = y2; last_x = x2; x2 += 1; }
						if (map_[y2][x2 + 1] == 6) { x2 += 1; searching_for_end = false; }
					}
				}
				saws.push_back(saw(
					Vector2f(x * game::grid_size, y * game::grid_size),
					Vector2f(x2 * game::grid_size, y2 * game::grid_size),
				3));
				saws.back().visual_adjustments();
				saws.back().set_texture();
			}
		}
	}
	return true;
}

