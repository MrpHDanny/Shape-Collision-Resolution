#include "RectangleCollider.h"
#include <string> 


RectangleCollider::RectangleCollider(unsigned int w, unsigned int h, Vector2 pos, CollisionVolume::Type t, RigidBody* rb)
{
	type = t;
	position = pos;
	width = w;
	height = h;
	parentBody = rb;
	colliderShape = ColliderShape::Rectangle;
}


bool RectangleCollider::isCollision(CollisionVolume* s)
{
	
	/* Ignore collisions between map tile colliders */
	if ((getType() == Type::Ground || getType() == Type::Ladder || getType() == Type::Wall) &&
		(s->getType() == Type::Ground || s->getType() == Type::Ladder || s->getType() == Type::Wall)) {

		return false;
	}

	if (s->getShape() == CollisionVolume::ColliderShape::Rectangle) {		/* AABB-AABB collision */
		RectangleCollider* rectangle_col = dynamic_cast<RectangleCollider*>(s);
		float thisX = this->getPosition().x;
		float thisY = this->getPosition().y;
		float thisW = this->getHalfSize().x * 2;
		float thisH = this->getHalfSize().y * 2;
		float rhsX = rectangle_col->getPosition().x;
		float rhsY = rectangle_col->getPosition().y;
		float rhsW = rectangle_col->getHalfSize().x * 2;
		float rhsH = rectangle_col->getHalfSize().y * 2;

		float thisMinX = thisX - thisW / 2;
		float thisMinY = thisY - thisH / 2;
		float thisMaxY = thisY + thisH / 2;
		float thisMaxX = thisX + thisW / 2;
		float rhsMinX = rhsX - rhsW / 2;
		float rhsMinY = rhsY - rhsH / 2;
		float rhsMaxY = rhsY + rhsH / 2;
		float rhsMaxX = rhsX + rhsW / 2;
		
		if ((thisMinX < rhsMaxX && thisMaxX > rhsMinX) &&
			(thisMinY < rhsMaxY && thisMaxY > rhsMinY))
		{
		
			float smallest_penDist_x;
			float smallest_penDist_y;

			float distFromRight = rhsMaxX - thisMinX;
			float distFromLeft = thisMaxX - rhsMinX;
			float distFromTop = rhsMaxY - thisMinY;
			float distFromBottom = thisMaxY - rhsMinY;

			/* Find axis with least penetration distance */
			if ((abs(distFromRight) < abs(distFromBottom) && abs(distFromRight) < abs(distFromTop)) ||
				(abs(distFromLeft) < abs(distFromBottom) && abs(distFromLeft) < abs(distFromTop))) {
				// x axis
				if (abs(distFromRight) < abs(distFromLeft)) {
					// push right
					this->setCollisionNormal(Vector2(1,0));
					s->setCollisionNormal(Vector2(1, 0));
					this->setCollisionPenDistance(distFromRight);
					s->setCollisionPenDistance(distFromRight);
				}
				else {
					// push left
					this->setCollisionNormal(Vector2(-1, 0));
					s->setCollisionNormal(Vector2(-1, 0));
					this->setCollisionPenDistance(distFromLeft);
					s->setCollisionPenDistance(distFromLeft);
				}
			}
			else {
				if (abs(distFromBottom) < abs(distFromTop)) {
					// push down
					this->setCollisionNormal(Vector2(0, -1));
					s->setCollisionNormal(Vector2(0, -1));
					this->setCollisionPenDistance(distFromBottom);
					s->setCollisionPenDistance(distFromBottom);
				}
				else {
					// push up
					this->setCollisionNormal(Vector2(0, 1));
					s->setCollisionNormal(Vector2(0, 1));
					this->setCollisionPenDistance(distFromTop);
					s->setCollisionPenDistance(distFromTop);
				}
			}

			return true;
		}
	}
	else {
		return s->isCollision(this);
	}
	return false;
}

Vector2 RectangleCollider::getHalfSize() const
{
	return Vector2(width/2,height/2);
}
