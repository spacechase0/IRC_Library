#ifndef IRC_SERVERSTAT_H
#define IRC_SERVERSTAT_H

namespace irc
{
	namespace ServerStat
	{
		enum Stat
		{
			PeerConnectionList, // Other servers. Conflicted with ServerConnectionList
			LeavesOrHubs,
			AllowedHostList,
			GlobalBanList,
			ServerConnectionList,
			CommandList,
			OpHostList,
			YLines,
			Uptime
		};
	}
}

#endif // IRC_SERVERSTAT_H
