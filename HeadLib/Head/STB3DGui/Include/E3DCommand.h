#pragma once

#include "E3DCommandDef.h"
#include "PtrControl.h"
#include "BaseLock.h"
#include "BaseEvent.h"
#include "BaseThread.h"
#include "PictureBox.h"
#include "FontLib.h"

#define ISVALID_TEXTURE(id) ((((uint)id)!=INVALIDATE_TEXTURE) && (id!=0))

// 针对需要实时刷新的数据
// 如鼠标，fps更新，背景更新等，
// 可以在OnRefresh时更新
class IE3DRefreshListener
{
public:
	virtual ~IE3DRefreshListener(void) {}

	virtual void OnRefresh()=0;
};

class CE3DCommand
{
public:
	CE3DCommand();
	virtual ~CE3DCommand();

// call by gl thread
public:
	void InitE3D(
		BOOL isSecondOpenGL,
		BOOL bTransparentBlend,
		int nDispWidth,
		int nDispHeight,
		int nUIWidth,
		int nUIHeight);
	void DeInitE3D();

	int GetUIWidth();
	int GetUIHeight();

	void AddRefreshListener(
		IE3DRefreshListener *pListener);
	void DelRefreshListener(
		IE3DRefreshListener *pListener);
	void EnableRefreshListener(
		BOOL bEnable);
	void Refresh();

	// return left commands count
	int GetLeftCommandCount();

	void ProcessCommands(
		UINT64 uTimeOutUS);

// call by non-gl thread
// 1. 如果操作涉及到 openggl， 则必须加入到 Command List，由E3D主线程处理
// 例如，CreateTexture 等等
// 2. 如果操作涉及到 先后顺序，必须加入到 Command List，以保证先后顺序，例如
// 例如：RemoveUIControl, DestroyListView 等等
// 3. 如果操作会改动到 E3D GL 数据内容，例如 3DObject list，则必须使用同步机制 mGLOperatorLock，
// 如果此操作是可以不等待的，建议加入到 Command List，以免调用者线程阻塞，
// 例如：ShowUIControl 等等
// 4. 如果操作仅与对象本身有关，则直接操作此内容
// 例如：CreateListView

public:
	// E3D 中执行，可以大幅加快texture创建速度
	BOOL LoadUIResource(
		CUIResource *pUIResource,
		const char* cResourceFile,
		const BYTE* pResKey,
		int nKeyLength);

	UINT32 CreateTexture();
	void SetTextureData(
		UINT32 textureID,
		CImageBuffer *pImageBuffer);
	void UpdateTextureData(
		UINT32 textureID,
		CImageBuffer *pImageBuffer,
		int xStart,
		int yStart,
		int nWidth,
		int nHeight);
	UINT32 CreateTextureKHR(
		int nWidth,
		int nHeight,
		BOOL bBGROrder);
	BYTE* GetKHRImageBuffer(
		UINT32 textureID);
	void FlushKHRImage(
		UINT32 textureID);
	void ClearSetTextureDataCmd(
		UINT32 textureID);
	void RemoveTexture(
		UINT32 textureID);

	void CaptureScreen(
		int xStart,
		int yStart,
		int nWidth,
		int nHeight,
		int bytesPerPixel,
		const BYTE* pImgData);

	void AddHollowRect(
		int nID,
		int xStart,
		int yStart,
		int nWidth,
		int nHeight);
	void DelHollowRect(
		int nID);

	void RemoveUIControl(
		I3DUIControl* pUIControl);
	void ShowUIControl(
		I3DUIControl* pUIControl,
		BOOL bVisible);

	I3DPictureBox* CreatePictureBox();

	void SetPictureBoxTexture(
		I3DPictureBox* pPictureBox,
		UINT32 textureID);
	void SetPictureBoxColor(
		I3DPictureBox* pPictureBox,
		UINT32 uARGB);
	void SetPictureBoxPosition(
		I3DPictureBox* pPictureBox,
		float zPos,
		int nAngle,
		RECT rcBound,
		RECT rcControl);
	void ClearPictureBoxCmd(
		I3DPictureBox* pPictureBox,
		int nCommandID);

	BOOL IsListViewCmd(
		int nCmdID);
	BOOL HasListViewCmd(
		I3DListView* pListView);

