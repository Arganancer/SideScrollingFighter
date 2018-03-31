#include "player_character.h"
#include "input_manager.h"
#include <iostream>

Texture player_character::texture_character_;
Texture player_character::texture_blank_;

player_character::player_character(Vector2f position, int player_id) : character(position, 10), respawn_delay_remaining_(0)
{
	// Animation Variables
	current_anim_ = 0;
	current_frame_ = 0;
	nb_frames_since_last_change_ = 0;
	animation_facing_left_ = false;
	jump_animation_frames_ = 0;

	// Character state variables
	player_id_ = player_id;
	is_respawning_ = false;
	respawn_delay_ = 120;
	fire_rate_ = 60;
	fire_rate_counter_ = 60;
	shuriken_button_pressed_ = false;
	fire_rate_counter_ = 0;
	shuriken_button_pressed_ = false;

	// Physics variables
	velocity_ = Vector2f(0, 0);
	max_regular_velocity_ = Vector2f(6, 10);
	max_sprint_velocity_ = Vector2f(9, 12);
	max_velocity_ = max_regular_velocity_;
	acceleration_x_ = 0.9f;
	deceleration_x_ = 0.1f;
	jump_acceleration_ = 5;
	second_jump_used_ = false;
	nb_of_frames_that_jump_is_held_ = 0;
	preparing_to_jump_ = false;
	jump_button_still_held_ = false;
}

bool player_character::load_textures(const char character_texture_path[], const char blank[])
{
	if (!texture_character_.loadFromFile(character_texture_path)) {
		return false;
	}
	if (!texture_blank_.loadFromFile(blank)) {
		return false;
	}
	return true;
}

void player_character::visual_adjustments()
{
	// Adjust character textures.
	const auto nb_character_frames = 8;
	const auto nb_character_anims = 6;
	int width = texture_character_.getSize().x / nb_character_frames;
	const int height = texture_character_.getSize().y / nb_character_anims;

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
	// Adjust character collision points.
	top_left_point_ = Vector2f(width*0.25f, 0);
	top_right_point_ = Vector2f(width*0.75f, 0);
	left_upper_point_ = Vector2f(0, height*0.25f);
	left_lower_point_ = Vector2f(0, height*0.75f);
	bottom_left_point_ = Vector2f(width*0.25f, height);
	bottom_right_point_ = Vector2f(width*0.75f, height);
	right_upper_point_ = Vector2f(width, height*0.25f);
	right_lower_point_ = Vector2f(width, height*0.75f);
}

void player_character::set_texture()
{
	setTexture(texture_blank_);
	character_sprite_.setTexture(texture_character_);
	character_sprite_.setTextureRect(int_rects_character_[0][0]);
	character_sprite_.setOrigin(character_sprite_.getGlobalBounds().width / 2 - 16, 0);
}

