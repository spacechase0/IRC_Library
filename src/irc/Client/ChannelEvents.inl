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

else if ( tokens[ 0 ] == "331" )
{
	event.type = Event::NoTopic;
}
else if ( tokens[ 0 ] == "332" )
{
	event.type = Event::Topic;
	event.channel = tokens[ 2 ];
	
	eraseToken();
	eraseToken();
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "JOIN" )
{
	event.type = Event::Join;
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.channel = line;
}
else if ( tokens[ 0 ] == "PART" )
{
	event.type = Event::Part;
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.channel = line;
}
else if ( tokens[ 0 ] == "QUIT" )
{
	event.type = Event::Quit;
	
	eraseToken();
	event.message = line;
}
