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
