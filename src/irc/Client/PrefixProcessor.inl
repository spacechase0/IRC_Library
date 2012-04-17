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

if ( line[ 0 ] == ':' )
{
	size_t space = line.find( ' ' );
	if ( space == std::string::npos )
	{
		return Event();
	}
	
	event.prefix = line.substr( 1, space - 1 );
	line.erase( 0, space + 1 );
	
	std::string process = event.prefix;
	
	size_t exclamation = process.find( '!' );
	if ( exclamation != std::string::npos )
	{
		event.nick = process.substr( 0, exclamation );
		process.erase( 0, exclamation + 1 );
	}
	
	size_t at = process.find( '@' );
	if ( at != std::string::npos )
	{
		event.user = process.substr( 0, at );
		process.erase( 0, at + 1 );
		event.host = process;
	}
}