void player_character::update(RenderWindow& main_win)
{
	fire_rate_counter_++;
	if (input_manager::get_input_manager()->get_button_is_pressed(1, player_id_) == true && has_shuriken_ == true)
	{
		if (fire_rate_counter_ >= fire_rate_)
		{
			shuriken_button_pressed_ = true;
			fire_rate_counter_ = 0;
		}
	}
	if(input_manager::get_input_manager()->get_left_trigger_pos(player_id_) > 20)
	{
		max_velocity_ = max_sprint_velocity_;
	}
	else
	{
		max_velocity_ = max_regular_velocity_;
	}
	if(is_on_platform_ && second_jump_used_)
	{
		second_jump_used_ = false;
	}
	float modified_gravity = gravity_;
	if (is_colliding_wall_left_ || is_colliding_wall_right_)
	{
		modified_gravity /= 2;
		if (velocity_.y > 0)
		{
			max_velocity_.y = 5;
		}
	}
	int noise_value = 30;
	// Get controller state:
	Vector2f left_joystick_pos = input_manager::get_input_manager()->get_left_joystick_pos(player_id_);
	float left_joystick_angle = atan2(left_joystick_pos.y, left_joystick_pos.x);
	Vector2f x_and_y_angle;
	if(left_joystick_pos.x <= noise_value && left_joystick_pos.y <= noise_value)
	{
		x_and_y_angle = Vector2f(0, -1);
	}
	else
	{
		x_and_y_angle = Vector2f(cos(left_joystick_angle), sin(left_joystick_angle));
	}
	//float right_joystick_angle = atan2(right_joystick_pos.y, right_joystick_pos.x) * 180 / 3.14f;

	// PHYSICS AND INPUTS:
	// Check to see if the jump key has been pressed.
	if (!input_manager::get_input_manager()->get_button_is_pressed(0, player_id_))
	{
		jump_button_still_held_ = false;
		preparing_to_jump_ = false;
		nb_of_frames_that_jump_is_held_ = 0;
	}
	if ((input_manager::get_input_manager()->get_button_is_pressed(0, player_id_) || preparing_to_jump_) && !jump_button_still_held_)
	{
		if (is_on_platform_ || preparing_to_jump_)
		{
			preparing_to_jump_ = true;
			++nb_of_frames_that_jump_is_held_;
			jump(x_and_y_angle);
			if (nb_of_frames_that_jump_is_held_ >= 10)
			{
				jump_button_still_held_ = true;
				preparing_to_jump_ = false;
			}
		}
		else if(is_colliding_wall_left_)
		{
			jump(Vector2f(jump_acceleration_, jump_acceleration_));
		}
		else if(is_colliding_wall_right_)
		{
			jump(Vector2f(-jump_acceleration_, jump_acceleration_));
		}
		else
		{
			jump(x_and_y_angle);
		}
	}
	// Accelerate gravity.
	accelerate(Vector2f(0, modified_gravity));

	// Check to see if the horizontal movement is accelerated.
	if (abs(left_joystick_pos.x) > noise_value && abs(velocity_.x) < max_velocity_.x)
	{	
		if (is_on_platform_) 
		{
			if (abs(velocity_.x) < abs(max_velocity_.x * left_joystick_pos.x / 100.0f))
			{
				if (left_joystick_pos.x > 0 && velocity_.x < 0) // Turning around when moving right.
				{
					accelerate(Vector2f(deceleration_x_ * 7, 0));
				}
				else if (left_joystick_pos.x > 0 && velocity_.x < 0) // Turning around when moving left.
				{
					accelerate(Vector2f(-deceleration_x_ * 7, 0));
				}
				else
				{
					accelerate(Vector2f(acceleration_x_ * left_joystick_pos.x / 100.0f, 0));
				}
			}
		}
		else
		{
			accelerate(Vector2f(acceleration_x_ * left_joystick_pos.x / 100.0f, 0));
		}
	}
	// If neither left nor right has been pressed, the movement of the character deccelerates.
	else
	{
		float temp_deceleration_x = 0;
		if (is_on_platform_) // If character is on a platform, he decelerates faster than when he is in the air.
		{
			temp_deceleration_x = deceleration_x_ * 5;
		}
		else
		{
			temp_deceleration_x = deceleration_x_;
		}
		if (velocity_.x > 1.5f)
		{
			accelerate(Vector2f(-temp_deceleration_x, 0));
		}
		else if (velocity_.x < -1.5f)
		{
			accelerate(Vector2f(temp_deceleration_x, 0));
		}
		else
		{
			velocity_.x = 0;
		}
	}
	// Friction is applied to the character's speed.
	if (velocity_.x != 0)
	{
		velocity_.x *= friction_;
	}
	if (velocity_.y != 0)
	{
		velocity_.y *= friction_;
	}
	// After verifying all of the above, the character's trajectory is affected via the "move" method.
	move();
	character_sprite_.setPosition(getPosition());

	// The character's animation is updated to reflect the effects of inputs and physics.
	// Modify Animation
	if (velocity_.x > 0)
	{
		animation_facing_left_ = false;
	}
	else if (velocity_.x < 0)
	{
		animation_facing_left_ = true;
	}
	nb_frames_since_last_change_++;
			// OLD ANIMATION
			//if (!animation_facing_left_) {
			//	if (!is_on_platform_) {
			//		if(jump_animation_frames_ < 5) { current_anim_ = 4; }
			//		else { current_anim_ = 6; } }
			//	else if (velocity_.x >= 0.5f) { current_anim_ = 0; }
			//	else { current_anim_ = 2; }
			//}
			//else { 
			//	if (!is_on_platform_) {
			//		if (jump_animation_frames_ < 5) { current_anim_ = 5; }
			//		else { current_anim_ = 7; } }
			//	else if (velocity_.x <= -0.5f) { current_anim_ = 1; }
			//	else { current_anim_ = 3; } 
			//}
			//if(nb_frames_since_last_change_ == 5) {
			//	if(!is_on_platform_ && jump_animation_frames_ < 5) {
			//		if(jump_animation_frames_ == 0) {
			//			current_frame_ = 0; }
			//		jump_animation_frames_++;}
			//	if(current_frame_ < 5) { current_frame_++; }
			//	else { current_frame_ = 0; }
			//	nb_frames_since_last_change_ = 0;
			//	setTextureRect(int_rects_character_[current_anim_][current_frame_]);
			//}

	// NEW ANIMATION
	if (!animation_facing_left_) {
		if (velocity_.x >= 5.0f) { current_anim_ = 4; }
		else if (velocity_.x >= 0.5f) { current_anim_ = 2; }
		else { current_anim_ = 0; }
	}
	else {
		if (velocity_.x <= -5.0f) { current_anim_ = 5; }
		else if (velocity_.x <= -0.5f) { current_anim_ = 3; }
		else { current_anim_ = 1; }
	}
	if (nb_frames_since_last_change_ == 5) {
		if (current_frame_ < 7) { current_frame_++; }
		else { current_frame_ = 0; }
		nb_frames_since_last_change_ = 0;
		character_sprite_.setTextureRect(int_rects_character_[current_anim_][current_frame_]);
	}
}

