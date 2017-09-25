/*
 * Enjoy3DInterfaces.h
 *
 *  Created on: 2012-4-2
 *      Author: chengchen
 */

#ifndef ENJOY3DINTERFACES_H_
#define ENJOY3DINTERFACES_H_

#include "typedefines.h"

class I3DRender
{
public:
	virtual RESULT Initialize(
		bool bTransparentBlend) = 0;
	virtual void Uninitialize(void) = 0;
	virtual	void ApplyFrustum(
		float left, float right,
		float bottom, float top,
		float near, float far) = 0;
	virtual void ApplyOrtho(
		float left, float right,
		float bottom, float top,
		float near, float far) = 0;

	virtual void ApplyModeViewTrans(
		const mat4& modeview) = 0;

	virtual void Add3DObject(
		T3DObject* object) = 0;
	virtual void Remove3DObject(
		T3DObject* object) = 0;
	virtual void Clear3DObjects(void) = 0;

	virtual CE3DTexture* CreateTexture() = 0;
	virtual void SetTextureData(
		CE3DTexture* pE3DTexture,
		byte* imgData,
		int width,
		int height,
		int bytesPerPixel,
		bool grayscale) = 0;
	virtual void UpdateTextureData(
		CE3DTexture* pE3DTexture,
		byte* imgData,
		int left,
		int top,
		int width,
		int height,
		int bytesPerPixel) = 0;
	virtual CE3DTexture* CreateTextureKHR(
		int width,
		int height,
		int nBGROrder)=0;
	virtual byte* GetKHRImageBuffer(
		CE3DTexture* pE3DTexture)=0;
	virtual void FlushKHRImage(
		CE3DTexture* pE3DTexture)=0;
	virtual void RemoveTexture(
		CE3DTexture* pE3DTexture) = 0;
	virtual void CaptureScreen(
		int left,
		int top,
		int width,
		int height,
		int bytesPerPixel,
		byte* imgData)=0;

	virtual void Render(void) = 0;

	virtual void AddHollowRect(
		int id,
		float left,
		float top,
		float width,
		float height) = 0;
	virtual void DelHollowRect(
		int id) = 0;

	virtual ~I3DRender(void) {};
};

APIEXPORT I3DRender* E3DCreateGLES2Render(void);
APIEXPORT void E3DDestroyRender(
	I3DRender* render);


class I3DDevice
{
public:
	virtual RESULT Initialize(
		bool isSecondOpenGL,
		int x,
		int y,
		int width,
		int height) = 0;
	virtual void Uninitialize(void) = 0;
	virtual RESULT PreRenderring(void) = 0;
	virtual RESULT PostRenderring(void) = 0;
	virtual void Viewport(
		int x,
		int y,
		int width,
		int height) = 0;
	virtual ~I3DDevice(void) {};
};

APIEXPORT I3DDevice* E3DCreateGlutXDevice(void);
APIEXPORT void E3DDestroyDevice(I3DDevice* dev);

class I3DUpdateState
{
public:
	virtual RESULT PreRenderring(
		uint64 timeline,
		uint32 timeStep) = 0;
	virtual RESULT PostRenderring(
		uint64 timeline,
		uint32 timeStep) = 0;

	virtual ~I3DUpdateState(void) {};
};

class I3DEngine
{
public:
	virtual void Attach3Device(
		I3DDevice* dev) = 0;
	virtual I3DDevice* GetCurr3Device(void) = 0;
	virtual void Attach3DRender(
		I3DRender* render) = 0;
	virtual I3DRender* GetCurr3DRender(void) = 0;
	virtual RESULT Refresh(void) = 0;
	virtual RESULT Initialize(void) = 0;
	virtual void Uninitialize(void) = 0;

	virtual CE3DTexture* CreateTexture() = 0;
	virtual void SetTextureData(
		CE3DTexture* pE3DTexture,
		byte* imgData,
		int width,
		int height,
		int bytesPerPixel,
		bool grayscale) = 0;
	virtual void UpdateTextureData(
		CE3DTexture* pE3DTexture,
		byte* imgData,
		int left,
		int top,
		int width,
		int height,
		int bytesPerPixel) = 0;
	virtual CE3DTexture* CreateTextureKHR(
		int width,
		int height,
		int nBGROrder)=0;
	virtual byte* GetKHRImageBuffer(
		CE3DTexture* pE3DTexture)=0;
	virtual void FlushKHRImage(
		CE3DTexture* pE3DTexture)=0;
	virtual void RemoveTexture(
		CE3DTexture* pE3DTexture) = 0;
	virtual void CaptureScreen(
		int left,
		int top,
		int width,
		int height,
		int bytesPerPixel,
		byte* imgData)=0;

