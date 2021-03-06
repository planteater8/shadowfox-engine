/******************************************************************************
 *
 *	ShadowFox Engine Source
 *	Copyright (C) 2012-2013 by ShadowFox Studios
 *	Created: 2012-10-28 by Taylor Snead
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
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
#include <boost/signals2.hpp>
#include <typeinfo>

// Internal
#include "Type.hpp"

#define SENDER(obj, sig) obj, "sig"
#define RECEIVER(obj, slot) obj, &decltype(*obj)::slot

using boost::signals2::signal;

namespace sfs
{

	/** @addtogroup Engine
	 *	@{
	 */
	/** @addtogroup Subsystems
	 *	@{
	 */

	/**
	 *	The base class for any object-oriented classes.
	 *	@details
	 *		Implements a signals and slots system similar to Qt's. Also contains
	 *		a few basic game-loop functions to allow homogeneous pointers to an Object
	 *		instance, like in ActionScript.
	 *	@todo
	 *		Possibly make the connection naming more efficient.
	 *		Be sure that the variadic templating works.
	 */
	class Object
	{
		class Event
		{
		public:
			string name;

			Event(string name) :
				name(name)
			{
			}

			virtual ~Event()
			{
			}
		};

		class Event0 : public Event
		{
		public:
			signal<void(void)> sig;

			Event0(string name, boost::function<void()> func) :
				Event(name)
			{
				sig.connect(func);
			}
		};

		template<typename ... P>
		class EventP : public Event
		{
		public:
			signal<void(P...)> sig;

			EventP(string name, boost::function<void(P...)> func) :
				Event(name)
			{
				sig.connect(func);
			}
		};
	public:
		/*template<class C>
		 void Connect( Object* sender, string name, C* receiver, void (C::*func)() )
		 {
		 name = Type( sender ) + "::" + name + "()";
		 for (auto connection : sender->connections)
		 {
		 if (connection->name == name)
		 {
		 Connection0* con = dynamic_cast<Connection0*>( connection );
		 if (con)
		 {
		 //						con->sig.connect( boost::bind( func, receiver ) );
		 }
		 return;
		 }
		 }
		 //			sender->connections += new Connection0( name, boost::bind( func, receiver ) );
		 }*/

		template<typename S, typename R, typename F, typename ... P>
		void connect(S* sender, string name, R* receiver, F(R::*func)(P...))
		{
			name = Type(sender) + "::" + name + "(" + Type<P...>() + ")";
			for(auto connection : sender->events)
			{
				if(connection->name == name)
				{
					EventP<P...>* con = dynamic_cast<EventP<P...>*>(connection);
					if(con)
					{
						con->sig.connect(boost::bind(func, receiver));
					}
					return;
				}
			}
			Event* con = new EventP<P...>(name, boost::bind(func, receiver));
			sender->events.push_back(con);
		}

		void trigger(string name)
		{
			name = Type(this) + "::" + name + "()";
			for(auto event : events)
			{
				if(event->name == name)
				{
					Event0* con = dynamic_cast<Event0*>(event);
					if(con)
					{
						con->sig();
					}
				}
			}
		}

		template<typename ... P>
		void trigger(string name, P ... args)
		{
			name = Type(this) + "::" + name + "(" + Type<P...>() + ")";
			for(auto connection : events)
			{
				if(connection->name == name)
				{
					EventP<P...>* con = dynamic_cast<EventP<P...>*>(connection);
					if(con)
					{
						con->sig(args...);
					}
				}
			}
			trigger(name);
		}

		bool connected(string name)
		{
			name = Type(this) + "::" + name;
			for(uint i = 0; i < events.size(); ++i)
			{
				if(events[i]->name == name)
				{
					return true;
				}
			}
			return false;
		}

		virtual void Init();
		virtual void Update()
		{
		}
		virtual void Destroy();

	protected:
		Object();
		virtual ~Object();

		virtual void Destroy(Object* obj);
		virtual void OnDestroy()
		{
		}
		virtual void Bind();

	private:
		vector<Event*> events;
	};

/// @}
/// @}

} /* namespace sfs */
