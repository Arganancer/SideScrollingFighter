#include "saw.h"

Texture saw::texture_;

saw::saw(Vector2f start_position, Vector2f end_position, float speed) : npc(start_position, speed)
{
	is_moving_towards_end_pos_ = true;
	start_position_ = start_position;
	end_position_ = end_position;
}

bool saw::load_textures(const char texture_path[])
{
	if (!texture_.loadFromFile(texture_path)) {
		return false;
	}
	return true;
}

void saw::set_texture()
{
	setTexture(texture_);
	setTextureRect(int_rects_character_[0][0]);
}

void saw::visual_adjustments()
{
	const auto nb_character_frames = 1;
	const auto nb_character_anims = 1;

	// Adjust character bounding box.
	const int width = texture_.getSize().x / nb_character_frames;
	const int height = texture_.getSize().y / nb_character_anims;

	int_rects_character_ = new IntRect*[nb_character_anims];
	for (size_t i = 0; i < nb_character_anims; i++)
	{
		int_rects_character_[i] = new IntRect[nb_character_frames];
		for (size_t j = 0; j < nb_character_frames; j++)
		{
			int_rects_character_[i][j].left = width * j;
			int_rects_character_[i][j].top = height * i;
			int_rects_character_[i][j].width = width;
			int_rects_character_[i][j].height = height;
		}
	}

	// Adjust collision box
	center_of_saw_ = Vector2f(width/2, height/2);
}

void saw::update()
{
	const float distance_between_start_and_end = sqrt(pow(start_position_.x - end_position_.x, 2) +
		pow(start_position_.y - end_position_.y, 2));

	float temp_angle;
	if(is_moving_towards_end_pos_)
	{
		temp_angle = atan2(end_position_.y - getPosition().y, end_position_.x - getPosition().x);

		const float distance_between_start_and_saw = sqrt(pow(start_position_.x - getPosition().x, 2) +
			pow(start_position_.y - getPosition().y, 2));
		if(distance_between_start_and_end <= distance_between_start_and_saw)
		{
			is_moving_towards_end_pos_ = false;
		}
	}
	else
	{
		temp_angle = atan2(start_position_.y - getPosition().y, start_position_.x - getPosition().x);

		const float distance_between_end_and_saw = sqrt(pow(end_position_.x - getPosition().x, 2) +
			pow(end_position_.y - getPosition().y, 2));
		if (distance_between_start_and_end <= distance_between_end_and_saw)
		{
			is_moving_towards_end_pos_ = true;
		}
	}
	Vector2f direction = Vector2f(cos(temp_angle), sin(temp_angle));
	setPosition(getPosition() + direction * speed_);
}

bool saw::contains(Vector2f point) const
{
	const float distance = sqrt(pow(point.x - (getPosition().x + center_of_saw_.x), 2) +
		pow(point.y - (getPosition().y + center_of_saw_.y), 2));
	if(getGlobalBounds().width/2 >= distance)
	{
		return true;
	}
	return false;
}
