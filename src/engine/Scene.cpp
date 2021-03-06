/******************************************************************************
 *
 * ShadowFox Engine Source
 * Copyright (C) 2012-2013 by ShadowFox Studios
 * Created: 2012-09-02 by Taylor Snead
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/
#include "Scene.hpp"

// External

// Internal
#include "Entity.hpp"
#include "Console.hpp"
#include "Camera.hpp"

using namespace sfs;

Scene::Scene()
{
	// TODO Auto-generated constructor stub
}

Scene::~Scene()
{
	// TODO Auto-generated destructor stub
}

void Scene::Init()
{
}

void Scene::Update()
{
	for(auto ent : entities)
	{
		if(ent->active)
		{
			Log("Scene::Update(): Updating " + ent->name);
			ent->Update();
		}
	}
	Log("Scene::Update(): Finished");
}

void Scene::OnDestroy()
{
	for(uint i = 0; i < entities.size(); ++i)
	{
		entities[i]->Destroy();
	}
}

/*Entity* Scene::GetEntity( uint32_t idx )
 {
 return entities[idx];
 }*/

Entity* Scene::GetEntity(string name)
{
	for(uint i = 0; i < entities.size(); ++i)
	{
		if(entities[i]->name == name)
		{
			return entities[i];
		}
	}
}
