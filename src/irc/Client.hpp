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

#ifndef IRC_CLIENT_HPP
#define IRC_CLIENT_HPP

#include <SFML/Network.hpp>
#include <queue>

#include "irc/Event.hpp"
#include "irc/Mode.hpp"
#include "irc/ServerStat.hpp"

namespace irc
{
	class Client
	{
		public:
			Client();
			
			bool connect( sf::IpAddress host, sf::Uint16 port = 6667 );
			void disconnect();
			bool isConnected() const;
			
			bool pollEvent( Event& event );
			
			// Registration/login related
			void pass( const std::string& password = "*" );
			void setNickname( const std::string& nickname );
			void user( const std::string& username, const std::string& realname );
			void oper( const std::string& user, const std::string& password );
			void quit( const std::string& message = "" );
			void squit( const std::string& server, const std::string& comment );
			
			// Channel management
			void joinChannel( const std::string& channel, const std::string& key = "" );
			void leaveChannel( const std::string& channel );
			void setChannelTopic( const std::string& channel, const std::string& topic = "" );
			void kickUserFromChannel( const std::string& channel, const std::string& user, const std::string& comment = "" );
			void inviteToChannel( const std::string& nickname, const std::string& channel );
			
			// Channel modes
			void addChannelFlags( const std::string& channel, long modes );
			void removeChannelFlags( const std::string& channel, long modes );
			
			void setChannelLimit( const std::string& channel, int amount = 0 );
			void setChannelKey( const std::string& channel, const std::string& key = "" );
			
			void addChannelBanMask( const std::string& channel, const std::string& mask );
			void removeChannelBanMask( const std::string& channel, const std::string& mask );
			void addChannelBanException( const std::string& channel, const std::string& mask );
			void removeChannelBanException( const std::string& channel, const std::string& mask );
			void addChannelInviteMask( const std::string& channel, const std::string& mask );
			void removeChannelInviteMask( const std::string& channel, const std::string& mask );
			
			void addChannelSpeaker( const std::string& channel, const std::string& user );
			void removeChannelSpeaker( const std::string& channel, const std::string& user );
			void addChannelOp( const std::string& channel, const std::string& user );
			void removeChannelOp( const std::string& channel, const std::string& user );
			void addChannelVoice( const std::string& channel, const std::string& user );
			void removeChannelVoice( const std::string& channel, const std::string& user );
			
			// (TO DO: Come up with a section name.)
			void addUserModes( const std::string& nickname, long modes );
			void removeUserModes( const std::string& nickname, long modes );
			void sendMessage( const std::string& receiver, const std::string& message, bool notice = false );
			
			// Misc
			void getNames( const std::string& channels = "" );
			void listChannels( const std::string& channels = "", const std::string& server = "" );
			
			// Server queries (some may be op-only)
			void queryVersion( const std::string& server = "" );
			void queryStats( ServerStat::Stat stat, const std::string& server = "" );
			void queryLinks( const std::string& remoteServer = "", const std::string& serverMask = "" );
			void queryTime( const std::string& server = "" );
			void connectServers( const std::string& targetServer, sf::Uint16 port = 0, const std::string& remoteServer = "" );
			void trace( const std::string& server = "" );
			void admin( const std::string& server = "" );
			void info( const std::string& server = "" );
			
			// User queries
			void who( const std::string& name = "", bool opOnly = false );
			void whoIs( const std::string& nickmask );
			void whoIs( const std::string& server, const std::string& nickmask );
			void whoWas( const std::string& nickname, size_t count = 0, const std::string& server = "" );
			
			// Misc
			void kill( const std::string& nickname, const std::string& comment );
			void pong( const std::string& str );
		
		private:
			sf::TcpSocket socket;
			std::queue< std::string > messages;
			std::queue< Event > events;
			
			sf::Mutex messageMutex;
			sf::Mutex eventMutex;
			
			sf::Thread thread;
			
			std::string doChannelMode( long modes ) const;
			std::string doUserMode( long modes ) const;
			char doServerStat( ServerStat::Stat stat ) const;
			void addCommand( const std::string command );
			
			inline sf::Socket::Status receiveData( sf::TcpSocket& socket, char buffer[ 512 ], size_t& received ) const
			{
				return socket.receive( buffer, sizeof( buffer ), received );
			}
			
			void process();
			Event processEvent( const std::string& Line );
	};
}

#endif // IRC_CLIENT_HPP
