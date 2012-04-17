else if ( tokens[ 0 ] == "NOTICE" )
{
	event.type = Event::Notice;
	
	if ( tokens.size() > 1 )
	{
		if ( line[ 0 ] == ':' )
		{
			line.erase( 0, 1 );
		}
		event.message = line;
	}
}
else if ( tokens[ 0 ] == "PRIVMSG" )
{
	event.type = Event::Message;
	
	if ( tokens.size() > 1 )
	{
		event.channel = tokens[ 1 ];
		eraseToken();
	}
	if ( tokens.size() > 2 )
	{
		if ( line[ 0 ] == ':' )
		{
			line.erase( 0, 1 );
		}
		event.message = line;
	}
	
	if ( event.channel[ 0 ] != '#' and event.channel[ 0 ] != '&' )
	{
		event.channel = event.nick;
	}
}
