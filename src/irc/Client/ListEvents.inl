else if ( tokens[ 0 ] == "251" )
{
	event.type = Event::ListUserClient;
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "252" )
{
	event.type = Event::ListUserOp;
	event.amount = tokens[ 1 ];
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "253" )
{
	event.type = Event::ListUserUnknown;
	event.amount = tokens[ 1 ];
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "254" )
{
	event.type = Event::ListUserChannels;
	event.amount = tokens[ 1 ];
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "255" )
{
	event.type = Event::ListUserMe;
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
