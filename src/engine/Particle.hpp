/******************************************************************************
 *
 *	ShadowFox Engine Source
 *	Copyright (C) 2012-2013 by ShadowFox Studios
 *	Created: 2012-08-03 by Taylor Snead
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
#pragma once
#include "stdafx.hpp"

// External

// Internal
#include "Transform.hpp"
#include "Range.hpp"

namespace sfs
{
	class ParticleSystem;

	/** @addtogroup Engine
	 *	 @{
	 */
	/** @addtogroup Particles
	 *	 @{
	 */

	/**	Particle
	 *	@details
	 *		Description
	 *	@todo
	 *		Todo
	 */
	class Particle
	{
	public:
		Particle();
		virtual ~Particle();

		// Make these virtual when they need to be inherited and overwritten.
		void Init();
		void Update(double delta);
		void Destroy();

		//void Launch();

		void Activate(bool reset = false);
		void Deactivate();
		void SetVelocity(vec3 vel);
		void SetSpeed(float speed);
		void SetSizeRange(float start, float end)
		{
			size.min = start;
			size.max = end;
		}
		void SetGravity(vec3 gravity)
		{
			this->gravity = gravity;
		}
		void StartLife(float life);
		void InterpParams(double delta);
		void SetParamDiffs();
		void ApplyForce(vec3 force);
		void ApplyForce(float speed, vec3 dir);

		/// Converts the velocity vector into a speed float.
		float GetSpeed();

		Transform* transform;
		float speed;
		vec3 velocity;
		Range<vec3> velRange;
		vec3 velDiff;
		vec3 gravity;
		float lifetime;
		float age;
		Range<float> size;
		float sizeDiff;
		Range<rgba> color;
		rgba colorDiff;
		bool active;

		ParticleSystem* system;

	protected:

	private:
	};

	/** @} */
	/** @} */
}
