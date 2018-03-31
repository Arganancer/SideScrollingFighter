#include "spike_trap.h"

Texture spike_trap::texture_;

spike_trap::spike_trap(Vector2f position): npc(position, 0), current_anim_(0)
{
	position_ = position;
	is_triggered_ = false;
	is_alive_ = false;
	delay_counter_ = 0;
	delay_ = 60;
}

bool spike_trap::load_textures(const std::string texture_path)
{
	if (!texture_.loadFromFile(texture_path)) {
		return false;
	}
	return true;
}

void spike_trap::set_textures(int *map, int scene_width, int scene_height, int top, int bottom, int left, int right)
{
	setTexture(texture_);
	if(bottom ==1)
	{
		//Spike trap vers le haut
		setTextureRect(int_rects_character_[0][0]);
		inactive_hitbox_.left = getPosition().x + 2;
		inactive_hitbox_.top = getPosition().y + 30;
		inactive_hitbox_.width = getGlobalBounds().width - 4;
		inactive_hitbox_.height = 4;
		current_anim_ = 0;
	}
	else if( left ==1)
	{
		//Spike trap de gauche a droite
		setTextureRect(int_rects_character_[1][0]);
		inactive_hitbox_.left = getPosition().x - 2;
		inactive_hitbox_.top = getPosition().y + 2;
		inactive_hitbox_.width = 4;
		inactive_hitbox_.height = getGlobalBounds().height - 4;
		current_anim_ = 1;
	}
	else if(right ==1)
	{
		//Spike trap de droite a gauche
		setTextureRect(int_rects_character_[3][0]);
		inactive_hitbox_.left = getPosition().x + 30;
		inactive_hitbox_.top = getPosition().y + 2;
		inactive_hitbox_.width = 4;
		inactive_hitbox_.height = getGlobalBounds().height - 4;
		current_anim_ = 3;
	}
	else if(top ==1)
	{
		//Spike trap de haut en bas
		setTextureRect(int_rects_character_[2][0]);
		inactive_hitbox_.left = getPosition().x + 2;
		inactive_hitbox_.top = getPosition().y - 2;
		inactive_hitbox_.width = getGlobalBounds().width - 4;
		inactive_hitbox_.height = 4;
		current_anim_ = 2;
	}
	else
	{
		//spike trap du backgroud.
		setTextureRect(int_rects_character_[4][0]);
		inactive_hitbox_ = getGlobalBounds();
		current_anim_ = 4;
	}
}


void spike_trap::visual_adjustments()
{
	const auto nb_character_frames = 2;
	const auto nb_character_anims = 5;

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

}

void spike_trap::update()
{
	if (is_triggered_ == true)
	{
		delay_counter_++;
	}
	if (delay_counter_ == delay_)
	{
		setTextureRect(int_rects_character_[current_anim_][1]);
		is_alive_ = true;
	}
	else if (delay_counter_ > 180)
	{
		setTextureRect(int_rects_character_[current_anim_][0]);
		is_alive_ = false;
		is_triggered_ = false;
		delay_counter_ = 0;
	}
}


bool spike_trap::contains(Vector2f point) 
{
	if(is_alive_ == false)
	{
		if (inactive_hitbox_.contains(point) == true)
		{
			is_triggered_ = true;
		}
		return false;
	}
	return getGlobalBounds().contains(point);
}

