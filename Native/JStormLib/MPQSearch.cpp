#include "MPQSearch.h"
#include "Common.h"
#include <StormLib.h>
#include <JniEnv.h>

/*
 * Class:     de_deaod_jstormlib_MPQSearch
 * Method:    findNextFile
 * Signature: (JLde/deaod/jstormlib/data/MPQFindData;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQSearch_findNextFile
  (JNIEnv *env, jclass /*cls*/, jlong find, jobject findFileData)
JNIH_EXCEPTION_TRAP_BEGIN() {
    SFILE_FIND_DATA findData;
    jboolean result = SFileFindNextFile(
        reinterpret_cast<HANDLE>(find),
        &findData
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        FillFindData(env, &findData, findFileData);
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQSearch
 * Method:    findClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQSearch_findClose
  (JNIEnv *env, jclass /*cls*/, jlong find)
JNIH_EXCEPTION_TRAP_BEGIN() {
    if (!SFileFindClose(reinterpret_cast<HANDLE>(find))) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQSearch
 * Method:    listFindNextFile
 * Signature: (JLde/deaod/jstormlib/data/MPQFindData;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQSearch_listFindNextFile
  (JNIEnv *env, jclass /*cls*/, jlong find, jobject findFileData)
JNIH_EXCEPTION_TRAP_BEGIN() {
    SFILE_FIND_DATA findData;
    jboolean result = SListFileFindNextFile(
        reinterpret_cast<HANDLE>(find),
        &findData
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        FillFindData(env, &findData, findFileData);
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQSearch
 * Method:    listFindClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQSearch_listFindClose
  (JNIEnv *env, jclass /*cls*/, jlong find)
JNIH_EXCEPTION_TRAP_BEGIN() {
    if (!SListFileFindClose(reinterpret_cast<HANDLE>(find))) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2
