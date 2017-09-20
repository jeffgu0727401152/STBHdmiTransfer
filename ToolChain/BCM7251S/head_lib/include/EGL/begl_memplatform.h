/*=============================================================================
Copyright (c) 2014 Broadcom Europe Limited.
All rights reserved.
=============================================================================*/

#ifndef __BEGL_MEMPLATFORM_H__
#define __BEGL_MEMPLATFORM_H__

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
   BEGL_MemCacheLineSize,
   BEGL_MemLargestBlock,
   BEGL_MemFree,
   BEGL_MemPrintHeapData
} BEGL_MemInfoType;

typedef void *BEGL_MemHandle;

typedef struct BEGL_MemoryInterface
{
   BEGL_MemHandle (*Alloc)(void *context, size_t numBytes, size_t alignment, uint32_t flags, const char *desc);
   void           (*Free)(void *context, BEGL_MemHandle h);
   void          *(*Map)(void *context, BEGL_MemHandle h, size_t offset, size_t length, uint32_t usage_flags);
   void           (*Unmap)(void *context, BEGL_MemHandle h, void *cpu_ptr, size_t length);
   uint32_t       (*Lock)(void *context, BEGL_MemHandle h);
   void           (*Unlock)(void *context, BEGL_MemHandle h);
   void           (*FlushCache)(void *context, BEGL_MemHandle h, void *pCached, size_t numBytes);
   uint64_t       (*GetInfo)(void *context, BEGL_MemInfoType type);

   void           *context;
} BEGL_MemoryInterface;


extern void BEGL_RegisterMemoryInterface(BEGL_MemoryInterface *iface);

typedef void (*PFN_BEGL_RegisterMemoryInterface)(BEGL_MemoryInterface *);

#ifdef __cplusplus
}
#endif

#endif
