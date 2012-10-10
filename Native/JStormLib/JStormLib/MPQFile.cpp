#include "MPQFile.h"
#include "Common.h"
#include <jni.h>
#include <Windows.h>
#include <StormLib.h>

JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_getFileSize
  (JNIEnv *env, jclass clazz, jlong file)
{
    DWORD lo;
    DWORD hi;
    lo = SFileGetFileSize((HANDLE) file, &hi);

    return ((unsigned long long) hi << 32L) + (unsigned long long) lo;
}

JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_setFilePointer
  (JNIEnv *env, jclass clazz, jlong file, jlong newPosition, jint moveMethod)
{
    LONG newActualLowerBits, newDesiredLowerBits=newPosition, newHighBits=newPosition>>32;

    newActualLowerBits = SFileSetFilePointer((HANDLE) file, newDesiredLowerBits, &newHighBits, moveMethod);

    return ((jlong)newHighBits)<<32L+(jlong)newActualLowerBits;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_readFile
  (JNIEnv *env, jclass clazz, jlong file, jbyteArray buffer, jint bytesToRead, jobject bytesRead)
{
    int result;

    jsize bufferLength=env->GetArrayLength(buffer);
    jbyte* dataBuffer=env->GetByteArrayElements(buffer, false);

    jclass bytesRead_class=env->GetObjectClass(bytesRead);
    jfieldID bytesRead_fid = env->GetFieldID(bytesRead_class, "value", "I");
    DWORD bytesRead_val=0;

    result = SFileReadFile((HANDLE) file, dataBuffer, min(bytesToRead, bufferLength), &bytesRead_val, NULL);
    
    env->ReleaseByteArrayElements(buffer, dataBuffer, 0);

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_writeFile
  (JNIEnv *env, jclass clazz, jlong file, jbyteArray data, jint size, jint compression)
{
    return false;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_closeFile
  (JNIEnv *env, jclass clazz, jlong file)
{
    return SFileCloseFile((HANDLE) file);
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_getFileName
  (JNIEnv *env, jclass clazz, jlong file, jstring name)
{
    int result;

    //result = SFileGetFileName((HANDLE) file, );

    return result!=0;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_getFileInfo
  (JNIEnv *env, jclass clazz, jlong file, jint, jbyteArray, jint, jobject)
{
    return false;
}

JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_setFileLocale
  (JNIEnv *env, jclass clazz, jlong file, jint)
{
    return false;
}