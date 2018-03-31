#pragma once
#include "entity.h"

class movable : public entity
{
public:
	// Overload Constructor
	movable(Vector2f position, float speed);

	// Accessors
	bool get_is_alive() const;
	
	/// <summary>
	/// Gets the velocity.
	/// </summary>
	/// <returns></returns>
	Vector2f get_velocity() const;
	
	/// <summary>
	/// Gets the top left point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_top_left_point() const;
	
	/// <summary>
	/// Gets the top right point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_top_right_point() const;
	
	/// <summary>
	/// Gets the right upper point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_right_upper_point() const;
	
	/// <summary>
	/// Gets the right lower point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_right_lower_point() const;
	
	/// <summary>
	/// Gets the bottom left point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_bottom_left_point() const;
	
	/// <summary>
	/// Gets the bottom right point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_bottom_right_point() const;
	
	/// <summary>
	/// Gets the left upper point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_left_upper_point() const;
	
	/// <summary>
	/// Gets the left lower point.
	/// </summary>
	/// <returns></returns>
	Vector2f get_left_lower_point() const;
	
	/// <summary>
	/// Gets is colliding wall left.
	/// </summary>
	/// <returns></returns>
	bool get_is_colliding_wall_left();
	
	/// <summary>
	/// Gets is colliding wall right.
	/// </summary>
	/// <returns></returns>
	bool get_is_colliding_wall_right();
	
	/// <summary>
	/// Gets is colliding platform under.
	/// </summary>
	/// <returns></returns>
	bool get_is_colliding_platform_under();
	
	/// <summary>
	/// Gets is colliding platform over.
	/// </summary>
	/// <returns></returns>
	bool get_is_colliding_platform_over();

	// Mutators
	
	/// <summary>
	/// Sets acceleration
	/// </summary>
	/// <param name="acceleration">The acceleration.</param>
	void accelerate(Vector2f acceleration);
	
	/// <summary>
	/// Moves this instance.
	/// </summary>
	void move();
	
	/// <summary>
	/// Sets is on platform.
	/// </summary>
	/// <param name="is_on_platform">if set to <c>true</c> [is on platform].</param>
	void set_is_on_platform(bool is_on_platform);
	
	/// <summary>
	/// Adjusts the movable's position.
	/// </summary>
	/// <param name="adjustment_vector">The adjustment vector.</param>
	void adjust_movable_position(Vector2f adjustment_vector);
	
	/// <summary>
	/// Kills the x velocity.
	/// </summary>
	void kill_x_velocity();
	
	/// <summary>
	/// Kills the y velocity.
	/// </summary>
	void kill_y_velocity();
	
	/// <summary>
	/// Kills the movable.
	/// </summary>
	void kill_movable();
	
	/// <summary>
	/// Sets is colliding wall left.
	/// </summary>
	/// <param name="is_colliding">if set to <c>true</c> [is colliding].</param>
	void set_is_colliding_wall_left(bool is_colliding);
	
	/// <summary>
	/// Sets is colliding wall right.
	/// </summary>
	/// <param name="is_colliding">if set to <c>true</c> [is colliding].</param>
	void set_is_colliding_wall_right(bool is_colliding);
	
	/// <summary>
	/// Sets is colliding platform under.
	/// </summary>
	/// <param name="is_colliding">if set to <c>true</c> [is colliding].</param>
	void set_is_colliding_platform_under(bool is_colliding);
	
	/// <summary>
	/// Sets is colliding platform over.
	/// </summary>
	/// <param name="is_colliding">if set to <c>true</c> [is colliding].</param>
	void set_is_colliding_platform_over(bool is_colliding);

protected:
	float speed_;
	bool is_alive_;

	float friction_;
	float gravity_;
	float acceleration_x_;
	float deceleration_x_;

	bool is_colliding_platform_under_;
	bool is_colliding_platform_over_;
	bool is_colliding_wall_left_;
	bool is_colliding_wall_right_;
	bool has_shuriken_;

	Vector2f velocity_;
	Vector2f max_velocity_;
	IntRect** int_rects_movable_;

	bool is_on_platform_;

	const double pi_ = 3.14159265358979323846;
	
	// Collision points of the movable. These are used when verifying collisions with tiles 
	// to know in which direction to reajust the movable.
	// The first part of the variable name designates the side of the rectangle the point is on.
	// Since there are two points per side, the second part of the variable name designates the 
	// position of the point on the side it is on.
	Vector2f top_left_point_;
	Vector2f top_right_point_;
	Vector2f right_upper_point_;
	Vector2f right_lower_point_;
	Vector2f bottom_left_point_;
	Vector2f bottom_right_point_;
	Vector2f left_upper_point_;
	Vector2f left_lower_point_;
};
