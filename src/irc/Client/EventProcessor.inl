#define eraseToken() line.erase( 0, line.find( " " ) + 1 ); tokens.erase( tokens.begin() );
std::string oldLine = line;
//eraseToken();
if ( tokens[ 0 ] == "PING" )
{
	event.type = Event::Ping;
	eraseToken();
	
	if ( line[ 0 ] == ':' )
	{
		line.erase( 0, 1 );
	}
	event.message = tokens[ 0 ];
}
#include "irc/Client/ChannelEvents.inl"
#include "irc/Client/MessageEvents.inl"
#include "irc/Client/ListEvents.inl"
#include "irc/Client/MotdEvents.inl"
#include "irc/Client/ModeEvents.inl"
#include "irc/Client/NameEvents.inl"
else if ( tokens[ 0 ] == "001" or tokens[ 0 ] == "002" or
		  tokens[ 0 ] == "003" or tokens[ 0 ] == "004" or
		  tokens[ 0 ] == "005" or tokens[ 0 ] == "265" or
		  tokens[ 0 ] == "266" or tokens[ 0 ] == "333" )
{
	// Ignore these, I don't see them in the RFC
}
else
{
	std::cout << "Got an unknown '" << tokens[ 0 ] << "': " << std::endl
	          << "\t" << oldLine << std::endl;
}
