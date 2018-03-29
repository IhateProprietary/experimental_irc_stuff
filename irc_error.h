#ifndef __IRC_ERROR_H__
# define __IRC_ERROR_H__

#include "irc_reply.h"

# define ERR_UNKNOW		0			/* undefined */
# define ERR_NOSUCHNICK 401 		/* nickname is unsused */
# define ERR_NOSUCHSERVER 402		/* server doesn't exist */
# define ERR_NOSUCHCHANNEL 403		/* channel doesn't exist */
# define ERR_CANNOTSENDTOCHAN 404	/* cannot send to channel */
# define ERR_TOOMANYCHANNEL 405 	/* max allowed channel joined reached */
# define ERR_WASNOSUCHNICK 406		/* nickname was never used */
# define ERR_TOOMANYTARGETS 407		/* duplicate recipient */
# define ERR_NOORIGIN 409			/* no origin specified */
# define ERR_NORECIPIENT 411
# define ERR_NOTEXTTOSEND 412
# define ERR_NOTOPLEVEL 413
# define ERR_WILDTOPLEVEL 414
# define ERR_UNKNOWNCOMMAND 421
# define ERR_NOMOTD 422
# define ERR_NOADMININFO 423
# define ERR_FILEERROR 424
# define ERR_NONICKNAMEGIVEN 431
# define ERR_ERRONEUSNICKNAME 432
# define ERR_NICKNAMEINUSE 433
# define ERR_NICKCOLLISION 436
# define ERR_USERNOTINCHANNEL 441
# define ERR_NOTONCHANNEL 442
# define ERR_USERONCHANNEL 443
# define ERR_NOLOGIN 444
# define ERR_SUMMONDISABLED 445
# define ERR_USERSDISABLED 446
# define ERR_NOTREGISTERED 451
# define ERR_NEEDMOREPARAMS 461
# define ERR_ALREADYREGISTRED 462
# define ERR_NOPERMFORHOST 463
# define ERR_PASSWDMISMATCH 464
# define ERR_YOUREBANNEDCREEP 465
# define ERR_KEYSET 467
# define ERR_CHANNELISFULL 471
# define ERR_UNKNOWNMODE 472
# define ERR_INVITEONLYCHAN 473
# define ERR_BANNEDFROMCHAN 474
# define ERR_BADCHANNELKEY 475
# define ERR_NOPRIVILEGES 481
# define ERR_CHANOPRIVSNEEDED 482
# define ERR_CANTKILLSERVER 483
# define ERR_NOOPERHOST 491
# define ERR_UMODEUNKNOWNFLAG 501
# define ERR_USERSDONTMATCH 502

extern irc_no_t	irc_errstring[];

#endif