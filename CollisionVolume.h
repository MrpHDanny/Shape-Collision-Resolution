#pragma once
#include "../../Common/Vector2.h"
#include "RigidBody.h"



class CollisionVolume {
public:
	CollisionVolume();
	virtual ~CollisionVolume();
	virtual bool isCollision(CollisionVolume* s) = 0;
	Vector2 getPosition() const;
	void setPosition(Vector2 pos);
	
	enum class ColliderShape {
		Circle,
		Rectangle
	};

	ColliderShape colliderShape;

	ColliderShape getShape() {
		return colliderShape;
	}

	RigidBody* getRigidBody() {
		return parentBody;
	}

	Vector2 getCollisionNormal() {
		return collision_normal;
	}

	float getCollisionPenDistance() {
		return collision_pen_distance;
	}

	void setCollisionNormal(Vector2 norm) {
		collision_normal = norm;
	}

	void setCollisionPenDistance(float dist) {
		collision_pen_distance = dist;
	}

protected:
	Vector2 position;
	Vector2 collision_normal;
	float collision_pen_distance;
	RigidBody* parentBody;

};




