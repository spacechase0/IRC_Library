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
