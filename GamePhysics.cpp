#include "GamePhysics.h"
#include "RigidBody.h"
#include "CollisionVolume.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "../../Common/Vector2.h"

/* Everything from this class except for the relevant method was removed */

void GamePhysics::SeparateObjects(CollisionVolume* lhs, CollisionVolume* rhs) {

		// Projection
		// ----------
		RigidBody* lhs_rb = lhs->getRigidBody();
		RigidBody* rhs_rb = rhs->getRigidBody();
		float lhs_mass = 0;
		float rhs_mass = 0;
		if (lhs_rb != nullptr) lhs_mass = lhs_rb->inverseMass;
		if (rhs_rb != nullptr) rhs_mass = rhs_rb->inverseMass;

		Vector2 normal = lhs->getCollisionNormal();
		
		float penetration_distance = lhs->getCollisionPenDistance();
	
		float totalMass = lhs_mass + rhs_mass;

		if (lhs_rb != nullptr) lhs_rb->position += normal * penetration_distance * lhs_mass / totalMass;
		if (rhs_rb != nullptr) rhs_rb->position -= normal * penetration_distance * rhs_mass / totalMass;

		// apply impulses
		// --------------
		Vector2 lhs_vel(0, 0);
		Vector2 rhs_vel(0, 0);
		if (lhs_rb != nullptr) lhs_vel = lhs_rb->GetVelocity();
		if (rhs_rb != nullptr) rhs_vel = rhs_rb->GetVelocity();
		float e = 0.5;
			
		Vector2 relativeVelocity = rhs_vel - lhs_vel;


		float dot_prod = Vector2::Dot(normal,relativeVelocity);
		float impulse = (-(1 + e) * dot_prod) / totalMass;
	
		Vector2 lhs_impulse = (normal * impulse)*lhs_mass;
		Vector2 rhs_impulse = (normal * impulse)*rhs_mass;

		if (lhs_rb != nullptr)lhs_rb->AddImpulse(-lhs_impulse);
		if (rhs_rb != nullptr)rhs_rb->AddImpulse(rhs_impulse);

}

