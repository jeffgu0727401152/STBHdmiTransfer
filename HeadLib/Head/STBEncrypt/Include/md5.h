#ifndef MD5_H
#define MD5_H

#include "types.h"

/* MD5 declaration. */
class MD5 {
public:
	MD5();
	MD5(const BYTE *input, size_t length);
	void update(const BYTE *input, size_t length);
	const BYTE* digest();
	void reset();

private:
	void final();
	void transform(const BYTE block[64]);
	void encode(const UINT32 *input, BYTE *output, size_t length);
	void decode(const BYTE *input, UINT32 *output, size_t length);

	/* class uncopyable */
	MD5(const MD5&);
	MD5& operator=(const MD5&);
private:
	UINT32 _state[4];	/* state (ABCD) */
	UINT32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	BYTE _buffer[64];	/* input buffer */
	BYTE _digest[16];	/* message digest */
	bool _finished;		/* calculate finished ? */

	static const BYTE PADDING[64];	/* padding for calculate */
	static const char HEX[16];
	static const size_t BUFFER_SIZE = 1024;
};

void GetFileMD5(
	const char* cFileName,
	BYTE pMD5Value[16]);
void GetFileMD5(
	FILE *fp,
	BYTE pMD5Value[16]);

#endif/*MD5_H*/
