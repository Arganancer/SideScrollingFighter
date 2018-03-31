#include "entity.h"

entity::entity(Vector2f position)
{
}

bool entity::intersects(Sprite* sprite) const
{
	auto r = sprite->getGlobalBounds();
	r.left = sprite->getPosition().x;
	r.top = sprite->getPosition().y;
	return getGlobalBounds().intersects(r);
}


bool entity::contains(Vector2f point) const
{
	return getGlobalBounds().contains(point);
}
