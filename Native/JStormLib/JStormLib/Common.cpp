#include "Common.h"
#include <jni.h>
#include <Windows.h>
#include <StormLib.h>
#include <string>

using namespace std;

const TCHAR* jGetStringChars(JNIEnv *env, jstring which) {
#ifdef UNICODE
    const TCHAR *str_which = (const TCHAR*) env->GetStringChars(which, NULL);
    if (str_which == NULL) {
        return NULL; /* OutOfMemoryError already thrown */
    }
#else
    const TCHAR *str_which = env->GetStringUTFChars(which, NULL);
    if (str_which == NULL) {
        return NULL; /* OutOfMemoryError already thrown */
    }
#endif
    return str_which;
}

void jReleaseStringChars(JNIEnv *env, jstring which, const TCHAR * str_which) {
#ifdef UNICODE
    env->ReleaseStringChars(which, (const jchar*) str_which);
#else
    env->ReleaseStringUTFChars(which, str_which);
#endif
}

void jFillFindData(JNIEnv *env, SFILE_FIND_DATA* source, jobject target) {
    jclass target_class = env->GetObjectClass(target);
    jfieldID fileName_fid = env->GetFieldID(target_class, "fileName", "Ljava/lang/String;");
    jfieldID plainName_fid = env->GetFieldID(target_class, "plainName", "Ljava/lang/String;");
    jfieldID hashIndex_fid = env->GetFieldID(target_class, "hashIndex", "I");
    jfieldID blockIndex_fid = env->GetFieldID(target_class, "blockIndex", "I");
    jfieldID fileSize_fid = env->GetFieldID(target_class, "fileSize", "I");
    jfieldID fileFlags_fid = env->GetFieldID(target_class, "fileFlags", "I");
    jfieldID compSize_fid = env->GetFieldID(target_class, "compSize", "I");
    jfieldID fileTimeLo_fid = env->GetFieldID(target_class, "fileTimeLo", "I");
    jfieldID fileTimeHi_fid = env->GetFieldID(target_class, "fileTimeHi", "I");
    jfieldID locale_fid = env->GetFieldID(target_class, "locale", "I");

    string tmp(source->cFileName, MAX_PATH);
    jstring fileName = env->NewStringUTF(tmp.c_str());
    env->SetObjectField(target, fileName_fid, fileName);
    jstring plainName = env->NewStringUTF(source->szPlainName);
    env->SetObjectField(target, plainName_fid, plainName);
    env->SetIntField(target, hashIndex_fid, source->dwHashIndex);
    env->SetIntField(target, blockIndex_fid, source->dwBlockIndex);
    env->SetIntField(target, fileSize_fid, source->dwFileSize);
    env->SetIntField(target, fileFlags_fid, source->dwFileFlags);
    env->SetIntField(target, compSize_fid, source->dwCompSize);
    env->SetIntField(target, fileTimeLo_fid, source->dwFileTimeLo);
    env->SetIntField(target, fileTimeHi_fid, source->dwFileTimeHi);
    env->SetIntField(target, locale_fid, source->lcLocale);
}