#include "skeleton.h"

Texture skeleton::texture_character_;
Texture skeleton::texture_blank_;

skeleton::skeleton(Vector2f position, float speed, bool is_moving_left) : npc(position, speed)
{
	max_velocity_.x = 5;
	frames_since_last_attack_ = 0;
	frames_since_started_attacking_ = 0;
	current_anim_ = 0;
	current_frame_ = 0;
	attack_rate_ = 90;
	attack_delay_ = 30;
	skeleton_is_moving_left_ = is_moving_left;
	is_attacking_ = false;
	attack_hit_box_is_active_ = false;
	hit_box_active_frames_ = 10;
	frames_since_hit_box_became_active_ = 0;
	idle_counter_ = 0;
	is_idle_ = false;
	nb_frames_since_last_change_ = 0;
	attack_is_resolving_ = false;
}

bool skeleton::load_textures(const char skeleton_texture_path[], const char texture_blank_path[])
{
	if (!texture_character_.loadFromFile(skeleton_texture_path)) {
		return false;
	}
	if (!texture_blank_.loadFromFile(texture_blank_path)) {
		return false;
	}
	return true;
}

void skeleton::visual_adjustments()
{
	// Adjust character textures.
	const auto nb_character_frames = 10;
	const auto nb_character_anims = 8;
	int width = texture_character_.getSize().x / nb_character_frames;
	int height = texture_character_.getSize().y / nb_character_anims;

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
	width = 32;
	height = 64;
	// Adjust character collision points.
	top_left_point_ = Vector2f(width*0.25f, 0);
	top_right_point_ = Vector2f(width*0.75f, 0);
	left_upper_point_ = Vector2f(0, height*0.25f);
	left_lower_point_ = Vector2f(0, height*0.75f);
	bottom_left_point_ = Vector2f(width*0.25f, height);
	bottom_right_point_ = Vector2f(width*0.75f, height);
	right_upper_point_ = Vector2f(width, height*0.25f);
	right_lower_point_ = Vector2f(width, height*0.75f);

	attack_hit_box_.width = 64;
	attack_hit_box_.height = 64;
}

void skeleton::set_texture()
{
	setTexture(texture_blank_);
	character_sprite_.setTexture(texture_character_);
	character_sprite_.setTextureRect(int_rects_character_[0][0]);
	character_sprite_.setOrigin(character_sprite_.getGlobalBounds().width/2 - 16, character_sprite_.getGlobalBounds().height - 64);
}

void skeleton::update()
{
	if(is_colliding_wall_left_ || is_colliding_wall_right_)
	{
		turn_around();
	}

	// Update attack variables
	if (frames_since_last_attack_ < attack_rate_)
	{
		++frames_since_last_attack_;
	}
	if (is_attacking_)
	{
		if (is_attacking_ && !attack_hit_box_is_active_ && !attack_is_resolving_)
		{
			if (++frames_since_started_attacking_ >= attack_delay_)
			{
				attack_hit_box_is_active_ = true;
			}
		}
		if (attack_hit_box_is_active_ && !attack_is_resolving_)
		{
			attack_hit_box_.top = getPosition().y;
			if (skeleton_is_moving_left_)
			{
				attack_hit_box_.left = getPosition().x - attack_hit_box_.width + getGlobalBounds().width / 2;
			}
			else
			{
				attack_hit_box_.left = getPosition().x + (getGlobalBounds().width/2);
			}
			if (++frames_since_hit_box_became_active_ >= hit_box_active_frames_)
			{
				attack_is_resolving_ = true;
				frames_since_hit_box_became_active_ = 0;
				attack_hit_box_is_active_ = false;
				frames_since_last_attack_ = 0;
				is_idle_ = true;
				idle_counter_ = rand() % 120 + 60;
			}
		}
	}
	else
	{
		// Update movement/idle state
		if (is_idle_)
		{
			if (--idle_counter_ <= 0)
			{
				is_idle_ = false;
				idle_counter_ = rand() % 240 + 60;
			}
		}
		else
		{
			if (--idle_counter_ <= 0)
			{
				is_idle_ = true;
				idle_counter_ = rand() % 240 + 60;
			}
			else if (skeleton_is_moving_left_)
			{
				velocity_.x = -speed_;
				move();
			}
			else
			{
				velocity_.x = speed_;
				move();
			}
		}
	}
	character_sprite_.setPosition(getPosition());

	// Update animations
	if (skeleton_is_moving_left_) 
	{
		if (is_attacking_) { current_anim_ = 5; }
		else if(is_idle_) { current_anim_ = 1; }
		else { current_anim_ = 3; }
	}
	else 
	{
		if (is_attacking_) { current_anim_ = 4; }
		else if (is_idle_) { current_anim_ = 0; }
		else { current_anim_ = 2; }
	}
	if (++nb_frames_since_last_change_ == 6) 
	{
		if (current_frame_ < 9) { current_frame_++; }
		else
		{
			if(is_attacking_)
			{
				is_attacking_ = false;
				attack_is_resolving_ = false;
			}
			current_frame_ = 0;
		}
		nb_frames_since_last_change_ = 0;
		character_sprite_.setTextureRect(int_rects_character_[current_anim_][current_frame_]);
	}

}

void skeleton::turn_around()
{
	skeleton_is_moving_left_ = !skeleton_is_moving_left_;
}


void skeleton::check_hero_is_in_proximity(Vector2f hero_position)
{
	if(!is_attacking_ && 
		frames_since_last_attack_ >= attack_rate_ &&
		abs(hero_position.y - getPosition().y) < 64 
		&& abs(hero_position.x - getPosition().x) < 64)
	{
		if(getPosition().x - hero_position.x > 0)
		{
			skeleton_is_moving_left_ = true;
		}
		else
		{
			skeleton_is_moving_left_ = false;
		}
		is_attacking_ = true;
		current_frame_ = 0;
		frames_since_started_attacking_ = 0;
	}
}

bool skeleton::get_attack_intersects_movable(movable movable)
{
	if (attack_hit_box_is_active_)
	{
		if (attack_hit_box_.intersects(movable.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

void skeleton::draw(RenderWindow& main_win)
{
	//// TODO: Remove (this was for testing the collision hit-box when the skeleton was attacking.
	//if (attack_hit_box_is_active_)
	//{
	//	RectangleShape shapeHitBoxTest = RectangleShape(Vector2f(attack_hit_box_.width, attack_hit_box_.height));
	//	shapeHitBoxTest.setPosition(attack_hit_box_.left, attack_hit_box_.top);
	//	shapeHitBoxTest.setFillColor(Color::Red);
	//	main_win.draw(shapeHitBoxTest);
	//}
	main_win.draw(character_sprite_);
}