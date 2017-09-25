#pragma once

#include "basetype.h"

typedef void (*TEXTURE_FREE_FUNC)(bool isKHRTexture, uint textureID);

class APIEXPORT CE3DTextureSP
{
public:
	// for normal buffer
	CE3DTextureSP(
		bool isKHRTexture,
		uint textureID,
		TEXTURE_FREE_FUNC pfnFree);

	virtual ~CE3DTextureSP();

public:
	void AddRef();
	void Release();
	int GetRefCount();

public:
	uint GetE3DTextureID();

private:
	CE3DTextureSP& operator= (const CE3DTextureSP& e)
	{
		return *this;
	}

private:
	int mRefCount;
	bool mIsKHRTexture;
	uint mTextureID;
	TEXTURE_FREE_FUNC mFreeFunction;
};
