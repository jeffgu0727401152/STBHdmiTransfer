/*
 * typedefines.h
 *
 *  Created on: 2012-4-2
 *      Author: chengchen
 */

#ifndef TYPEDEFINES_H_
#define TYPEDEFINES_H_

#include "Vector.h"
#include "Matrix.h"
#include <vector>
#include <deque>
using std::vector;
using std::deque;
//
// 基础数据类型
//
typedef unsigned char 	byte;

typedef short int 		int16;
typedef long			int32;
typedef long long 		int64;

typedef unsigned int			uint;
typedef unsigned short int 		uint16;
typedef unsigned long			uint32;
typedef unsigned long long 		uint64;

typedef enum tag_T3DITEM_TYPE
{
	t3dUnknowType,
	t3dRectangle,
	t3dCircle,

	t3dItemTypeCount
} T3DITEM_TYPE;

typedef enum tag_T3D_FLAGS
{
	t3dVisiable = 0x1,		// 本项是否显示
	t3dModelTrans = 0x400,	// 后面的项都执行此变换
	t3dMirror = 0x800,	// 此项有镜像
	t3dScissor = 0x1000, // 此项有裁剪区
	//t3dCreateOffScreenData = 0x1000, // 此项需要创建离屏渲染技术
	t3dItetorControl = 0x10000	// 手动指定Render时的顺序
} T3D_FLAGS;


struct T3DVertex
{
	vec3 Position;
	vec2 TextureCoord;
	vec4 Color;
};

typedef vector<T3DVertex> T3DVertices;

struct T3DItem
{
	T3DITEM_TYPE type;
	uint flags;
	mat4 modelTrans;
	uint texture;
	T3DVertices vertices;
};

typedef struct tag_GroupData
{
	uint32 i32;
	float f32;
	void* pointer;
}GroupData;

typedef deque<T3DItem*> T3DItems;

struct T3DItemGroup
{
	uint flags;
	mat4 modelTrans;
	T3DItems items;
	mat4 mirroTrans;
	vec3 position;
	int nextItetor;
	GroupData data;
};

typedef deque<T3DItemGroup*> T3DItemGroups;

struct T3DObject
{
	uint flags;
	mat4 modelTrans;
//	void* offScreenData;
//	ivec2 offScreenSize;
	T3DItemGroups itemGroups;
	int nextItetor;
	vec2 scissorPos;
	vec2 scissorSize;
};

struct E3DListViewAttribute
{
	vec3 position;
	vec2 size;
	int subItemCount;
	int rowCount;
	int colCount;
	vec2 itemSize;
	float itemXGop;
	float itemYGop;
	int viewStartCol;
	int baseItemIndex;
	int maxItemCount;
	bool mirroEnable;
	float mirroDist;
	float mirroHeight;
	float mirroStartAlph;
};

typedef enum tag_MOVE_DIRECTION
{
	t3dLeft,
	t3dRight,
	t3dFloatInOut
}MOVE_DIRECTION;

//
// RESULT相关定义
//
typedef enum tag_RESULT_VAL
{
	resultOK = 0,
	resultFailed = -1,
} RESULT;

//
// 所有的接口都使用公共虚拟继承
//
#define INTERFACE(x) public virtual x


//
// I3DListViewDataProvider所要用到的数据类型
//
typedef enum tag_ITEM_DATA_TYPE
{
	itemDataPicture,
	itemDataListView
}ITEM_DATA_TYPE;


struct ITEM_DATA_PICTURE
{
	uint texture;
};

struct ITEM_DATA_LISTVIEW
{
	int itemIndex;
	int subItemIndex;
	bool show;
	//bool isFont;
	T3DITEM_TYPE type;
	vec2 itemSize;
	vec3 position;
	vec2 size;
	uint texture;
	vec4 color;
};

//I3DListViewFloatingBubble所用到的数据类型
struct FLOATING_BUBBLE_ATTRIBUTE
{
	float minFadingInSpeed;
	float maxFadingInSpeed;
	float minRadius;
	float maxRadius;
	float minSpeed;
	float maxSpeed;
	float minMass;
	float maxMass;
};

struct COVERFLOW_ITEMSCALE_ATTRIBUTE
{
	// offset
	vec2 ratio;
	vec2 offset;
};

struct BREAKBUBBLE_ATTRIBUTE
{
	int breakBubbleCount;
	float breakBubbleMinSpeed;
	float breakBubbleMaxSpeed;
	float breakBubbleMinFade;
	float breakBubbleMaxFade;
	uint breakBubbletexture;
	vec2 breakBubbleSize;
};

#define INVALIDATE_TEXTURE	uint(-1)

//
// 默认情况下gcc导出所有全局符号。
// 启用-fvisibility=hidden编译参数后, 默认不导出，
// 用APIEXPORT指明需要导出的符号。
// 导出函数的动作只有在动态库生成时需要做，
// 所以BUILD_DYNAMIC_LIB只有在Enjoy3DEngine动态库的工程中需要设定，
// 其它使用这个库的工程中不需要也不能定义这个宏
//
// BUILD_DYNAMIC_LIB是在工程的属性中设定的预定义宏
//
#ifdef BUILD_DYNAMIC_LIB
#define APIEXPORT	__attribute__ ((visibility ("default")))
#else
#define APIEXPORT
#endif

#endif /* TYPEDEFINES_H_ */
