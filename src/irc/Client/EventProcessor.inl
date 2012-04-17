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

#define eraseToken() line.erase( 0, line.find( " " ) + 1 )

eraseToken();
if ( tokens[ 0 ] == "PING" )
{
	event.type = Event::Ping;
	event.message = tokens[ 1 ];
}
#include "irc/Client/ChannelEvents.inl"
#include "irc/Client/MessageEvents.inl"
#include "irc/Client/ListEvents.inl"
#include "irc/Client/MotdEvents.inl"
#include "irc/Client/ModeEvents.inl"
#include "irc/Client/NameEvents.inl"
else if ( tokens[ 0 ] == "001" or tokens[ 0 ] == "002" or
		  tokens[ 0 ] == "003" or tokens[ 0 ] == "004" or
		  tokens[ 0 ] == "005" or tokens[ 0 ] == "265" or
		  tokens[ 0 ] == "266" or tokens[ 0 ] == "333" )
{
	// Ignore these, I don't see them in the RFC
}
else
{
	std::cout << "Got an unknown '" << tokens[ 0 ] << "': " << std::endl
	          << "\t" << line << std::endl;
}
