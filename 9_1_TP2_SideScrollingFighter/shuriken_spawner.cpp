#include "shuriken_spawner.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


 Texture shuriken_spawner::texture_;


shuriken_spawner::shuriken_spawner() : entity(Vector2f(0,0))
{
	is_alive_ = true;
}


void shuriken_spawner::set_is_alive(bool is_alive)
{
	is_alive_ = is_alive;
}


bool shuriken_spawner::get_is_alive() const 
{
	return  is_alive_;
}



bool shuriken_spawner::load_textures(const std::string texture_path)
{
	if (!texture_.loadFromFile(texture_path)) {
		return false;
	}
	return true;
}


void shuriken_spawner::set_textures()
{
	setTexture(texture_);
}

bool shuriken_spawner::contains(Vector2f point)
{
	//checks the distance between the two sprites as a circle.
	const float distance = sqrt(pow(point.x - (getPosition().x + center_of_spawner.x), 2) +
		pow(point.y - (getPosition().y + center_of_spawner.y), 2));
	if (getGlobalBounds().width*5 / 2 >= distance)
	{
		is_alive_ = false;
		return true;
	}
	return false;
}

void shuriken_spawner::visual_adjustments()
{

	//Ajustement des animations 
	const auto nb_shuriken_frames = 1;
	const auto nb_shuriken_anims = 1;

	// Adjust character bounding box.
	const int width = texture_.getSize().x / nb_shuriken_frames;
	const int height = texture_.getSize().y / nb_shuriken_anims;

	int_rects_shuriken_spawner = new IntRect*[nb_shuriken_anims];
	for (size_t i = 0; i < nb_shuriken_anims; i++)
	{
		int_rects_shuriken_spawner[i] = new IntRect[nb_shuriken_frames];
		for (size_t j = 0; j < nb_shuriken_frames; j++)
		{
			int_rects_shuriken_spawner[i][j].left = width * j;
			int_rects_shuriken_spawner[i][j].top = height * i;
			int_rects_shuriken_spawner[i][j].width = width;
			int_rects_shuriken_spawner[i][j].height = height;
		}
	}
}


Vector2f shuriken_spawner::get_position()
{
	return getPosition();
}



void shuriken_spawner::set_position(Vector2f position)
{
	setPosition(position);
}

void shuriken_spawner::update()
{

}

int shuriken_spawner::get_player_id()
{
	return  player_id_;
}

void shuriken_spawner::set_player_id(int player_id)
{
	player_id_ = player_id;
}

