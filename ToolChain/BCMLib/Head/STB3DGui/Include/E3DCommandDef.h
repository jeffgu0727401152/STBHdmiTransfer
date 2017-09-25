#pragma once

#include "E3DCommon.h"
#include "BaseEvent.h"
#include "UIResource.h"
#include "ImageBuffer.h"

#define E3DCOMMAND_INVALID				 			0x00000000

#define E3DCOMMAND_LOADUIRESOURCE 				0x00000001
#define E3DCOMMAND_CREATETEXTURE 					0x00000002
#define E3DCOMMAND_SETTEXTUREDATA 					0x00000003
#define E3DCOMMAND_UPDATETEXTUREDATA 			0x00000004
#define E3DCOMMAND_CREATETEXTUREKHR 			0x00000005
#define E3DCOMMAND_GETKHRIMAGEBUFFER 			0x00000006
#define E3DCOMMAND_FLUSHKHRIMAGE		 			0x00000007
#define E3DCOMMAND_REMOVETEXTURE  				0x00000008

#define E3DCOMMAND_CAPTURESCREEN  		0x000000010

#define E3DCOMMAND_ADDHOLLOWRECT		0x000000011
#define E3DCOMMAND_DELHOLLOWRECT 		0x000000012

#define E3DCOMMAND_REMOVEUICONTROL		0x000000015
#define E3DCOMMAND_SHOWUICONTROL 		0x000000016

#define E3DCOMMAND_SETPICTUREBOXTEXTURE		0x00000021
#define E3DCOMMAND_SETPICTUREBOXCOLOR		0x00000022
#define E3DCOMMAND_SETPICTUREBOXPOSITION	0x00000023

#define E3DCOMMAND_CREATELISTVIEW		0x00000030
#define E3DCOMMAND_DESTROYLISTVIEW		0x00000031
#define E3DCOMMAND_SETLISTVIEWDATAPROVIDER		0x00000032
#define E3DCOMMAND_UPDATELISTVIEWITEM			0x00000033
#define E3DCOMMAND_GETLISTVIEWBASEITEMINDEX	0x00000038
#define E3DCOMMAND_SETLISTVIEWBASEITEMINDEX	0x00000039
#define E3DCOMMAND_SETLISTVIEWMAXITEMCOUNT	0x0000003A
#define E3DCOMMAND_SETLISTVIEWCLIPRECT		0x00000040
#define E3DCOMMAND_SETLISTVIEWEFFECT        0x00000041

#define E3DCOMMAND_DESTROYLISTVIEWEFFECT 	0x00000050
#define E3DCOMMAND_SETSLIDEEFFECT 			0x00000051
#define E3DCOMMAND_SETFLYINGINEFFECT 		0x00000052
#define E3DCOMMAND_SETROTATEINEFFECT 		0x00000053
#define E3DCOMMAND_SETCOVERFLOWEFFEC 		0x00000054
#define E3DCOMMAND_SETBREAKBUBBLEATTR		0x00000055
#define E3DCOMMAND_BREAKCOVERFLOWITEM		0x00000056
#define E3DCOMMAND_STARTEFFECT 				0x00000057
#define E3DCOMMAND_STOPEFFECT 				0x00000058
#define E3DCOMMAND_ISEFFECTTIMEOVER 		0x00000059

#define LISTVIEWUPDATE_VISIBLE		0x00000001
#define LISTVIEWUPDATE_COLOR		0x00000002
#define LISTVIEWUPDATE_TEXTURE		0x00000004
#define LISTVIEWUPDATE_POSITION		0x00000008
#define LISTVIEWUPDATE_ALL		\
	(LISTVIEWUPDATE_VISIBLE|\
		LISTVIEWUPDATE_COLOR|\
		LISTVIEWUPDATE_TEXTURE|\
		LISTVIEWUPDATE_POSITION)

typedef enum eE3DLVEFFECT_TYPE
{
	E3DLVEffectType_NoEffect=0,
	E3DLVEffectType_Sliding,
	E3DLVEffectType_FlyingIn,
	E3DLVEffectType_FadeIn,
	E3DLVEffectType_RotateIn,
	E3DLVEffectType_Coverflow,
	E3DLVEffectType_FloatingBubble,
} E3DLVEFFECT_TYPE;