void player_character::jump(Vector2f jump_acceleration)
{
	if (preparing_to_jump_)
	{
		float jump_acceleration_modifier = 0;
		if (nb_of_frames_that_jump_is_held_ <= 1)
		{
			jump_acceleration_modifier = jump_acceleration_;
		}
		else if (nb_of_frames_that_jump_is_held_ <= 4)
		{
			jump_acceleration_modifier = jump_acceleration_ / 4.0f;
		}
		else
		{
			jump_acceleration_modifier = jump_acceleration_ / 8.0f;
		}
		jump_animation_frames_ = 0;
		is_on_platform_ = false;
		accelerate(Vector2f(0, -jump_acceleration_modifier));
	}
	else if((is_colliding_wall_left_ || is_colliding_wall_right_) && !jump_button_still_held_)
	{
		max_velocity_.y = 10;
		is_colliding_wall_left_ = false;
		is_colliding_wall_right_ = false;
		kill_y_velocity();
		jump_button_still_held_ = true;
		accelerate(Vector2f(jump_acceleration.x *1.5f, -jump_acceleration.y *2.0f));
	}
	else if (!second_jump_used_ && !jump_button_still_held_)
	{
		kill_x_velocity();
		kill_y_velocity();
		jump_button_still_held_ = true;
		second_jump_used_ = true;
		accelerate(Vector2f(jump_acceleration.x * jump_acceleration_ * 2, jump_acceleration.y * jump_acceleration_ * 2));
	}
}

void player_character::start_respawn_delay()
{
	if (!is_respawning_)
	{
		is_respawning_ = true;
		respawn_delay_remaining_ = respawn_delay_;
	}
}

void player_character::update_respawn_delay()
{
	if(respawn_delay_remaining_ > 0)
	{
		--respawn_delay_remaining_;
	}
	else
	{
		is_respawning_ = false;
		is_alive_ = true;
	}
}

bool player_character::get_is_respawning()
{
	return is_respawning_;
}

bool player_character::get_is_active()
{
	return is_active_;
}

void player_character::set_is_active(bool is_active)
{
	is_active_ = is_active;
}


int player_character::get_player_id()
{
	return player_id_;
}

bool player_character::get_shuriken_button_pressed()
{
	return shuriken_button_pressed_;
}

bool player_character::get_character_facing_left()
{
	return animation_facing_left_;
}

void player_character::draw(RenderWindow& main_win)
{
	main_win.draw(character_sprite_);
}


void player_character::set_shuriken_button_pressed(bool shuriken_button_pressed)
{
	shuriken_button_pressed_ = shuriken_button_pressed;
}


void player_character::set_has_shuriken(bool has_shurikens)
{
	has_shuriken_ = has_shurikens;
}

bool player_character::get_has_shuriken()
{
	return has_shuriken_;
}
