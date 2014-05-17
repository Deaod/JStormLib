#ifndef _Common_h
#define _Common_h

#include <JNIHelper.h>
#include <StormLib.h>

#define C_MPQLocale "de/deaod/jstormlib/MPQLocale"
#define F_MPQLocale JNI_ClassToField(C_MPQLocale)

#define C_MPQFileFlags "de/deaod/jstormlib/MPQFileFlags"
#define F_MPQFileFlags JNI_ClassToField(C_MPQFileFlags)

void FillFindData(JNIEnv *env, SFILE_FIND_DATA* source, jobject target);

jlong CPointerToJLong(void* pointer);

void ErrorCodeToException(JNIEnv *env, long error);

#endif