typedef enum eE3DLVEFFECT_STATE
{
	E3DLVEffectState_Stopped=0,
	E3DLVEffectState_Running,
	E3DLVEffectState_Stopping
} E3DLVEFFECT_STATE;

class CE3DCommandParam
{
public:
	CE3DCommandParam()
	{
		nE3DCommandType = E3DCOMMAND_INVALID;
		bAsyncProcess=FALSE;
		bCanceled = FALSE;
	}

	virtual ~CE3DCommandParam(){}

	// command type
	int nE3DCommandType;
	CBaseEvent complete;
	BOOL bAsyncProcess;
	BOOL bCanceled;
};

class CE3DCommandLoadUIResourceParam : public CE3DCommandParam
{
public:
	CE3DCommandLoadUIResourceParam()
	{
		nE3DCommandType=E3DCOMMAND_LOADUIRESOURCE;

		pUIResource = NULL;
		cResourceFile = NULL;
		pResKey = NULL;
		nKeyLength = 0;

		bLoadSuccess = FALSE;
	}

public:
	// command data
	CUIResource* pUIResource;
	const char* cResourceFile;
	const BYTE* pResKey;
	int nKeyLength;

	// return value
	BOOL bLoadSuccess;
};

class CE3DCommandCreateTextureParam : public CE3DCommandParam
{
public:
	CE3DCommandCreateTextureParam()
	{
		nE3DCommandType=E3DCOMMAND_CREATETEXTURE;

		pE3DTexture = NULL;
	}

public:
	// return value
	CE3DTexture* pE3DTexture;
};

class CE3DCommandSetTextureDataParam : public CE3DCommandParam
{
public:
	CE3DCommandSetTextureDataParam()
	{
		nE3DCommandType=E3DCOMMAND_SETTEXTUREDATA;
	}

public:
	// command data
	CE3DTexture sE3DTexture;
	CImageBuffer sImgBuf;
};

class CE3DCommandUpdateTextureDataParam : public CE3DCommandParam
{
public:
	CE3DCommandUpdateTextureDataParam()
	{
		nE3DCommandType=E3DCOMMAND_UPDATETEXTUREDATA;

		xStart = 0;
		yStart = 0;
	}

public:
	// command data
	CE3DTexture sE3DTexture;
	CImageBuffer sImgBuf;
	int xStart;
	int yStart;
};

class CE3DCommandCreateTextureKHRParam : public CE3DCommandParam
{
public:
	CE3DCommandCreateTextureKHRParam()
	{
		nE3DCommandType=E3DCOMMAND_CREATETEXTUREKHR;

		nWidth = 0;
		nHeight = 0;
		bBGROrder = FALSE;

		pE3DTexture = NULL;
	}

public:
	// command data
	int nWidth;
	int nHeight;
	BOOL bBGROrder;

	// return value
	CE3DTexture* pE3DTexture;
};

class CE3DCommandGetKHRImageBufferParam : public CE3DCommandParam
{
public:
	CE3DCommandGetKHRImageBufferParam()
	{
		nE3DCommandType=E3DCOMMAND_GETKHRIMAGEBUFFER;

		pImageBuffer = NULL;
	}

public:
	// command data
	CE3DTexture sE3DTexture;

	// return value
	BYTE* pImageBuffer;
};

class CE3DCommandFlushKHRImageParam : public CE3DCommandParam
{
public:
	CE3DCommandFlushKHRImageParam()
	{
		nE3DCommandType=E3DCOMMAND_FLUSHKHRIMAGE;

		pImageBuffer = NULL;
	}

public:
	// command data
	CE3DTexture sE3DTexture;

	// return value
	BYTE* pImageBuffer;
};

class CE3DCommandRemoveTextureParam : public CE3DCommandParam
{
public:
	CE3DCommandRemoveTextureParam()
	{
		nE3DCommandType=E3DCOMMAND_REMOVETEXTURE;
		pE3DTexture = NULL;
	}

public:
	// command data
	CE3DTexture* pE3DTexture;

