//
//  XXTEA.h
//
//  Created by Yuming on 12-7-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

/*
 * 此类是对XXTEA官方算法进行的封装，XXTEA信息详见http://en.wikipedia.org/wiki/XXTEA
 */

#ifndef XXTEA_h
#define XXTEA_h

#include "types.h"

// demo
// char cSource[17] = "1111111111111111";
// XXTEA_btea((UINT32 *)cSource, 4, (UINT32 *)cKey);
// XXTEA_btea((UINT32 *)cSource, -4, (UINT32 *)cKey);

BOOL XXTEA_btea(UINT32* v, int n, UINT32* k);

#endif
