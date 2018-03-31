#include  "shuriken.h"
#include <SFML/Graphics/Texture.hpp>
Texture shuriken::texture_;

shuriken::shuriken() : movable(Vector2f(0,0),0)
{
	//Setting basic variables
	is_alive_ = false;
	max_velocity_ = Vector2f(20, 5);
}

void shuriken::update()
{
	if (is_alive_ == true)
	{
		accelerate(Vector2f(0, 0.30f));
		move();
	}
}

bool shuriken::load_textures(const std::string texture_path)
{
if (!texture_.loadFromFile(texture_path)) {
	return false;
	}
return true;
}

void shuriken::set_textures()
{
	setTexture(texture_);
	setTextureRect(int_rects_movable_[0][0]);
}


void shuriken::visual_adjustments()
{
const auto nb_shuriken_frames = 1;
const auto nb_shuriken_anims = 1;

// Adjust character bounding box.
const int width = texture_.getSize().x / nb_shuriken_frames;
const int height = texture_.getSize().y / nb_shuriken_anims;

int_rects_movable_ = new IntRect*[nb_shuriken_anims];
for (size_t i = 0; i < nb_shuriken_anims; i++)
{
	int_rects_movable_[i] = new IntRect[nb_shuriken_frames];
	for (size_t j = 0; j < nb_shuriken_frames; j++)
	{
		int_rects_movable_[i][j].left = width * j;
		int_rects_movable_[i][j].top = height * i;
		int_rects_movable_[i][j].width = width;
		int_rects_movable_[i][j].height = height;
	}
}
//top_left_point_ = Vector2f(width / 2 * 0.25f + width, 0);
//top_right_point_ = Vector2f(width / 2 * 0.75f + width, 0);
//left_upper_point_ = Vector2f(0, height*0.25f);
//left_lower_point_ = Vector2f(0, height*0.75f);
//bottom_left_point_ = Vector2f(width / 2 * 0.25f + width, height);
//bottom_right_point_ = Vector2f(width / 2 * 0.75f + width, height);
//right_upper_point_ = Vector2f(width, height*0.25f);
//right_lower_point_ = Vector2f(width, height*0.75f);
//center_of_shuriken_ = Vector2f(width / 2, height / 2);

	top_left_point_ = Vector2f(0,0);
	top_right_point_ = Vector2f(width, 0);
	left_upper_point_ = Vector2f(0, height*0.25f);
	left_lower_point_ = Vector2f(0, height*0.75f);
	bottom_left_point_ = Vector2f(0 , height);
	bottom_right_point_ = Vector2f( width, height);
	right_upper_point_ = Vector2f(width, height*0.25f);
	right_lower_point_ = Vector2f(width, height*0.75f);
	center_of_shuriken_ = Vector2f(width / 2, height / 2);
}

bool shuriken::contains(Vector2f point)
{
	//Gets the distance between the to objects as circles.
	const float distance = sqrt(pow(point.x - (getPosition().x +center_of_shuriken_.x), 2) +
		pow(point.y - (getPosition().y + center_of_shuriken_.y), 2));
	if (getGlobalBounds().width / 2 >= distance)
	{
		set_is_alive(false);
		return true;
	}
	return false;
}

void shuriken::set_position(Vector2f position)
{
	setPosition(position);
}

void shuriken::set_is_alive(bool is_alive)
{
	is_alive_ = is_alive;
}


void shuriken::set_shuriken_player_id(int player_id)
{
	shuriken_player_id_ = player_id;
}

bool shuriken::get_is_alive()
{
	return is_alive_;
}

void shuriken::shoot(Vector2f position, int id_player, Vector2f velocity,bool is_faceing_left)
{
	set_position(position);
	set_shuriken_player_id(id_player);
	set_is_alive(true);
	//shoots left if the character is facing left
	if(is_faceing_left == true)
	{
		velocity.x = -30;
	}
	//shoots left if the character is facing left
	else
	{
		velocity.x = 30;
	}
	set_initial_velocity(velocity);
}

void shuriken::set_initial_velocity(Vector2f velocity)
{
	velocity_ = velocity;
}

int shuriken::get_shuriken_player_id()
{
	return shuriken_player_id_;
}
