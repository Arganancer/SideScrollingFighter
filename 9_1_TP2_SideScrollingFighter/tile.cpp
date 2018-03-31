#include "tile.h"
#include <SFML/Graphics/Texture.hpp>

Texture tile::texture_;

tile::tile(Vector2f position, tile_type tile) : entity(position)
{
	position_ = Vector2f(position.x/32, position.y/32);
	tile_type_ = tile;
    setPosition(Vector2f(position));
}

bool tile::load_textures(const char texture_path[])
{
	if (!texture_.loadFromFile(texture_path)) {
		return false;
	}
	return true;
}

void tile::visual_adjustments()
{
	const auto nb_of_rock_frames = 16;

	const int width = texture_.getSize().x / nb_of_rock_frames;
	const int height = texture_.getSize().y;
	int_rects_rock_tiles_ = new IntRect[nb_of_rock_frames];
	for (size_t i = 0; i < nb_of_rock_frames; i++)
	{
		int_rects_rock_tiles_[i].left = width * i;
		int_rects_rock_tiles_[i].top = 0;
		int_rects_rock_tiles_[i].width = width;
		int_rects_rock_tiles_[i].height = height;
	}
}

void tile::set_texture(int *map, int scene_width, int scene_height)
{
	tile_type up;
	tile_type down;
	tile_type left;
	tile_type right;
	if (position_.x == 0) { left = platform; }
	else { left = tile_type(*(map+int(position_.y)*scene_width + int(position_.x) - 1)); }
	if(position_.x == scene_width - 1) { right = platform; }
	else { right = tile_type(*(map + int(position_.y)*scene_width + int(position_.x + 1))); }
	if(position_.y == 0) { up = platform; }
	else { up = tile_type(*(map + int(position_.y-1)*scene_width + int(position_.x))); }
	if(position_.y == scene_height - 1) { down = platform; }
	else { down = tile_type(*(map + int(position_.y+1)*scene_width + int(position_.x))); }

	setTexture(texture_);

	// All empty
	if(up != platform && down != platform && left != platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[1]);
	}

	// One platform
	else if (up == platform && down != platform && left != platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[13]);
	}
	else if (up != platform && down == platform && left != platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[15]);
	}
	else if (up != platform && down != platform && left == platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[12]);
	}
	else if (up != platform && down != platform && left != platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[14]);
	}

	// Two platforms side by side
	else if (up == platform && down != platform && left == platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[9]);
	}
	else if (up != platform && down == platform && left == platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[8]);
	}
	else if (up != platform && down == platform && left != platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[11]);
	}
	else if (up == platform && down != platform && left != platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[10]);
	}

	// Two platforms parallel
	else if (up == platform && down == platform && left != platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[3]);
	}
	else if (up != platform && down != platform && left == platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[2]);
	}

	// Three platforms
	else if (up == platform && down == platform && left == platform && right != platform)
	{
		setTextureRect(int_rects_rock_tiles_[5]);
	}
	else if (up == platform && down == platform && left != platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[7]);
	}
	else if (up == platform && down != platform && left == platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[6]);
	}
	else if (up != platform && down == platform && left == platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[4]);
	}

	// All full
	else if (up == platform && down == platform && left == platform && right == platform)
	{
		setTextureRect(int_rects_rock_tiles_[0]);
	}
}

void tile::set_tile_type(tile_type tile)
{
	//TODO: Evaluate if this will be necessary.
}

tile_type tile::get_tile_type() const
{
	return tile_type_;
}
