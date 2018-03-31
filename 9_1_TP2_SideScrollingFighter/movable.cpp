#include "movable.h"
#include "shuriken_spawner.h"


movable::movable(Vector2f position, float speed) : entity(position), is_alive_(true), is_on_platform_(false)
{
	speed_ = speed;
	setPosition(position);
	gravity_ = 0.35f;
	friction_ = 0.99f;
	has_shuriken_ = false;
}

bool movable::get_is_alive() const
{
	return is_alive_;
}

void movable::kill_movable()
{
	is_alive_ = false;
	velocity_ = Vector2f(0, 0);
	if(has_shuriken_ == true)
	{
		has_shuriken_ = false;
	}
}

void movable::move()
{
	if(velocity_.x > max_velocity_.x)
	{
		velocity_.x = max_velocity_.x;
	}
	else if (velocity_.x < -max_velocity_.x)
	{
		velocity_.x = -max_velocity_.x;
	}
	if (velocity_.y > max_velocity_.y)
	{
		velocity_.y = max_velocity_.y;
	}
	else if (velocity_.y < -max_velocity_.y)
	{
		velocity_.y = -max_velocity_.y;
	}
	Sprite::move(velocity_);
}


void movable::adjust_movable_position(Vector2f adjustment_vector)
{
	Sprite::move(adjustment_vector);
}


void movable::kill_x_velocity()
{
	velocity_.x = 0;
}

void movable::kill_y_velocity()
{
	velocity_.y = 0;
}

void movable::accelerate(Vector2f acceleration)
{
	velocity_.x += acceleration.x;
	velocity_.y += acceleration.y;
}

void movable::set_is_on_platform(bool is_on_platform)
{
	if(is_on_platform)
	{
		velocity_.y = 0;
	}
	is_on_platform_ = is_on_platform;
}

Vector2f movable::get_velocity() const
{
	return velocity_;
}

void movable::set_is_colliding_wall_left(bool is_colliding)
{
	is_colliding_wall_left_ = is_colliding;
}

void movable::set_is_colliding_wall_right(bool is_colliding)
{
	is_colliding_wall_right_ = is_colliding;
}

Vector2f movable::get_top_left_point() const
{
	return getPosition() + top_left_point_;
}

Vector2f movable::get_top_right_point() const
{
	return getPosition() + top_right_point_;
}

Vector2f movable::get_right_upper_point() const
{
	return getPosition() + right_upper_point_;
}

Vector2f movable::get_right_lower_point() const
{
	return getPosition() + right_lower_point_;
}

Vector2f movable::get_bottom_left_point() const
{
	return getPosition() + bottom_left_point_;
}

Vector2f movable::get_bottom_right_point() const
{
	return getPosition() + bottom_right_point_;
}

Vector2f movable::get_left_upper_point() const
{
	return getPosition() + left_upper_point_;
}

Vector2f movable::get_left_lower_point() const
{
	return getPosition() + left_lower_point_;
}

void movable::set_is_colliding_platform_under(bool is_colliding)
{
	is_colliding_platform_under_ = is_colliding;
}

void movable::set_is_colliding_platform_over(bool is_colliding)
{
	is_colliding_platform_over_ = is_colliding;
}


bool movable::get_is_colliding_wall_left()
{
	return is_colliding_wall_left_;
}

bool movable::get_is_colliding_wall_right()
{
	return is_colliding_wall_right_;
}

bool movable::get_is_colliding_platform_under()
{
	return is_colliding_platform_under_;
}

bool movable::get_is_colliding_platform_over()
{
	return is_colliding_platform_over_;
}
