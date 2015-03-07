else if ( tokens[ 0 ] == "372" )
{
	event.type = Event::Motd;
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "375" )
{
	event.type = Event::MotdStart;
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "376" )
{
	event.type = Event::EndOfMotd;
	eraseToken();
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
