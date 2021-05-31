#include "CollisionVolume.h"

CollisionVolume::CollisionVolume()
{
}

CollisionVolume::~CollisionVolume()
{
}

Vector2 CollisionVolume::getPosition() const
{
	return position;
}

void CollisionVolume::setPosition(Vector2 pos) {
	this->position = pos;
}







