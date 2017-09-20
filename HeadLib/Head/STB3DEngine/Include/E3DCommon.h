/*
 * common.h
 *
 *  Created on: 2012-4-2
 *      Author: chengchen
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "E3DConfig.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "typedefines.h"
#include "Enjoy3DInterfaces.h"

// 使用 DbgOutput 替代原本的定义
#if 0
#ifdef ANDROID
#include <android/log.h>
#endif

//
// DEBUG Message输出宏定义
//
#ifdef ANDROID
#define  LOG_TAG    "Enjoy3DEngine"
#define	EMSG(formatString, args...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, formatString, ##args)
#define WMSG(formatString, args...)	__android_log_print(ANDROID_LOG_WARN,LOG_TAG, formatString, ##args)
#define	INFO(formatString, args...)	  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, formatString, ##args)
#else
#if DEBUG_LEVEL > MSG_WARN
#define	EMSG(formatString, args...)	fprintf(stderr, formatString, ##args)
#define WMSG(formatString, args...)	{}
#define	INFO(formatString, args...)	{}
#elif DEBUG_LEVEL > MSG_INFO
#define	EMSG(formatString, args...)	fprintf(stderr, formatString, ##args)
#define WMSG(formatString, args...)	fprintf(stderr, formatString, ##args)
#define	INFO(formatString, args...)	{}
#else
#define	EMSG(formatString, args...)	fprintf(stderr, formatString, ##args)
#define WMSG(formatString, args...)	fprintf(stderr, formatString, ##args)
#define	INFO(formatString, args...)	fprintf(stderr, formatString, ##args)
#endif
#endif
#else
#include "DbgOutput.h"
#define	EMSG(formatString, args...)	LOGMSG(DBG_LEVEL_E, formatString, ##args)
#define WMSG(formatString, args...)	LOGMSG(DBG_LEVEL_W, formatString, ##args)
#define	INFO(formatString, args...)	LOGMSG(DBG_LEVEL_I, formatString, ##args)
#endif

//
// RESULT值的粗略判定
//
static inline bool FAILED(const RESULT& res)
{
	return res < 0;
}

static inline bool SUCCEEDED(const RESULT& res)
{
	return res >= 0;
}

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

static inline uint64 GetCurrMonoTime(void)
{
	struct timespec ts;
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts.tv_sec = mts.tv_sec;
	ts.tv_nsec = mts.tv_nsec;
#else
	clock_gettime(CLOCK_MONOTONIC, &ts);
#endif

	return (((uint64)ts.tv_sec)*1000000 + ((uint64)ts.tv_nsec)/1000);
}

//
// Shader文本块
//
#define SHADERPROGRAM(name)  static const char* name
#define TEXTBLOCK(text)	#text



#endif /* COMMON_H_ */