	// no return value
};

class CE3DCommandCaptureScreenParam : public CE3DCommandParam
{
public:
	CE3DCommandCaptureScreenParam()
	{
		nE3DCommandType=E3DCOMMAND_CAPTURESCREEN;

		xStart = 0;;
		yStart = 0;
		nWidth = 0;
		nHeight = 0;
		bytesPerPixel = 0;
		pImgData = NULL;
	}

public:
	// command data
	int xStart;
	int yStart;
	int nWidth;
	int nHeight;
	int bytesPerPixel;
	BYTE* pImgData;

	// no return value
};

class CE3DCommandAddHollowRectParam : public CE3DCommandParam
{
public:
	CE3DCommandAddHollowRectParam()
	{
		nE3DCommandType=E3DCOMMAND_ADDHOLLOWRECT;

		nID = 0;
		xStart = 0;
		yStart = 0;
		nWidth = 0;
		nHeight = 0;
	}

public:
	// command data
	int nID;
	int xStart;
	int yStart;
	int nWidth;
	int nHeight;
};

class CE3DCommandDelHollowRectParam : public CE3DCommandParam
{
public:
	CE3DCommandDelHollowRectParam()
	{
		nE3DCommandType=E3DCOMMAND_DELHOLLOWRECT;

		nID = 0;
	}

public:
	// command data
	int nID;
};

class CE3DCommandRemoveUIControlParam : public CE3DCommandParam
{
public:
	CE3DCommandRemoveUIControlParam()
	{
		nE3DCommandType=E3DCOMMAND_REMOVEUICONTROL;

		pUIControl = NULL;
	}

public:
	// return value
	I3DUIControl* pUIControl;
};

class CE3DCommandShowUIControlParam : public CE3DCommandParam
{
public:
	CE3DCommandShowUIControlParam()
	{
		nE3DCommandType=E3DCOMMAND_SHOWUICONTROL;

		pUIControl = NULL;
		bVisible = FALSE;
	}

public:
	// command data
	I3DUIControl* pUIControl;
	BOOL bVisible;
};

class CE3DCommandPictureBoxParam : public CE3DCommandParam
{
public:
	CE3DCommandPictureBoxParam()
	{
		pPictureBox = NULL;
	}

public:
	I3DPictureBox* pPictureBox;
};

class CE3DCommandSetPictureBoxTextureParam : public CE3DCommandPictureBoxParam
{
public:
	CE3DCommandSetPictureBoxTextureParam()
	{
		nE3DCommandType=E3DCOMMAND_SETPICTUREBOXTEXTURE;
	}

public:
	// command data
	CE3DTexture sE3DTexture;
};

class CE3DCommandSetPictureBoxColorParam : public CE3DCommandPictureBoxParam
{
public:
	CE3DCommandSetPictureBoxColorParam()
	{
		nE3DCommandType=E3DCOMMAND_SETPICTUREBOXCOLOR;

		uARGB = 0x00000000;
	}

public:
	// command data
	UINT32 uARGB;
};

class CE3DCommandSetPictureBoxPositionParam : public CE3DCommandPictureBoxParam
{
public:
	CE3DCommandSetPictureBoxPositionParam()
	{
		nE3DCommandType=E3DCOMMAND_SETPICTUREBOXPOSITION;

		zPos = 0.0;
		nAngle = 0;
		SetRectXY(&rcBound, 0, 0, 0, 0);
		SetRectXY(&rcControl, 0, 0, 0, 0);
	}

public:
	// command data
	float zPos;
	int nAngle;
	RECT rcBound;
	RECT rcControl;
};

class CE3DCommandListViewParam : public CE3DCommandParam
{
public:
	CE3DCommandListViewParam()
	{
		pListView = NULL;
	}

public:
	I3DListView* pListView;
};

