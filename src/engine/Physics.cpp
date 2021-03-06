/******************************************************************************
 *
 *	ShadowFox Engine Source
 *	Copyright (C) 2012-2013 by ShadowFox Studios
 *	Created: 2012-07-29 by Taylor Snead
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 ******************************************************************************/

#include "Physics.hpp"

// External

// Internal
#include "Engine.hpp"
#include "Time.hpp"

using namespace sfs;

Physics::Physics()
{
}

Physics::~Physics()
{
}

/*******************************************************************************
 *
 *		Game Loop
 *
 *******************************************************************************/

void Physics::Init()
{
	collisionConfig = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
//	world = new sfDynamicsWorld( dispatcher, broadphase, solver, collisionConfig );

	gContactAddedCallback = &Physics::OnCollideEnter;
	gContactProcessedCallback = &Physics::OnCollideStay;
	gContactDestroyedCallback = &Physics::OnCollideExit;
}

void Physics::Update()
{
	if(world)
	{
		world->stepSimulation(game->time->deltaTime);
	}
}

void Physics::OnDestroy()
{
	delete collisionConfig;
	delete dispatcher;
	delete broadphase;
	delete solver;
	delete world;
}

/*******************************************************************************
 *
 *		Point Gravity
 *
 *******************************************************************************/

GravPoint* Physics::GetGravityPoint(string name)
{
	for(GravPoint * grav : gravityPoints)
	{
		if(grav->name == name)
		{
			return grav;
		}
	}
}

void Physics::SetGravityPoint(string name, vec3 point, float force)
{
	if(GravPoint* grav = GetGravityPoint(name))
	{
		grav->point = new vec3(point);
		grav->force = force;
		return;
	}
	gravityPoints.push_back(new GravPoint(name, new vec3(point), force));
}

void Physics::SetGravityPoint(string name, vec3& point, float force)
{
	if(GravPoint* grav = GetGravityPoint(name))
	{
		grav->point = &point;
		grav->force = force;
		return;
	}
	gravityPoints.push_back(new GravPoint(name, &point, force));
}

void Physics::SetGravityPoint(string name, float force)
{
	if(auto grav = GetGravityPoint(name))
	{
		grav->force = force;
	}
}

/*******************************************************************************
 *
 *		Static Collision Callbacks
 *
 *******************************************************************************/

bool Physics::OnCollide(string func, btManifoldPoint& cp, const btCollisionObject* colObj0, int partId0, int index0,
						const btCollisionObject* colObj1, int partId1, int index1)
{
	/*Rigidbody* body0 = nullptr;
	 Rigidbody* body1 = nullptr;

	 for (uint i = 0; i < game->physics->bodies.size(); ++i)
	 {
	 if (game->physics->bodies[i]->body == colObj0)
	 {
	 body0 = game->physics->bodies[i];
	 }
	 else if (game->physics->bodies[i]->body == colObj1)
	 {
	 body1 = game->physics->bodies[i];
	 }
	 }

	 if (body0 && body1)
	 {
	 CollisionInfo col;

	 col.rigidbody = body1;
	 col.collider = body1->collider;
	 col.entity = body1->owner;
	 col.point = vec3_cast<vec3>( cp.pointA ); //fix
	 col.normal = vec3_cast<vec3>( cp.normalA ); //fix

	 if (body1->isTrigger)
	 {
	 body0->collider->trigger( "OnTrigger" + func, col );
	 }
	 else
	 {
	 body0->collider->trigger( "OnCollide" + func, col );
	 }

	 col.rigidbody = body0;
	 col.collider = body0->collider;
	 col.entity = body0->owner;
	 col.point = vec3_cast<vec3>( cp.pointB ); //fix
	 col.normal = vec3_cast<vec3>( cp.normalB ); //fix

	 if (body0->isTrigger)
	 {
	 body1->collider->trigger( "OnTrigger" + func, col );
	 }
	 else
	 {
	 body1->collider->trigger( "OnCollide" + func, col );
	 }
	 }*/
}

bool Physics::OnCollideEnter(btManifoldPoint& cp, const btCollisionObject* colObj0, int partId0, int index0,
							 const btCollisionObject* colObj1, int partId1, int index1)
{
	return OnCollide("Enter", cp, colObj0, partId0, index0, colObj1, partId1, index1);
}

bool Physics::OnCollideStay(btManifoldPoint& cp, void* body0, void* body1)
{
//	return OnCollide( "Stay", cp, colObj0, partId0, index0, colObj1, partId1, index1 );
}

bool Physics::OnCollideExit(void* userPersistentData)
{
//	return OnCollide( "Exit", cp, colObj0, partId0, index0, colObj1, partId1, index1 );
}
