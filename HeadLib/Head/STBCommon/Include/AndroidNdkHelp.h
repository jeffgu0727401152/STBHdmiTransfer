#pragma once

#ifdef ANDROID
#include <jni.h>
void InitNativeJavaVM(
	JavaVM* pJavaVM,
	jobject pClazz);

// format "arg1,arg2,...,argn\n"
void NativeCommand(
	const char* cCommand);

int NativeOSDCommand(
	const char* cCommand);
#else
// format "arg1,arg2,...,argn\n"
void NativeCommand(
	const char* cCommand);
#endif
