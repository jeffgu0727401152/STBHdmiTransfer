
/*
 -------------------------------------------------------------------------
 Copyright (c) 2001, Dr Brian Gladman <brg@gladman.uk.net>, Worcester, UK.
 All rights reserved.

 TERMS

 Redistribution and use in source and binary forms, with or without 
 modification, are permitted subject to the following conditions:

  1. Redistributions of source code must retain the above copyright 
     notice, this list of conditions and the following disclaimer. 

  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the 
     documentation and/or other materials provided with the distribution. 

  3. The copyright holder's name must not be used to endorse or promote 
     any products derived from this software without his specific prior 
     written permission. 

 This software is provided 'as is' with no express or implied warranties 
 of correctness or fitness for purpose.
 -------------------------------------------------------------------------
 Issue Date: 21/01/2002

 This file contains the definitions required to use AES (Rijndael) in C++.
*/

#ifndef _AESCPP_H
#define _AESCPP_H

#include "aes.h"
#include "string.h"

class CAESclass
{
public:
#if defined(AES_BLOCK_SIZE)
    CAESclass() ;
#else
    CAESclass(unsigned int blen = 16) ;
    aes_rval blk_len_enc(unsigned int blen) ;
	aes_rval blk_len_dec(unsigned int blen) ;
#endif

public:
    aes_rval enc_key(const unsigned char in_key[], unsigned int klen) ;
    aes_rval dec_key(const unsigned char in_key[], unsigned int klen) ;

	// in_buf :buffer will be encrypt
	// out_buf :buffer save the encrypt data
	// nlenth :length of in_buf
	// PS:
	// sizeof out_buf must be times of 16
	aes_rval enc_buf(const unsigned char in_buf[], unsigned char out_buf[], aes_32t nlenth) ;

	// in_buf :buffer will be decrypt
	// out_buf :buffer save the decrypt data
	// nlenth :length of in_buf
	// PS:
	// sizeof out_buf must be times of 16
	aes_rval dec_buf(const unsigned char in_buf[], unsigned char out_buf[], aes_32t nlenth) ;

private:
	aes_rval enc_blk(const unsigned char in_blk[], unsigned char out_blk[]) ;
	aes_rval dec_blk(const unsigned char in_blk[], unsigned char out_blk[]) ;

private:
	aes_ctx cx_enc[1];
	aes_ctx cx_dec[1];
};

#endif
