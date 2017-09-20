#ifndef __DBG_OUTPUT_HEADER__
#define __DBG_OUTPUT_HEADER__

#include <stdio.h>
#include "types.h"

#define DBG_LEVEL_D	1
#define DBG_LEVEL_I		2
#define DBG_LEVEL_W	3
#define DBG_LEVEL_E	4

#define DBG_LEVEL_SWITCH		DBG_LEVEL_I

void DbgOutputOpenFile(
	const char *cFileName,
	BOOL bAppend) ;

void DbgOutputCloseFile() ;

void DbgOutput(
	BOOL bWithPrefix,
	const char *fmt,
	...);

void DbgFlush();

#define LOGMSG(level, format, args...) if ((level) >= DBG_LEVEL_SWITCH){DbgOutput(TRUE, format, ##args);}
#define LOGMSGNOPRFIX(level, format, args...) if ((level) >= DBG_LEVEL_SWITCH){DbgOutput(FALSE, format, ##args);}

#endif //__DBG_OUTPUT_HEADER__
