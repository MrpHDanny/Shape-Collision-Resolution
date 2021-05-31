#include "CircleCollider.h"
#include "RectangleCollider.h"

CircleCollider::CircleCollider(unsigned int r, Vector2 pos, RigidBody* rb)
{
	type = t;
	position = pos;
	radius = r;
	parentBody = rb;
	colliderShape = ColliderShape::Circle;
}

bool CircleCollider::isCollision(CollisionVolume* s)
{

	if (s->getShape() == CollisionVolume::ColliderShape::Circle) {			/* Circle-Circle collision */
		CircleCollider* circle_col = dynamic_cast<CircleCollider*>(s);
		int xDif = (this->getPosition().x - circle_col->getPosition().x);
		int yDif = (this->getPosition().y - circle_col->getPosition().y);
		float distance = sqrt(pow(xDif, 2) + pow(yDif, 2));
		int radiusSum = this->getRadius() + circle_col->getRadius();

		if (distance <= radiusSum) {
			Vector2 normal = (this->getPosition() - circle_col->getPosition()).Normalised();
			float penetrationDistance = abs(distance - (this->getRadius() + circle_col->getRadius()));

			this->setCollisionNormal(normal);
			this->setCollisionPenDistance(penetrationDistance);
			s->setCollisionNormal(normal);
			s->setCollisionPenDistance(penetrationDistance);
			return true;
		}
		return false;
	}
	else {																	/* Circle-AABB collision */
		RectangleCollider* rectangle_col = dynamic_cast<RectangleCollider*>(s);
		float testX = this->getPosition().x;
		float testY = this->getPosition().y;

		// Circle
		int cx = this->getPosition().x;
		int cy = this->getPosition().y;
		int r = this->getRadius();

		// AABB
		int rx = rectangle_col->getPosition().x;
		int ry = rectangle_col->getPosition().y;
		int rw = rectangle_col->getHalfSize().x;
		int rh = rectangle_col->getHalfSize().y;

		// which edge is closest?
		if (cx < rx - rw) testX = rx - rw; // Test left edge
		else if (cx > rx + rw) testX = rx + rw; // Test right edge
		
		if (cy < ry - rh) testY = ry - rh; // Test bottom edge
		else if (cy > ry + rh) testY = ry + rh; // Test Top edge

		// get distance from closes edges
		int distX = cx - testX;
		int distY = cy - testY;
		float distance = sqrt(pow(distX, 2) + pow(distY, 2));

		// if the distance is less than the radius we have a collision
		if (distance < r) {
			Vector2 closestPoint(testX, testY);
			Vector2 normal = (this->getPosition() - closestPoint).Normalised();

			float penetrationDistance = abs(this->getRadius() - distance);

			this->setCollisionNormal(normal);
			this->setCollisionPenDistance(penetrationDistance);
			s->setCollisionNormal(-normal);
			s->setCollisionPenDistance(penetrationDistance);
			
			return true;
		}
	}
	return false;
}

float CircleCollider::getRadius() const
{
	return radius;
}