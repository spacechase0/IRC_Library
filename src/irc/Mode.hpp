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
