#ifndef _Common_h
#define _Common_h

#include <jni.h>
#include <Windows.h>
#include <StormLib.h>

const TCHAR* jGetStringChars(JNIEnv *env, jstring which);

void jReleaseStringChars(JNIEnv *env, jstring which, const TCHAR * str_which);

void jFillFindData(JNIEnv *env, SFILE_FIND_DATA* source, jobject target);

#endif