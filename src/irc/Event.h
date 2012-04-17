////////////////////////////////////////////////////////////
//
// IRC Client
// Copyright (C) 2012 Chase Warrington (staff@spacechase0.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef IRC_EVENT_H
#define IRC_EVENT_H

#include <string>

namespace irc
{
	class Event
	{
		public:
			#include "irc/Event/Type.inl"
			
			Event();
			Event( const std::string& thePrefix, Type theType );
			Event( const std::string& thePrefix, Type theType, const std::string& theMessage );
			Event( const std::string& thePrefix, Type theType, const std::string& theChannel, const std::string& theMessage );
			
			Type type;
			
			std::string prefix;
			std::string nick;
			std::string user;
			std::string host;
			
			std::string channel;
			std::string message;
			std::string amount;
			std::string mask;
			bool add;
			long mode;
	};
}

#endif // IRC_EVENT_H
