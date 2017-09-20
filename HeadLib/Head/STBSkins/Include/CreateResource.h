/*
 * CreateResource.h
 *
 *  Created on: 2013-1-1
 *      Author: kyo
 */

#include "ResComposer.h"

#ifdef __cplusplus
extern "C" {
#endif

void CreateResource(
	const char *cDataFolder,
	const char* cResourceFile,
	const BYTE* pResKey,
	int nKeyLength);

#if defined(__cplusplus)
}
#endif
