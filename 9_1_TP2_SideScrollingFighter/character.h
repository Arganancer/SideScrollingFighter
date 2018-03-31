#pragma once
#include "movable.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "input_manager.h"

class character : public movable
{
public:
	// Overload Constructor
	character(Vector2f position, float speed);

	// Accessors

	// Mutators

protected:

	IntRect** int_rects_character_;
};
