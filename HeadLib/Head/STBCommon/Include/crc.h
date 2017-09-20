// Common/CRC.h

#ifndef __COMMON_CRC_H
#define __COMMON_CRC_H

#include "types.h"

class CCRC
{
  UINT32 _value;
public:
  static UINT32 Table[256];
  static void InitTable();

  CCRC():  _value(0xABCDABCD){}
  void Init() { _value = 0xABCDABCD; }
  void UpdateBYTE(BYTE v);
  void UpdateUINT16(UINT16 v);
  void UpdateUINT32(UINT32 v);
  void UpdateUINT64(UINT64 v);
  void Update(const void *data, size_t size);
  UINT32 GetDigest() const ;
  static UINT32 CalculateDigest(const void *data, size_t size) ;
  static bool VerifyDigest(UINT32 digest, const void *data, size_t size) ;
};

#endif
