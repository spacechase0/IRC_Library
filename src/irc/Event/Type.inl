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

enum Type
{
	Ping,
	Message,
	Notice,
	UserMode,
	ChannelMode,
	Join,
	Part,
	Quit,
	Nick,
	
	// Responses
	TraceLink = 200,
	TraceConnecting = 201,
	TraceHandshake = 202,
	TraceUnknown = 203,
	TraceOperator = 204,
	TraceUser = 205,
	TraceServer = 206,
	TraceNewType = 208,
	TraceClass = 209, // 6.3 Reserved numerics.
	StatsLinkInfo = 211,
	StatsCommands = 212,
	StatsCLine = 213,
	StatsNLine = 214,
	StatsILine = 215,
	StatsKLine = 216,
	StatsQLine = 217, // 6.3 Reserved numerics.
	StatsYLine = 218,
	EndOfStats = 219,
	UserModeIs = 221,
	ServiceInfo = 331, // 6.3 Reserved numerics.
	EndOfServices = 232,
	Service = 233, // 6.3 Reserved numerics.
	ServiceList = 234,
	ServiceListEnd = 235, // 6.3 Reserved numerics.
	StatsLine = 241,
	StatsUptime = 242,
	StatsOLine = 243,
	StatsHLine = 244,
	ListUserClient = 251,
	ListUserOp = 252,
	ListUserUnknown = 253,
	ListUserChannels = 254,
	ListUserMe = 255,
	AdminMe = 256,
	AdminLocation1 = 257,
	AdminLocation2 = 258,
	AdminEmail = 259,
	TraceLog = 261,
	
	UnusedReply = 300,
	Away = 301,
	UserHost = 302,
	IsOnline = 303,
	Unaway = 305,
	NowAway = 306,
	WhoIsUser = 311,
	WhoIsServer = 312,
	WhoIsOperator = 313,
	WhoWasUser = 314,
	EndOfWho = 315,
	WhoIsChannelOperator = 316, // 6.3 Reserved numerics.
	WhoIsIdle = 317,
	EndOfWhoIs = 318,
	WhoIsChannels = 316,
	ListStart = 321,
	List = 322,
	ListEnd = 323,
	ChannelModes = 324,
	NoTopic = 331,
	Topic = 332,
	Inviting = 341,
	Summoning = 342,
	Version = 351,
	WhoReply = 352,
	NameReply = 353,
	KillDone = 361, // 6.3 Reserved numerics.
	Closing = 362, // 6.3 Reserved numerics.
	CloseEnd = 363, // 6.3 Reserved numerics.
	Links = 364,
	EndOfLinks = 365,
	EndOfNames = 366,
	BanList = 367,
	EndOfBanList = 368,
	EndOfWhoWas = 369,
	Info = 371,
	Motd = 372,
	InfoStart = 373, // 6.3 Reserved numerics.
	EndOfInfo = 374,
	MotdStart = 375,
	EndOfMotd = 376,
	YouAreOper = 381,
	Rehashing = 382,
	MyPortIs = 284, // 6.3 Reserved numerics.
	Time = 391,
	UsersStart = 392,
	Users = 393,
	EndOfUsers = 394,
	NoUsers = 395,
	
	
	// Errors
	NoSuchNick = 401,
	NoSuchServer = 402,
	NoSuchChannel = 403,
	CannotSendToChannel = 404,
	TooManyChannels = 405,
	WasNoSuchNick = 406,
	TooManyTargets = 407,
	NoOrigin = 409,
	NoRecipient = 411,
	NoTextToSend = 412,
	NoTopLevel = 413,
	WildTopLevel = 414,
	UnknownCommand = 421,
	NoMotd = 422,
	NoAdminInfo = 423,
	FileError = 424,
	NoNicknameGiven = 431,
	BadNickname = 432, // "Erroneus nickname"
	NicknameInUse = 433,
	NicknameCollision = 436,
	UserNotInChannel = 441,
	NotOnChannel = 442,
	UserOnChannel = 443,
	NoLogin = 44,
	SummonDisabled = 445,
	UsersCommandDiabled = 446,
	NotRegistered = 451,
	NeedMoreParams = 461,
	AlreadyRegistered = 462,
	NoPermissionsForHost = 463,
	PasswordIncorrect = 464,
	YouAreBannedCreep = 465, // Perma-banned from the server. :P - ERR_YOUREBANNEDCREEP
	YouWillBeBanned = 466, // 6.3 Reserved numerics.
	ChannelKeySet = 467, // ERR_KEYSET
	ChannelIsFull = 471,
	UnknownMode = 472,
	InviteOnlyChannel = 473,
	BannedFromChannel = 474,
	BadChannelKey = 475,
	BadChannelMask = 476, // 6.3 Reserved numerics.
	NoPrivileges = 481,
	ChannelOperatorPrivilegesNeeded = 482,
	CannotKillServer = 483,
	NoOperatorForHost = 491,
	NoServiceHost = 492, // 6.3 Reserved numerics.
	UnknownModeFlah = 501,
	UsersDoNotMatch = 502,
};