	I3DListView* CreateListView(
		float zPos,
		RECT rcListView,
		int subItemCount,
		int rowCount,
		int colCount,
		int baseItemIndex,
		int maxItemCount,
		int viewStartCol,
		int itemWidth,
		int itemHeight,
		int itemXSpace,
		int itemYSpace,
		bool bEnableMirror);

	void DestroyListView(
		I3DListView* pListView);

	void SetListViewDataProvider(
		I3DListView* pListView,
		I3DListViewDataProvider *pDataProvide);

	void UpdateListViewItem(
		I3DListView* pListView,
		int itemIndex,
		int subitemIndex,
		UINT32 uUpdateFlag,
		bool bVisible,
		UINT32 uARGB,
		UINT32 textureID,
		float fItemPos,
		float fLeft,
		float fTop,
		float fWidth,
		float fHeight);
	void ClearUpdateListViewItemCmd(
		I3DListView* pListView);

	int GetListViewBaseItemIndex(
		I3DListView* pListView);

	void SetListViewBaseItemIndex(
		I3DListView* pListView,
		int baseItemIndex);

	void SetListViewMaxItemCount(
		I3DListView* pListView,
		int maxItemCount);

	void SetListViewClipRect(
		I3DListView* pListView,
		float zPos,
		int dstLeft,
		int dstTop,
		int dstWidth,
		int dstHeight);

	I3DListViewEffector* CreateListViewEffect(
		I3DListView* pListView,
		E3DLVEFFECT_TYPE effectType);
	void DestroyListViewEffect(
		I3DListViewEffector* pEffector);

	void SetListViewEffect(
		I3DListView* pListView,
		I3DListViewEffector* pEffector);

	void SetFadeInEffectAttr(
		I3DListViewEffector* pEffector,
		float fSpeed,
		float fGop);
	void SetCoverflowEffectAttr(
		I3DListViewEffector* pEffector,
		float fBottomWidth,
		float fDepth,
		float fAngle,
		float fSpeed);
	void SetCoverflowItemScaleAttr(
		I3DListViewEffector* pEffector,
		vector<COVERFLOW_ITEMSCALE_ATTRIBUTE> attrib);
	void SetFloatingBubbleEffectAttr(
		I3DListViewEffector* pEffector,
		float fMinFadingInSpeed,
		float fMaxFadingInSpeed,
		float fMinRadius,
		float fMaxRadius,
		float fMinSpeed,
		float fMaxSpeed,
		float fMinMass,
		float fMaxMass);

	void SetSlideEffect(
		I3DListViewEffector* pEffector,
		bool bStepEffect,
		float fStepOffset,
		float fSpeed,
		float fTargetAngle,
		float fAnglePerSecond);

	void SetFlyingInEffect(
		I3DListViewEffector* pEffector,
		MOVE_DIRECTION direction,
		float moveSpeed,
		float rotateSpeed,
		float startHight,
		float startAngle);

	void SetRotateInEffect(
		I3DListViewEffector* pEffector,
		float angleSpeed,
		I3DListViewDataProvider* backfaceDataProvider,
		int backfaceBaseIndex);

	void SetCoverflowEffect(
		I3DListViewEffector* pEffector,
		bool bStepEffect,
		float fStepOffset,
		int nTarget);

	void SetBreakBubbleAttr(
		I3DListViewEffector* pEffector,
		const BREAKBUBBLE_ATTRIBUTE& attrib);

	void BreakCoverFlowItem(
		I3DListViewEffector* pEffector,
		int nItemIndex,
		int nStartX,
		int nStartY,
		float zPos);

	void StartEffect(
		I3DListViewEffector* pEffector);

	void StopEffect(
		I3DListViewEffector* pEffector,
		bool forceStop);

	bool IsEffectTimeOver(
		I3DListViewEffector* pEffector);

private:
	void ProcessCommand(
		CE3DCommandParam *pCommandParam);

	void ProcessLoadUIResource(
		CE3DCommandLoadUIResourceParam *pLoadUIResourceParam);

	void ProcessCreateTexture(
		CE3DCommandCreateTextureParam *pCreateTextureParam);

	void ProcessSetTextureData(
		CE3DCommandSetTextureDataParam *pSetTextureDataParam);

	void ProcessUpdateTextureData(
		CE3DCommandUpdateTextureDataParam *pUpdateTextureDataParam);

	void ProcessCreateTextureKHR(
		CE3DCommandCreateTextureKHRParam *pCreateTextureKHRParam);