	virtual T3DObject* CreateT3DObject(void) = 0;
	//virtual void DeleteT3DObject(
	//	T3DObject* obj) = 0;
	virtual void Attach3DObject(
		T3DObject* obj) = 0;
	virtual void Remove3DObject(
		T3DObject* obj) = 0;
	//virtual void Move3DObject(T3DObject* obj, const vec3& position) = 0;

	virtual void AddHollowRect(
		int id,
		float left,
		float top,
		float width,
		float height) = 0;
	virtual void DelHollowRect(
		int id) = 0;

	virtual RESULT RegisterUpdateEvent(
		I3DUpdateState* handler) = 0;
	virtual void UnregisterUpdateEvent(
		I3DUpdateState* handler) = 0;

	virtual void ResetTimeLine(void) = 0;
	virtual uint64 GetCurrentTime(void) = 0;

	virtual ~I3DEngine(void) {};
};
APIEXPORT I3DEngine* E3DCreateEnjoy3DEngine(void);
APIEXPORT void E3DDestroyEngine(
	I3DEngine* eng);


class I3DUIControl
{
public:
	//virtual I3DEngine* Set3DEngine(I3DEngine* newEngine) = 0;
	virtual void Show(
		bool visable) = 0;
	virtual void ClearObject(void) = 0;
	virtual void ClearItemGroup(
		T3DItemGroup* group) = 0;

	virtual void SetColor(
		const vec4& color) = 0;
	virtual void SetPosition(
		const vec3& pos,
		const float width,
		const float height) = 0;

	virtual T3DObject& Get3DObject(void) = 0;
	virtual operator T3DObject* (void) = 0;
//	virtual I3DEngine* Get3DEngine(void) = 0;
	virtual void SetDisplayArea(
		float left,
		float top,
		float width,
		float height) = 0;

	virtual ~I3DUIControl(void) {};
};
APIEXPORT void E3DDestroyTDControl(
	I3DUIControl* control);


class I3DListViewDataProvider
{
public:
	virtual RESULT GetItemData(
		ITEM_DATA_TYPE type,
		void* data) = 0;
	virtual RESULT ReleaseItemData(
		ITEM_DATA_TYPE type,
		const void* data) = 0;
	virtual void OnBaseIndexChanged(
		int nNewBaseIndex){};
	virtual void OnBreakBubbleDone(
		int nItemIndex){};

	virtual ~I3DListViewDataProvider(void) {};
};

class I3DListView;

class I3DListViewEffector
{
public:
	virtual void AttachToListView(
		I3DListView* listView) = 0;
	virtual I3DUpdateState* GetWorker(void) = 0;

	virtual void Start(void) = 0;
	virtual void Stop(bool force) = 0;
	virtual void Reset(void) = 0;

	virtual bool IsTimeOver(void) = 0;

	virtual ~I3DListViewEffector(void) {};
};
APIEXPORT void E3DDestroyListViewEffector(
	I3DListViewEffector* listEffector);


class I3DListViewSliding : INTERFACE(I3DListViewEffector)
{
public:
	virtual void SetSpeed(
		const float speed) = 0;
	virtual void RotateTo(
		const float targetAngle,
		const float speed) = 0;
	virtual void Step(
		const float offest) = 0;
	virtual void SetAngle(
		const float angle) = 0;

	virtual ~I3DListViewSliding(void) {};
};
APIEXPORT I3DListViewSliding* E3DCreateListViewSliding(void);



class I3DListViewFlyingIn : INTERFACE(I3DListViewEffector)
{
public:
	virtual void SetAnimationAttribute(
		float moveSpeed,
		float rotateSpeed,
		MOVE_DIRECTION moveDirection,
		float startHight,
		float startAngle = -60.0) = 0;
	virtual ~I3DListViewFlyingIn(void) {};
};
APIEXPORT I3DListViewFlyingIn* E3DCreateListViewFlyingIn(void);



class I3DListViewBubble : INTERFACE(I3DListViewEffector)
{
public:
	virtual void SetAnimationAttribute(
		const float& bottom,
		const float& top,
		const uint32& interval,
		const float& moveSpeed,
		const float& zDistance) = 0;
	virtual ~I3DListViewBubble(void) {};
};
APIEXPORT I3DListViewBubble* E3DCreateListViewBubble(void);

class I3DListViewFloatingBubble : INTERFACE(I3DListViewEffector)
{
public:
	virtual void SetAttribute(FLOATING_BUBBLE_ATTRIBUTE newAttrib) = 0;
	virtual FLOATING_BUBBLE_ATTRIBUTE GetAttribute(void) = 0;

	virtual ~I3DListViewFloatingBubble(void) {};
};
APIEXPORT I3DListViewFloatingBubble* E3DCreateListViewFloatingBubble(void);


