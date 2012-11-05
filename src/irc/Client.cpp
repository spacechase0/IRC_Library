////////////////////////////////////////////////////////////
//
// IRC Client
// Copyright (C) 2012 Chase Warrington (staff@spacechase0.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "irc/Client.h"

#include <iostream>

#include <util/String.hpp>

namespace irc
{
	Client::Client()
	   : socket(),
	     messages(),
	     events(),
	     messageMutex(),
	     eventMutex(),
	     thread( &Client::process, this )
	{
	}
	
	bool Client::connect( sf::IpAddress host, sf::Uint16 port )
	{
		if ( isConnected() )
		{
			disconnect();
		}
		
		bool success = ( socket.connect( host, port ) == sf::Socket::Done );
		socket.setBlocking( false );
		
		if ( success )
		{
			thread.launch();
		}
		
		return success;
	}
	
	void Client::disconnect()
	{
		socket.disconnect();
		thread.wait();
		
		while ( !messages.empty() )
		{
			messages.pop();
		}
		while ( !events.empty() )
		{
			events.pop();
		}
	}
	
	bool Client::isConnected() const
	{
		return ( socket.getLocalPort() != 0 );
	}
	
	bool Client::pollEvent( Event& event )
	{
		sf::Lock lock( eventMutex );
		
		if ( events.empty() )
		{
			return false;
		}
		
		event = events.front();
		events.pop();
		
		return true;
	}
	
	void Client::pass( const std::string& password )
	{
		addCommand( "PASS " + password );
	}
	
	void Client::setNickname( const std::string& nickname )
	{
		addCommand( "NICK " + nickname );
	}
	
	void Client::user( const std::string& username, const std::string& realname )
	{
		addCommand( "USER " + username + " 0 * :" + username );
	}
	
	void Client::oper( const std::string& user, const std::string& password )
	{
		addCommand( "OPER " + user + " " + password );
	}
	
	void Client::quit( const std::string& message )
	{
		if ( message == "" )
		{
			addCommand( "QUIT" );
		}
		else
		{
			addCommand( "QUIT :" + message );
		}
		
		sf::Clock clock;
		while ( isConnected() )
		{
			sf::sleep( sf::milliseconds( 25 ) );
			
			if ( clock.getElapsedTime() >= sf::seconds( 3.f ) )
			{
				socket.disconnect();
				break;
			}
		}
	}
	
	void Client::squit( const std::string& server, const std::string& comment )
	{
		addCommand( "SQUIT " + server + " " + comment );
	}
	
	void Client::joinChannel( const std::string& channel, const std::string& key )
	{
		if ( key == "" )
		{
			addCommand( "JOIN " + channel );
		}
		else
		{
			addCommand( "JOIN " + channel + " " + key );
		}
	}
	
	void Client::leaveChannel( const std::string& channel )
	{
		addCommand( "PART " + channel );
	}
	
	void Client::setChannelTopic( const std::string& channel, const std::string& topic )
	{
		if ( topic == "" )
		{
			addCommand( "TOPIC " + channel );
		}
		else
		{
			addCommand( "TOPIC " + channel + " :" + topic );
		}
	}
	
	void Client::kickUserFromChannel( const std::string& channel, const std::string& user, const std::string& comment )
	{
		if ( comment == "" )
		{
			addCommand( "KICK " + channel + " " + user );
		}
		else
		{
			addCommand( "KICK " + channel + " " + user + " :" + comment );
		}
	}
	
	void Client::inviteToChannel( const std::string& nickname, const std::string& channel )
	{
		addCommand( "INVITE " + nickname + " " + channel );
	}
	
	void Client::addChannelFlags( const std::string& channel, long modes )
	{
		std::string modeStr = doChannelMode( modes );
		if ( modeStr == "" )
		{
			return;
		}
		
		addCommand( "MODE " + channel + " +" + modeStr );
	}
	
