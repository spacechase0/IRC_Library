#ifndef IRC_EVENT_H
#define IRC_EVENT_H

#include <string>

namespace irc
{
	class Event
	{
		public:
			#include "irc/Event/Type.inl"
			
			Event();
			Event( const std::string& thePrefix, Type theType );
			Event( const std::string& thePrefix, Type theType, const std::string& theMessage );
			Event( const std::string& thePrefix, Type theType, const std::string& theChannel, const std::string& theMessage );
			
			Type type;
			
			std::string prefix;
			std::string nick;
			std::string user;
			std::string host;
			
			std::string channel;
			std::string message;
			std::string amount;
			std::string mask;
			bool add;
			long mode;
	};
}

#endif // IRC_EVENT_H