class CE3DCommandCreateListViewParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandCreateListViewParam()
	{
		nE3DCommandType=E3DCOMMAND_CREATELISTVIEW;

		zPos = 0.0;
		dstLeft = 0;
		dstTop = 0;
		dstWidth = 0;
		dstHeight = 0;

		subItemCount = 0;
		rowCount = 0;
		colCount = 0;
		baseItemIndex = 0;
		maxItemCount = 0;
		viewStartCol = 0;
		itemWidth = 0;
		itemHeight = 0;
		itemXSpace = 0;
		itemYSpace = 0;

		bEnableMirror = false;
	}

public:
	// position
	float zPos;
	int dstLeft;
	int dstTop;
	int dstWidth;
	int dstHeight;

	// subitem
	int subItemCount;
	int rowCount;
	int colCount;
	int baseItemIndex;
	int maxItemCount;
	int viewStartCol;
	int itemWidth;
	int itemHeight;
	int itemXSpace;
	int itemYSpace;

	// enable mirror
	bool bEnableMirror;
};

class CE3DCommandDestroyListViewParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandDestroyListViewParam()
	{
		nE3DCommandType=E3DCOMMAND_DESTROYLISTVIEW;
	}
};

class CE3DCommandSetListViewDataProviderParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandSetListViewDataProviderParam()
	{
		nE3DCommandType=E3DCOMMAND_SETLISTVIEWDATAPROVIDER;

		pDataProvide = NULL;
	}

public:
	// data provide
	I3DListViewDataProvider *pDataProvide;
};

class CE3DCommandUpdateListViewItemParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandUpdateListViewItemParam()
	{
		nE3DCommandType=E3DCOMMAND_UPDATELISTVIEWITEM;

		itemIndex = 0;
		subitemIndex = 0;
		uUpdateFlag = 0;
		bVisible = false;
		uARGB = 0x00000000;
		fItemPos = 0.0;
		fLeft = 0.0;
		fTop = 0.0;
		fWidth = 0.0;
		fHeight = 0.0;
	}

public:
	int itemIndex;
	int subitemIndex;
	UINT32 uUpdateFlag;
	bool bVisible;
	UINT32 uARGB;
	CE3DTexture sE3DTexture;
	float fItemPos;
	float fLeft;
	float fTop;
	float fWidth;
	float fHeight;
};

class CE3DCommandGetListViewBaseItemIndexParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandGetListViewBaseItemIndexParam()
	{
		nE3DCommandType=E3DCOMMAND_GETLISTVIEWBASEITEMINDEX;

		baseItemIndex = 0;
	}

public:
	int baseItemIndex;
};

class CE3DCommandSetListViewBaseItemIndexParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandSetListViewBaseItemIndexParam()
	{
		nE3DCommandType=E3DCOMMAND_SETLISTVIEWBASEITEMINDEX;

		baseItemIndex = 0;
	}

public:
	int baseItemIndex;
};

class CE3DCommandSetListViewMaxItemCountParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandSetListViewMaxItemCountParam()
	{
		nE3DCommandType=E3DCOMMAND_SETLISTVIEWMAXITEMCOUNT;

		maxItemCount = 0;
	}

public:
	int maxItemCount;
};

class CE3DCommandSetListViewClipRectParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandSetListViewClipRectParam()
	{
		nE3DCommandType=E3DCOMMAND_SETLISTVIEWCLIPRECT;

		zPos = 0.0;
		dstLeft = 0;
		dstTop = 0;
		dstWidth = 0;
		dstHeight = 0;
	}

public:
	float zPos;
	int dstLeft;
	int dstTop;
	int dstWidth;
	int dstHeight;
};

class CE3DCommandSetListViewEffectParam : public CE3DCommandListViewParam
{
public:
	CE3DCommandSetListViewEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_SETLISTVIEWEFFECT;

		pEffector = NULL;
	}

public:
	I3DListViewEffector *pEffector;
};

class CE3DCommandDestroyListViewEffectParam : public CE3DCommandParam
{
public:
	CE3DCommandDestroyListViewEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_DESTROYLISTVIEWEFFECT;

		pEffector = NULL;
	}

public:
	I3DListViewEffector *pEffector;
};