	void Client::removeChannelFlags( const std::string& channel, long modes )
	{
		std::string modeStr = doChannelMode( modes );
		if ( modeStr == "" )
		{
			return;
		}
		
		addCommand( "MODE " + channel + " -" + modeStr );
	}
	
	void Client::setChannelLimit( const std::string& channel, int amount )
	{
		if ( amount == 0 )
		{
			addCommand( "MODE " + channel + " -l" );
		}
		else
		{
			addCommand( "MODE " + channel + " +l " + util::toString( amount ) );
		}
	}
	
	void Client::setChannelKey( const std::string& channel, const std::string& key )
	{
		if ( key == "" )
		{
			addCommand( "MODE " + channel + " -k" );
		}
		else
		{
			addCommand( "MODE " + channel + " +k " + key );
		}
	}
	
	void Client::addChannelBanMask( const std::string& channel, const std::string& mask )
	{
		addCommand( "MODE " + channel + " +b " + mask );
	}
	
	void Client::removeChannelBanMask( const std::string& channel, const std::string& mask )
	{
		addCommand( "MODE " + channel + " -b " + mask );
	}
	
	void Client::addChannelBanException( const std::string& channel, const std::string& mask )
	{
		addCommand( "MODE " + channel + " +e " + mask );
	}
	
	void Client::removeChannelBanException( const std::string& channel, const std::string& mask )
	{
		addCommand( "MODE " + channel + " -e " + mask );
	}
	
	void Client::addChannelInviteMask( const std::string& channel, const std::string& mask )
	{
		addCommand( "MODE " + channel + " +I " + mask );
	}
	
	void Client::removeChannelInviteMask( const std::string& channel, const std::string& mask )
	{
		addCommand( "MODE " + channel + " -I " + mask );
	}
	
	void Client::addChannelSpeaker( const std::string& channel, const std::string& user )
	{
		addCommand( "MODE " + channel + " +v " + user );
	}
	
	void Client::removeChannelSpeaker( const std::string& channel, const std::string& user )
	{
		addCommand( "MODE " + channel + " -v " + user );
	}
	
	void Client::addChannelOp( const std::string& channel, const std::string& user )
	{
		addCommand( "MODE " + channel + " +o " + user );
	}
	
	void Client::removeChannelOp( const std::string& channel, const std::string& user )
	{
		addCommand( "MODE " + channel + " -o " + user );
	}
	
	void Client::addChannelVoice( const std::string& channel, const std::string& user )
	{
		addCommand( "MODE " + channel + " +v " + user );
	}
	
	void Client::removeChannelVoice( const std::string& channel, const std::string& user )
	{
		addCommand( "MODE " + channel + " -v " + user );
	}
	
	void Client::addUserModes( const std::string& nickname, long modes )
	{
		std::string modeStr = doUserMode( modes );
		if ( modeStr == "" )
		{
			return;
		}
		
		addCommand( "MODE " + nickname + " +" + modeStr );
	}
	
	void Client::removeUserModes( const std::string& nickname, long modes )
	{
		std::string modeStr = doUserMode( modes );
		if ( modeStr == "" )
		{
			return;
		}
		
		addCommand( "MODE " + nickname + " -" + modeStr );
	}
	
	void Client::sendMessage( const std::string& receiver, const std::string& message, bool notice )
	{
		std::string prefix;
		if ( notice )
		{
			prefix = "NOTICE";
		}
		else
		{
			prefix = "PRIVMSG";
		}
		
		addCommand( prefix + " " + receiver + " :" + message );
	}
	
	void Client::getNames( const std::string& channels )
	{
		if ( channels == "" )
		{
			addCommand( "NAMES" );
		}
		else
		{
			addCommand( "NAMES " + channels );
		}
	}
	
	void Client::listChannels( const std::string& channels, const std::string& server )
	{
		if ( channels == "" )
		{
			addCommand( "LIST" );
		}
		else
		{
			if ( server == "" )
			{
				addCommand( "LIST " + channels );
			}
			else
			{
				addCommand( "LIST " + channels + " " + server );
			}
		}
	}
	