	void ProcessGetKHRImageBuffer(
		CE3DCommandGetKHRImageBufferParam *pGetKHRImageBufferParam);

	void ProcessFlushKHRImage(
		CE3DCommandFlushKHRImageParam *pFlushKHRImageParam);

	void ProcessRemoveTexture(
		CE3DCommandRemoveTextureParam *pRemoveTextureParam);

	void ProcessCaptureScreen(
		CE3DCommandCaptureScreenParam *pCaptureScreenParam);

	void ProcessAddHollowRect(
		CE3DCommandAddHollowRectParam *pAddHollowRectParam);

	void ProcessDelHollowRect(
		CE3DCommandDelHollowRectParam *pDelHollowRectParam);

	void ProcessRemoveUIControl(
		CE3DCommandRemoveUIControlParam *pRemoveUIControlParam);

	void ProcessShowUIControl(
		CE3DCommandShowUIControlParam *pShowUIControlParam);

	void ProcessSetPictureBoxTexture(
		CE3DCommandSetPictureBoxTextureParam *pSetPictureBoxTextureParam);

	void ProcessSetPictureBoxColor(
		CE3DCommandSetPictureBoxColorParam *pSetPictureBoxColorParam);

	void ProcessSetPictureBoxPosition(
		CE3DCommandSetPictureBoxPositionParam *pSetPictureBoxPositionParam);

	void ProcessCreateListView(
		CE3DCommandCreateListViewParam *pCreateListViewParam);

	void ProcessDestroyListView(
		CE3DCommandDestroyListViewParam *pDestroyListViewParam);

	void ProcessSetListViewDataProvider(
		CE3DCommandSetListViewDataProviderParam *pSetListViewDataProviderParam);

	void ProcessUpdateListViewItem(
		CE3DCommandUpdateListViewItemParam *pUpdateListViewItemParam);

	void ProcessGetListViewBaseItemIndex(
		CE3DCommandGetListViewBaseItemIndexParam *pGetListViewBaseItemIndexParam);

	void ProcessSetListViewBaseItemIndex(
		CE3DCommandSetListViewBaseItemIndexParam *pSetListViewBaseItemIndexParam);

	void ProcessSetListViewMaxItemCount(
		CE3DCommandSetListViewMaxItemCountParam *pSetListViewMaxItemCountParam);

	void ProcessSetListViewClipRect(
		CE3DCommandSetListViewClipRectParam *pSetListViewClipRectParam);

	void ProcessDestroyListViewEffect(
		CE3DCommandDestroyListViewEffectParam *pDestroyListViewEffectParam);

	void ProcessSetListViewEffect(
		CE3DCommandSetListViewEffectParam *pSetListViewEffectParam);

	void ProcessSetSlideEffect(
		CE3DCommandSetSlideEffectParam *pSetSlideEffectParam);

	void ProcessSetFlyingInEffect(
		CE3DCommandSetFlyingInEffectParam *pSetFlyingInEffectParam);

	void ProcessSetRotateInEffect(
		CE3DCommandSetRotateInEffectParam *pSetRotateInEffectParam);

	void ProcessSetCoverflowEffect(
		CE3DCommandSetCoverflowEffectParam *pSetCoverflowEffectParam);

	void ProcessSetBreakBubbleAttr(
		CE3DCommandSetBreakBubbleAttrParam *pSetBreakBubbleAttrParam);

	void ProcessBreakCoverFlowItem(
		CE3DCommandBreakCoverFlowItemParam *pBreakCoverFlowItemParam);

	void ProcessStartEffect(
		CE3DCommandStartEffectParam *pStartEffectParam);

	void ProcessStopEffect(
		CE3DCommandStopEffectParam *pStopEffectParam);

	void ProcessIsEffectTimeOver(
		CE3DCommandIsEffectTimeOverParam *pIsEffectTimeOverParam);

private:
	CBaseEvent mCommandEvent;
	pthread_t mThreadID;
	CBaseLock  mE3DCommandListLock;
	CPtrListCtrl mE3DCommandList;

	// IE3DRefreshListener list
	CBaseLock  mE3DRefreshListenerListLock;
	CPtrListCtrl mE3DRefreshListenerList;
	BOOL mRefreshListenerEnable;

	I3DEngine* m3DEng;
	I3DDevice* m3DDevice;
	I3DRender* m3DRender;

	int mDispWidth;
	int mDispHeight;

	int mUIWidth;
	int mUIHeight;
};
