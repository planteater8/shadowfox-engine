/******************************************************************************
 *
 *	ShadowFox Engine Source
 *	Copyright (C) 2012-2013 by ShadowFox Studios
 *	Created: 2012-07-15 by Taylor Snead
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

#include "Engine.hpp"

// External

// Internal
#include "Renderer.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Physics.hpp"
#include "Settings.hpp"
#include "Audio.hpp"
#include "Scene.hpp"
#include "FileManager.hpp"
#include "Console.hpp"
#include "SystemInfo.hpp"
#include "Console.hpp"

namespace sfs
{
	Engine* game;
}

using namespace sfs;

extern "C" void Launch()
{
	game = new Engine();
	game->standAlone = true;
	game->Init();
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

/*******************************************************************************
 *
 *		Generic Subsystem Functions
 *
 *******************************************************************************/

void Engine::Init()
{
	standAlone = false;

	console = new Console;
	console->Init();

	Log("ShadowFox Engine launched.");

	systemInfo = new SystemInfo;
	time = new Time;
	physics = new Physics;
	scene = new Scene;
	renderer = new Renderer;
	input = new Input;

	Log("Subsystems instantiated.");

	//systemInfo->Init();
	time->Init();
	//physics->Init();
	if(standAlone)
	{
		renderer->Init();
	}
	scene->Init();
	input->Init();

	Log("Window callback set.");

	Log("Subsystems initialized");
}

void Engine::Update()
{
	while(!destroy)
	{
		PreUpdate();
		if(standAlone && renderer->render)
		{
			renderer->PreUpdate();
		}
		time->Update();
		//physics->Update();
		input->Update();
		if(standAlone && renderer->render)
		{
			renderer->Update();
		}
		PostUpdate();
	}
	Destroy();
}

/*******************************************************************************
 *
 *		General Game Functions
 *
 *******************************************************************************/

void Engine::LoadScene(string scene)
{
}

void Engine::Destroy()
{
	input->Destroy();
	renderer->Destroy();
	input->Destroy();
	physics->Destroy();
	scene->Destroy();
	delete this;
}

void Engine::Exit()
{
	destroy = true;
}