	void Client::queryVersion( const std::string& server )
	{
		if ( server == "" )
		{
			addCommand( "VERSION" );
		}
		else
		{
			addCommand( "VERSION " + server );
		}
	}
	
	void Client::queryStats( ServerStat::Stat stat, const std::string& server )
	{
		char statChar = doServerStat( stat );
		if ( statChar == '\0' )
		{
			return;
		}
		
		if ( server == "" )
		{
			addCommand( "STATS " + statChar );
		}
		else
		{
			addCommand( "STATS " + statChar + std::string( " " + server ) );
		}
	}
	
	void Client::queryLinks( const std::string& remoteServer, const std::string& serverMask )
	{
		if ( remoteServer == "" )
		{
			addCommand( "LINKS" );
		}
		else
		{
			if ( serverMask == "" )
			{
				addCommand( "LINKS " + remoteServer );
			}
			else
			{
				addCommand( "LINKS " + remoteServer + " " + serverMask );
			}
		}
	}
	
	void Client::queryTime( const std::string& server )
	{
		if ( server == "" )
		{
			addCommand( "TIME" );
		}
		else
		{
			addCommand( "TIME " + server );
		}
	}
	
	void Client::connectServers( const std::string& targetServer, sf::Uint16 port, const std::string& remoteServer )
	{
		if ( targetServer == "" )
		{
			addCommand( "LINKS" );
		}
		else
		{
			if ( port == 0 )
			{
				addCommand( "LINKS " + targetServer );
			}
			else
			{
				std::string portStr = util::toString( port );
				if ( remoteServer == "" )
				{
					addCommand( "LINKS " + targetServer + " " + portStr );
				}
				else
				{
					addCommand( "LINKS " + remoteServer + " " + portStr + " " + remoteServer );
				}
			}
		}
	}
	
	void Client::trace( const std::string& server )
	{
		if ( server == "" )
		{
			addCommand( "TRACE" );
		}
		else
		{
			addCommand( "TRACE " + server );
		}
	}
	
	void Client::admin( const std::string& server )
	{
		if ( server == "" )
		{
			addCommand( "ADMIN" );
		}
		else
		{
			addCommand( "ADMIN " + server );
		}
	}
	
	void Client::Client::info( const std::string& server )
	{
		if ( server == "" )
		{
			addCommand( "INFO" );
		}
		else
		{
			addCommand( "INFO " + server );
		}
	}
	
	void Client::who( const std::string& name, bool opOnly )
	{
		if ( name == "" )
		{
			addCommand( "WHO" );
		}
		else
		{
			if ( !opOnly )
			{
				addCommand( "WHO " + name );
			}
			else
			{
				addCommand( "WHO " + name + 'o' );
			}
		}
	}
	
	void Client::whoIs( const std::string& nickmask )
	{
		addCommand( "WHOIS " + nickmask );
	}
	
	void Client::whoIs( const std::string& server, const std::string& nickmask )
	{
		addCommand( "WHOIS " + server + " " + nickmask );
	}
	
	void Client::whoWas( const std::string& nickname, size_t count, const std::string& server )
	{
		if ( count == 0 )
		{
			addCommand( "WHOWAS " + nickname );
		}
		else
		{
			std::string countStr = util::toString( count );
			if ( server == "" )
			{
				addCommand( "WHOWAS " + nickname + " " + countStr );
			}
			else
			{
				addCommand( "WHOWAS " + nickname + " " + countStr + " " + server );
			}
		}
	}
	
	void Client::kill( const std::string& nickname, const std::string& comment )
	{
		addCommand( "KILL " + nickname + " " + comment );
	}
	
	void Client::pong( const std::string& str )
	{
		addCommand( "PONG " + str );
	}
	
