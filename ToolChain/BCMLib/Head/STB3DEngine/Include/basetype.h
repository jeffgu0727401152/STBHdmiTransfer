/*
 * typedefines.h
 *
 *  Created on: 2012-4-2
 *      Author: chengchen
 */

#ifndef COMMONTYPE_H_
#define COMMONTYPE_H_

#include "types.h"

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

#define INVALIDATE_TEXTURE	uint(-1)
#define ISVALID_TEXTURE(id) ((((uint)id)!=INVALIDATE_TEXTURE) && (id!=0))

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
