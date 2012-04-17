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

else if ( tokens[ 0 ] == "MODE" )
{
	eraseToken();
	
	if ( tokens[ 1 ][ 0 ] == '#' or tokens[ 1 ][ 0 ] == '&' or tokens[ 1 ][ 0 ] == '+' or tokens[ 1 ][ 0 ] == '!' )
	{
		event.type = Event::ChannelMode;
		event.channel = tokens[ 1 ];
	}
	else
	{
		event.type = Event::UserMode;
		event.user = tokens[ 1 ];
	}
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	
	{
		if ( line[ 0 ] == '+' )
		{
			event.add = true;
		}
		else
		{
			event.add = false;
		}
		line.erase( 0, 1 );
	}
	
	event.mode = 0;
	if ( event.type == Event::ChannelMode )
	{
		bool foundOwn = false;
		bool foundOp = false;
		bool foundVoice = false;
		bool foundKey = false;
		bool foundLimit = false;
		bool foundBan = false;
		bool foundBanExc = false;
		bool foundInv = false;
		for ( size_t i = 0; i < tokens[ 2 ].length(); ++i )
		{
			switch ( tokens[ 2 ][ i ] )
			{
				case 'a':
					event.mode |= Mode::Anonymous;
					break;
				
				case 'i':
					event.mode |= Mode::Invite;
					break;
				
				case 'm':
					event.mode |= Mode::Moderated;
					break;
				
				case 'n':
					event.mode |= Mode::NoOutside;
					break;
				
				case 'q':
					event.mode |= Mode::Quiet;
					break;
				
				case 'p':
					event.mode |= Mode::Private;
					break;
				
				case 's':
					event.mode |= Mode::Secret;
					break;
				
				case 'r':
					event.mode |= Mode::Reop;
					break;
				
				case 't':
					event.mode |= Mode::OpTopic;
					break;
				
				// A few 'special' ones
				case 'O':
					event.mode |= Mode::ChanOwner;
					foundOwn = true;
					break;
				
				case 'o':
					event.mode |= Mode::ChannelOp;
					foundOp = true;
					break;
				
				case 'v':
					event.mode |= Mode::Voice;
					foundVoice = true;
					break;
				
				case 'k':
					event.mode |= Mode::Key;
					foundKey = true;
					break;
				
				case 'l':
					event.mode |= Mode::Limit;
					foundLimit = true;
					break;
				
				case 'b':
					event.mode |= Mode::Ban;
					foundBan = true;
					break;
				
				case 'e':
					event.mode |= Mode::BanExcept;
					foundBanExc = true;
					break;
				
				case 'I':
					event.mode |= Mode::InviMask;
					foundInv = true;
					break;
			}
		}
		eraseToken();
		size_t next = 3;
		if ( foundLimit and event.add )
		{
			event.amount = tokens[ next++ ];
		}
		if ( foundOwn or foundOp or foundVoice )
		{
			event.user = tokens[ next++ ];
		}
		if ( foundBan or foundBanExc or foundInv )
		{
			event.mask = tokens[ next++ ];
		}
	}
	else
	{
		for ( size_t i = 0; i < tokens[ 2 ].length(); ++i )
		{
			switch ( tokens[ 2 ][ i ] )
			{
				case 'i':
					event.mode |= Mode::Invisible;
					break;
				
				case 's':
					event.mode |= Mode::ServerNotice;
					break;
				
				case 'w':
					event.mode |= Mode::Wallops;
					break;
				
				case 'o':
					event.mode |= Mode::Operator;
					break;
			}
		}
	}
	
}
