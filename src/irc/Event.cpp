#include "irc/Event.hpp"

namespace irc
{
	Event::Event()
	   : type( UnusedReply ),
	     prefix( "" ),
	     channel( "" ),
	     message( "" )
	{
	}
	
	Event::Event( const std::string& thePrefix, Type theType )
	   : type( theType ),
	     prefix( thePrefix ),
	     channel( "" ),
	     message( "" )
	{
	}
	
	Event::Event( const std::string& thePrefix, Type theType, const std::string& theMessage )
	   : type( theType ),
	     prefix( thePrefix ),
	     channel( "" ),
	     message( theMessage )
	{
	}
	
	Event::Event( const std::string& thePrefix, Type theType, const std::string& theChannel, const std::string& theMessage )
	   : type( theType ),
	     prefix( thePrefix ),
	     channel( theChannel ),
	     message( theMessage )
	{
	}
}
