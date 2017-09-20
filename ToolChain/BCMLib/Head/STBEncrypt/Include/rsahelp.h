#pragma once

#if 0

#include "types.h"

BOOL InitSysLibCrypto();
void DeInitSysLibCrypto();

int rsa_public_encrypt(
	const BYTE* data,
	int data_len,
	const BYTE* key,
	BYTE* encrypted);
int rsa_private_decrypt(
	const BYTE* enc_data,
	int data_len,
	const BYTE* key,
	BYTE* decrypted);

int rsa_private_encrypt(
	const BYTE* data,
	int data_len,
	const BYTE* key,
	BYTE* encrypted);
int rsa_public_decrypt(
	const BYTE* enc_data,
	int data_len,
	const BYTE* key,
	BYTE* decrypted);

void testRSA();

#endif
