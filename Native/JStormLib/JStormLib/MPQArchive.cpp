#include "MPQArchive.h"
#include "Common.h"
#include <jni.h>
#include <Windows.h>
#include <StormLib.h>

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_openArchive
  (JNIEnv *env, jclass clazz, jstring name, jint priority, jint flags, jobject mpq)
{
    int result;

    const TCHAR *str_name = jGetStringChars(env, name);
    if (str_name == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    jclass mpq_clazz = env->GetObjectClass(mpq);
    jfieldID mpq_fid = env->GetFieldID(mpq_clazz, "value", "J");
    long long mpq_val = env->GetLongField(mpq, mpq_fid);

    result = SFileOpenArchive(str_name, priority, flags, (HANDLE*) &mpq_val);

    jReleaseStringChars(env, name, str_name);

    env->SetLongField(mpq, mpq_fid, mpq_val);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_createArchive
  (JNIEnv *env, jclass clazz, jstring name , jint flags, jint maxFileCount, jobject mpq)
{
    int result;

    const TCHAR *str_name = jGetStringChars(env, name);
    if (str_name == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    jclass mpq_clazz = env->GetObjectClass(mpq);
    jfieldID mpq_fid = env->GetFieldID(mpq_clazz, "value", "J");
    long long mpq_val = env->GetLongField(mpq, mpq_fid);

    result = SFileCreateArchive(str_name, flags, maxFileCount, (HANDLE*) &mpq_val);

    jReleaseStringChars(env, name, str_name);

    env->SetLongField(mpq, mpq_fid, mpq_val);

    return result!=0;
}

JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_addListFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring name)
{
    int result;

    const char *str_name = env->GetStringUTFChars(name, NULL);
    if (str_name == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileAddListFile((HANDLE) mpq, str_name);

    env->ReleaseStringUTFChars(name, str_name);

    return result!=0;
}

JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setLocale
  (JNIEnv *env, jclass clazz, jint newLocale)
{
    SFileSetLocale(newLocale);
}

JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getLocale
  (JNIEnv *env, jclass clazz)
{
    return SFileGetLocale();
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_flushArchive
  (JNIEnv *env, jclass clazz, jlong mpq)
{
    return SFileFlushArchive((HANDLE) mpq);
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_closeArchive
  (JNIEnv *env, jclass clazz, jlong mpq)
{
    return SFileCloseArchive((HANDLE) mpq);
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_setMaxFileCount
  (JNIEnv *env, jclass clazz, jlong mpq, jint maxFileCount)
{
    return SFileSetMaxFileCount((HANDLE) mpq, maxFileCount);
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_compactArchive
  (JNIEnv *env, jclass clazz, jlong mpq, jstring listFile, jboolean reserved)
{
    bool result;

    const char *str_listFile = env->GetStringUTFChars(listFile, NULL);
    if (str_listFile == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileCompactArchive((HANDLE) mpq, str_listFile, reserved!=0);

    env->ReleaseStringUTFChars(listFile, str_listFile);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_openPatchArchive
  (JNIEnv *env, jclass clazz, jlong mpq, jstring name, jstring patchPathPrefix, jint flags)
{
    int result;

    const TCHAR *str_name = jGetStringChars(env, name);
    const char *str_patchPathPrefix = env->GetStringUTFChars(patchPathPrefix, NULL);
    if (str_name == NULL || str_patchPathPrefix == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileOpenPatchArchive((HANDLE) mpq, str_name, str_patchPathPrefix, flags);

    jReleaseStringChars(env, name, str_name);

    env->ReleaseStringUTFChars(patchPathPrefix, str_patchPathPrefix);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_isPatchedArchive
  (JNIEnv *env, jclass clazz, jlong mpq)
{
    return SFileIsPatchedArchive((HANDLE) mpq);
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_addFileEx
  (JNIEnv *env, jclass clazz, jlong mpq, jstring fileName, jstring archivedName, jint flags, jint compression, jint compressionNext)
{
    int result;

    const TCHAR *str_fileName = jGetStringChars(env, fileName);
    const char *str_archivedName = env->GetStringUTFChars(archivedName, NULL);
    if (str_fileName == NULL || str_archivedName == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileAddFileEx((HANDLE) mpq, str_fileName, str_archivedName, flags, compression, compressionNext);

    jReleaseStringChars(env, fileName, str_fileName);

    env->ReleaseStringUTFChars(archivedName, str_archivedName);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_createFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring archivedName, jlong fileTime, jint fileSize, jint locale, jint flags, jobject file)
{
    int result;

    const char *str_archivedName = env->GetStringUTFChars(archivedName, NULL);
    if (str_archivedName == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    jclass file_clazz = env->GetObjectClass(file);
    jfieldID file_fid = env->GetFieldID(file_clazz, "value", "J");
    long long file_val = env->GetLongField(file, file_fid);

    result = SFileCreateFile((HANDLE) mpq, str_archivedName, fileTime, fileSize, locale, flags, (HANDLE*) &file_val);

    env->ReleaseStringUTFChars(archivedName, str_archivedName);

    env->SetLongField(file, file_fid, file_val);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_openFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring name, jint scope, jobject file)
{
    int result;

    const char *str_name = env->GetStringUTFChars(name, NULL);
    if (str_name == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    jclass file_clazz = env->GetObjectClass(file);
    jfieldID file_fid = env->GetFieldID(file_clazz, "value", "J");
    long long file_val = env->GetLongField(file, file_fid);

    result = SFileOpenFileEx((HANDLE) mpq, str_name, scope, (HANDLE*) &file_val);

    env->ReleaseStringUTFChars(name, str_name);

    env->SetLongField(file, file_fid, file_val);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_hasFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring name)
{
    int result;

    const char *str_name = env->GetStringUTFChars(name, NULL);
    if (str_name == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileHasFile((HANDLE) mpq, str_name);

    env->ReleaseStringUTFChars(name, str_name);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_renameFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring oldName, jstring newName)
{
    int result;

    const char *str_oldName = env->GetStringUTFChars(oldName, NULL);
    const char *str_newName = env->GetStringUTFChars(newName, NULL);
    if (str_oldName == NULL || str_newName == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileRenameFile((HANDLE) mpq, str_oldName, str_newName);

    env->ReleaseStringUTFChars(oldName, str_oldName);
    env->ReleaseStringUTFChars(newName, str_newName);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_removeFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring fileName, jint searchScope)
{
    int result;

    const char *str_fileName = env->GetStringUTFChars(fileName, NULL);
    if (str_fileName == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileRemoveFile((HANDLE) mpq, str_fileName, searchScope);
    
    env->ReleaseStringUTFChars(fileName, str_fileName);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_getArchiveInfo
  (JNIEnv *env, jclass clazz, jlong mpq, jint infoType, jbyteArray data, jint dataMaxSize, jobject dataSize)
{
    int result;

    jbyte* ptr_data = env->GetByteArrayElements(data, NULL);

    jclass dataSize_clazz = env->GetObjectClass(dataSize);
    jfieldID dataSize_fid = env->GetFieldID(dataSize_clazz, "value", "I");
    long dataSize_val = env->GetIntField(dataSize, dataSize_fid);

    result = SFileGetFileInfo((HANDLE) mpq, infoType, ptr_data, dataMaxSize, (LPDWORD) &dataSize_val);

    env->ReleaseByteArrayElements(data, ptr_data, 0);

    env->SetIntField(dataSize, dataSize_fid, dataSize_val);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_verifyFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring fileName, jint flags)
{
    int result;

    const char *str_fileName = env->GetStringUTFChars(fileName, NULL);
    if (str_fileName == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileVerifyFile((HANDLE) mpq, str_fileName, flags);

    env->ReleaseStringUTFChars(fileName, str_fileName);

    return result!=0;
}

JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_verifyArchive
  (JNIEnv *env, jclass clazz, jlong mpq)
{
    return SFileVerifyArchive((HANDLE) mpq);
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_extractFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring toExtract, jstring extracted, jint searchScope)
{
    int result;

    const TCHAR *str_extracted = jGetStringChars(env, extracted);
    const char *str_toExtract = env->GetStringUTFChars(toExtract, NULL);
    if (str_extracted == NULL || str_toExtract == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = SFileExtractFile((HANDLE) mpq, str_toExtract, str_extracted, searchScope);

    jReleaseStringChars(env, extracted, str_extracted);

    env->ReleaseStringUTFChars(toExtract, str_toExtract);

    return result!=0;
}

JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_findFirstFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring mask, jobject fileFindData, jstring listFile)
{
    long long result;
    SFILE_FIND_DATA ptr_fileFindData;

    const char *str_mask = env->GetStringUTFChars(mask, NULL);
    const char *str_listFile = env->GetStringUTFChars(listFile, NULL);
    if (str_mask == NULL || str_listFile == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = (DWORD) SFileFindFirstFile((HANDLE) mpq, str_mask, &ptr_fileFindData, str_listFile);
    
    jFillFindData(env, &ptr_fileFindData, fileFindData);
    env->ReleaseStringUTFChars(mask, str_mask);
    env->ReleaseStringUTFChars(listFile, str_listFile);

    return result;
}

JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_listFindFirstFile
  (JNIEnv *env, jclass clazz, jlong mpq, jstring listFile, jstring mask, jobject fileFindData)
{
    long long result;
    SFILE_FIND_DATA ptr_fileFindData;

    const char *str_mask = env->GetStringUTFChars(mask, NULL);
    const char *str_listFile = env->GetStringUTFChars(listFile, NULL);
    if (str_mask == NULL || str_listFile == NULL) {
        return false; /* OutOfMemoryError already thrown */
    }

    result = (DWORD) SListFileFindFirstFile((HANDLE) mpq, str_listFile, str_mask, &ptr_fileFindData);

    jFillFindData(env, &ptr_fileFindData, fileFindData);
    env->ReleaseStringUTFChars(mask, str_mask);
    env->ReleaseStringUTFChars(listFile, str_listFile);

    return result;
}