else if ( tokens[ 0 ] == "331" )
{
	event.type = Event::NoTopic;
}
else if ( tokens[ 0 ] == "332" )
{
	event.type = Event::Topic;
	event.channel = tokens[ 1 ];
	
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
	
	eraseToken();
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.channel = line;
}
else if ( tokens[ 0 ] == "PART" )
{
	event.type = Event::Part;
	
	eraseToken();
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
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "KICK" )
{
	event.type = Event::Kick;
	
	event.channel = tokens[ 1 ];
	event.target = tokens[ 2 ];
	eraseToken();
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
