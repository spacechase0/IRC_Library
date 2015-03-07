else if ( tokens[ 0 ] == "353" )
{
	event.type = Event::NameReply;
	event.channel = tokens[ 3 ];
	eraseToken();
	eraseToken(); // Nick?
	eraseToken(); // An equals sign?
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "366" )
{
	event.type = Event::EndOfNames;
	event.channel = tokens[ 2 ];
	eraseToken();
	eraseToken(); // Nick?
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
else if ( tokens[ 0 ] == "NICK" )
{
	event.type = Event::Nick;
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = line;
}