	std::string Client::doChannelMode( long modes ) const
	{
		std::string modeStr = "";
		
		if ( modes & Mode::Anonymous )
		{
			modeStr += 'a';
		}
		if ( modes & Mode::Invite )
		{
			modeStr += 'i';
		}
		if ( modes & Mode::Moderated )
		{
			modeStr += 'm';
		}
		if ( modes & Mode::NoOutside )
		{
			modeStr += 'n';
		}
		if ( modes & Mode::Quiet )
		{
			modeStr += 'q';
		}
		if ( modes & Mode::Private )
		{
			modeStr += 'p';
		}
		if ( modes & Mode::Secret )
		{
			modeStr += 's';
		}
		if ( modes & Mode::Reop )
		{
			modeStr += 'r';
		}
		if ( modes & Mode::OpTopic )
		{
			modeStr += 't';
		}
		
		return modeStr;
	}
	
	std::string Client::doUserMode( long modes ) const
	{
		std::string modeStr = "";
		
		if ( modes & Mode::Invisible )
		{
			modeStr += 'i';
		}
		if ( modes & Mode::ServerNotice )
		{
			modeStr += 's';
		}
		if ( modes & Mode::Wallops )
		{
			modeStr += 'w';
		}
		if ( modes & Mode::Operator )
		{
			modeStr += 'o';
		}
		
		return modeStr;
	}
	
	char Client::doServerStat( ServerStat::Stat stat ) const
	{
		using ServerStat::Stat;
		
		switch ( stat )
		{
			case Stat::PeerConnectionList:
				return 'c';
				break;
			
			case Stat::LeavesOrHubs:
				return 'h';
				break;
			
			case Stat::AllowedHostList:
				return 'i';
				break;
			
			case Stat::GlobalBanList:
				return 'k';
				break;
			
			case Stat::ServerConnectionList:
				return 'l';
				break;
			
			case Stat::CommandList:
				return 'm';
				break;
			
			case Stat::OpHostList:
				return 'i';
				break;
			
			case Stat::YLines:
				return 'y';
				break;
			
			case Stat::Uptime:
				return 'u';
				break;
		};
		
		return '\0';
	}
	
	void Client::addCommand( const std::string command )
	{
		sf::Lock lock( messageMutex );
		messages.push( command );
	}
	
	void Client::process()
	{
		std::string buffer;
		bool hasReceived = false;
		
		while ( isConnected() )
		{
			// Events
			{
				sf::Lock lock( eventMutex );
				
				char tmpBuffer[ 512 ] = "";
				size_t received = 0;
				#define RECEIVE_LOOP receiveData( socket, tmpBuffer, received )
				sf::Socket::Status status;
				for ( status = RECEIVE_LOOP; status == sf::Socket::Done; status = RECEIVE_LOOP )
				{
					std::string tmpStr( tmpBuffer, received );
					buffer += tmpStr;
				}
				
				if ( status == sf::Socket::Disconnected or status == sf::Socket::Error )
				{
					socket.disconnect();
					break;
				}
				#undef RECEIVE_LOOP
				
				for ( size_t found = buffer.find( "\r\n" ); found != std::string::npos; found = buffer.find( "\r\n" ) )
				{
					std::string line = buffer.substr( 0, found );
					//std::cout << "<- " << line << std::endl;
					
					Event event = processEvent( line );
					events.push( event );
					
					buffer.erase( 0, found + 2 );
					hasReceived = true;
				}
			}
			
			// Messages
			if ( hasReceived )
			{
				sf::Lock lock( messageMutex );
				
				while ( !messages.empty() )
				{
					std::string message = messages.front() + "\r\n";
					//std::cout << "-> " << message << std::endl;
					
					socket.send( message.data(), message.size() );
					messages.pop();
				}
			}
			
			// Keep CPU usage low
			sf::sleep( sf::milliseconds( 10 ) );
		}
	}
	
	Event Client::processEvent( const std::string& theLine )
	{
		std::string line = theLine;
		Event event;
		
		#include "irc/Client/PrefixProcessor.inl"
		
		std::vector< std::string > tokens = util::tokenize( line, " " );
		if ( tokens.size() < 1 )
		{
			return Event();
		}
		
		#include "irc/Client/EventProcessor.inl"
		
		return event;
	}
}
