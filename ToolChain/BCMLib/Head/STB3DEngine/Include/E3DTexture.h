#pragma once

#include <E3DTextureSP.h>

// images should be ARGB32

class APIEXPORT CE3DTexture
{
public:
	CE3DTexture();
	virtual ~CE3DTexture();

public:
	void Create(
		bool isKHRTexture,
		uint textureID,
		TEXTURE_FREE_FUNC pfnFree);
	void Delete();

	void SetE3DTexture(
		CE3DTexture *pE3DTexture);

public:
	bool HasE3DTexture();
	uint GetE3DTextureID();

private:
	void SetE3DTextureSP(
		CE3DTextureSP *pE3DTextureSP);

	// must call this in locked
	CE3DTextureSP* GetE3DTextureSP();

	CE3DTexture& operator= (const CE3DTexture& e)
	{
		return *this;
	}

private:
	CE3DTextureSP* mpE3DTextureSP;
};
