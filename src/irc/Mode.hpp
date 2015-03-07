#ifndef IRC_MODE_HPP
#define IRC_MODE_HPP

namespace irc
{
	namespace Mode
	{
		enum Channel
		{
			Anonymous = 1 << 0, // a
			Invite    = 1 << 1, // i
			Moderated = 1 << 2, // m
			NoOutside = 1 << 3, // n
			Quiet     = 1 << 4, // q
			Private   = 1 << 5, // p
			Secret    = 1 << 6, // s
			Reop      = 1 << 7, // r
			OpTopic   = 1 << 8, // t
			
			// These shouldn't be done Add/RemoveChannelFlags
			ChanOwner = 1 << 9, // O
			ChannelOp = 1 << 10, // o
			Voice     = 1 << 11, // v
			
			Key       = 1 << 12, // k
			Limit     = 1 << 13, // l
			
			Ban       = 1 << 14, // b
			BanExcept = 1 << 15, // e
			InviMask  = 1 << 16, // I
		};
		
		enum User
		{
			Invisible    = 1 << 0, // i
			ServerNotice = 1 << 1, // s
			Wallops      = 1 << 2, // w
			Operator     = 1 << 3, // o
		};
	}
}

#endif // IRC_MODE_H