class CE3DCommandSetSlideEffectParam : public CE3DCommandParam
{
public:
	CE3DCommandSetSlideEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_SETSLIDEEFFECT;

		pEffector = NULL;

		bStepEffect = false;
		fStepOffset = 0.0;
		fSpeed = 0.0;
		fTargetAngle = 0.0;
		fAnglePerSecond = 0.0;
	}

public:
	I3DListViewEffector *pEffector;

	bool bStepEffect;
	// step effect
	float fStepOffset;
	// speed effect
	float fSpeed;//OffsetPerSecond
	float fTargetAngle;
	float fAnglePerSecond;
};

class CE3DCommandSetFlyingInEffectParam : public CE3DCommandParam
{
public:
	CE3DCommandSetFlyingInEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_SETFLYINGINEFFECT;

		pEffector = NULL;;

		direction = t3dLeft;
		moveSpeed = 0.0;
		rotateSpeed = 0.0;
		startHight = 0.0;
		startAngle = 0.0;
	}

public:
	I3DListViewEffector *pEffector;

	MOVE_DIRECTION direction;
	float moveSpeed;
	float rotateSpeed;
	float startHight;
	float startAngle;
};

class CE3DCommandSetRotateInEffectParam : public CE3DCommandParam
{
public:
	CE3DCommandSetRotateInEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_SETROTATEINEFFECT;

		pEffector = NULL;

		angleSpeed = 0.0;
		backfaceDataProvider = NULL;
		backfaceBaseIndex = 0;
	}

public:
	I3DListViewEffector *pEffector;

	float angleSpeed;
	I3DListViewDataProvider* backfaceDataProvider;
	int backfaceBaseIndex;
};

class CE3DCommandSetCoverflowEffectParam : public CE3DCommandParam
{
public:
	CE3DCommandSetCoverflowEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_SETCOVERFLOWEFFEC;

		pEffector = NULL;

		bStepEffect = false;
		fStepOffset = 0.0;
		nTarget = 0;
	}

public:
	I3DListViewEffector *pEffector;

	bool bStepEffect;
	// step effect
	float fStepOffset;
	// speed effect
	int nTarget;
};

class CE3DCommandSetBreakBubbleAttrParam : public CE3DCommandParam
{
public:
	CE3DCommandSetBreakBubbleAttrParam()
	{
		nE3DCommandType=E3DCOMMAND_SETBREAKBUBBLEATTR;

		pEffector = NULL;
	}

public:
	I3DListViewEffector *pEffector;
	BREAKBUBBLE_ATTRIBUTE attrib;
};

class CE3DCommandBreakCoverFlowItemParam : public CE3DCommandParam
{
public:
	CE3DCommandBreakCoverFlowItemParam()
	{
		nE3DCommandType=E3DCOMMAND_BREAKCOVERFLOWITEM;

		pEffector = NULL;
		nItemIndex = 0;
		nStartX = 0;
		nStartY = 0;
		zPos = 0.0;
	}

public:
	I3DListViewEffector *pEffector;
	int nItemIndex;
	int nStartX;
	int nStartY;
	float zPos;
};

class CE3DCommandStartEffectParam : public CE3DCommandParam
{
public:
	CE3DCommandStartEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_STARTEFFECT;

		pEffector = NULL;
	}

public:
	I3DListViewEffector *pEffector;
};

class CE3DCommandStopEffectParam : public CE3DCommandParam
{
public:
	CE3DCommandStopEffectParam()
	{
		nE3DCommandType=E3DCOMMAND_STOPEFFECT;

		pEffector = NULL;
		forceStop = false;
	}

public:
	I3DListViewEffector *pEffector;
	bool forceStop;
};

class CE3DCommandIsEffectTimeOverParam : public CE3DCommandParam
{
public:
	CE3DCommandIsEffectTimeOverParam()
	{
		nE3DCommandType=E3DCOMMAND_ISEFFECTTIMEOVER;

		pEffector = NULL;

		isTimeOver = false;
	}

public:
	I3DListViewEffector *pEffector;

	// return value
	bool isTimeOver;
};