class I3DListViewFadeIn : INTERFACE(I3DListViewEffector)
{
public:
	virtual void SetAttrib(
		float speed,
		float gop) = 0;
	virtual ~I3DListViewFadeIn(void) {};
};
APIEXPORT I3DListViewFadeIn* E3DCreateListViewFadeIn(void);

class I3DListViewRotateIn : INTERFACE(I3DListViewEffector)
{
public:
	virtual void SetAttrib(
		float speed,
		I3DListViewDataProvider* newDataProvider,
		int newBaseIndex) = 0;
	virtual ~I3DListViewRotateIn(void) {};
};
APIEXPORT I3DListViewRotateIn* E3DCreateListViewRotateIn(void);


class I3DListViewCoverFlow : INTERFACE(I3DListViewEffector)
{
public:
	virtual void SetAttribute(
		const float& bottomWidth,
		const float& depth,
		const float& angle,
		const float& speed) = 0;
	virtual void SetItemScaleAttr(
		vector<COVERFLOW_ITEMSCALE_ATTRIBUTE> attrib) = 0;
	virtual void SetBreakBubbleAttr(
		BREAKBUBBLE_ATTRIBUTE& attrib) = 0;
	virtual void Step(
		const float& step) = 0;
	virtual void ScrollTo(
		const int& target) = 0;
	virtual void BreakItem(
		int itemIndex,
		float xStart,
		float yStart,
		float zPos) = 0;

	virtual ~I3DListViewCoverFlow(void) {};
};
APIEXPORT I3DListViewCoverFlow* E3DCreateListViewCoverFlow(void);


class I3DListView : INTERFACE(I3DUIControl)
{
public:
	virtual void SetDataProvider(
		I3DListViewDataProvider* provider) = 0;
	virtual I3DListViewDataProvider* GetDataProvider(void) = 0;

	virtual void SetAttribute(
		const E3DListViewAttribute& attrib) = 0;
	virtual E3DListViewAttribute* GetAttribute(void) = 0;
	virtual int GetBaseItemIndex(void) = 0;
	virtual void SetBaseItemIndex(
		const int& newBaseItemIndex) = 0;
	virtual void SetMaxItemCount(
		const int& maxItemCount) = 0;

	virtual void ShowItem(
		int itemIndex,
		bool show) = 0;
	virtual void SetSubItemTexture(
		int itemIndex,
		int subItemIndex,
		CE3DTexture* pNewTexture) = 0;
	virtual void ShowSubItem(
		int itemIndex,
		int subItemIndex,
		bool show) = 0;
	virtual void SetSubItemType(
		int itemIndex,
		int subItemIndex,
		T3DITEM_TYPE type)=0;
	virtual void SetSubItemColor(
		int itemIndex,
		int subItemIndex,
		const vec4& color) = 0;
	virtual void SetSubItemPosition(
		int itemIndex,
		int subItemIndex,
		const vec3& pos,
		const vec2& size) = 0;
	virtual void SetSubItemTexturePos(
		int itemIndex,
		int subItemIndex,
		const vec2& pos,
		const vec2& size) = 0;

	virtual I3DListViewEffector* SetEffector(
		I3DEngine* newEngine,
		I3DListViewEffector* newEffector) = 0;

	virtual void Replace(
		bool show,
		bool itemsToOrigin,
		bool preserve = false) = 0;

	virtual void PrepareItem(
		T3DItemGroup* itemGroup,
		const int& itemIndex,
		const vec3& itemPos,
		I3DListViewDataProvider* dataProvider = NULL) = 0;
	virtual void ReleaseItem(
		T3DItemGroup* itemGroup,
		const int& itemIndex,
		I3DListViewDataProvider* dataProvider = NULL) = 0;
	virtual void AddItem(
		const int& itemIndex,
		const vec3& itemPos,
		const T3DItemGroups::iterator& insertPosconst,
		const GroupData* data = NULL) = 0;
	virtual T3DItemGroups::iterator RemoveItem(
		const int& itemIndex,
		const T3DItemGroups::iterator& erasePos) = 0;
	virtual void ReleaseAllItems(void) = 0;
	virtual void EnableMirro(
		const float& distance,
		const float& height,
		const float& startAlpha) = 0;
	virtual void DisableMirro(void) = 0;

	virtual ~I3DListView(void) {};
};
APIEXPORT I3DListView* E3DCreateTDListView(void);


class I3DPictureBox : INTERFACE(I3DUIControl)
{
public:
	virtual void SetPicture(
		CE3DTexture* pE3DTexture) = 0;
	virtual void SetTexturePos(
		const vec2& pos,
		const vec2& size) = 0;
	virtual void SetAngle(
		const float& angle) = 0;

	virtual ~I3DPictureBox(void) {};
};
APIEXPORT I3DPictureBox* E3DCreateTDPictureBox(void);


#endif /* ENJOY3DINTERFACES_H_ */
