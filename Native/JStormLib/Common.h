#ifndef _Common_h
#define _Common_h

#include <JNIHelper.h>
#include <StormLib.h>

void FillFindData(JNIEnv *env, SFILE_FIND_DATA* source, jobject target);

jlong CPointerToJLong(void* pointer);

void ErrorCodeToException(JNIEnv *env, long error);

#endif