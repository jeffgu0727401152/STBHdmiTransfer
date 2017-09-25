#pragma once

// wParam: not used
// lParam: not used
#define MSG_HDMIIN_CONNECT 		(WNDMSG_USERBASE+0x1)
#define MSG_HDMIIN_DISCONNECT 	(WNDMSG_USERBASE+0x2)

// wParam: player index
// lParam: complete reason
#define MSG_PLAYER_COMPLETE 		(WNDMSG_USERBASE+0x3)

// wParam: not used
// lParam: not used
#define INPUTWND_BACKMSG		(WNDMSG_USERBASE+0x20)

// wParam: not used
// lParam: not used
#define INPUTWND_CLEARMSG		(WNDMSG_USERBASE+0x21)

// wParam: not used
// lParam: not used
#define INPUTWND_SWITCHIME		(WNDMSG_USERBASE+0x22)

// wParam: wide-char of input
// lParam: not used
#define INPUTWND_WCHARMSG		(WNDMSG_USERBASE+0x23)

// wParam: CSimpleStringW* of input, need delete (CSimpleStringW *)wParam
// lParam: not used
#define INPUTWND_WSTRINGMSG		(WNDMSG_USERBASE+0x24)

// wParam: language type
// lParam: not used
#define INPUTWND_LANGUAGETYPEMSG	(WNDMSG_USERBASE+0x25)

// wParam: wordcount type
// lParam: not used
#define INPUTWND_WORDCOUNTTYPEMSG	(WNDMSG_USERBASE+0x26)

// wParam: not used
// lParam: not used
#define DBTYPE_CHANGED_MSG (WNDMSG_USERBASE+0x90)
