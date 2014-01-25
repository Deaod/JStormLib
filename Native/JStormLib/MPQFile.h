/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_deaod_jstormlib_MPQFile */

#ifndef _Included_de_deaod_jstormlib_MPQFile
#define _Included_de_deaod_jstormlib_MPQFile
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_de_deaod_jstormlib_MPQFile_getFileName
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    renameFile
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_renameFile
  (JNIEnv *, jclass, jlong, jstring, jstring);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    removeFile
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_removeFile
  (JNIEnv *, jclass, jlong, jstring, jint);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileSize
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_getFileSize
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    setFilePointer
 * Signature: (JJI)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_setFilePointer
  (JNIEnv *, jclass, jlong, jlong, jint);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    readFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_readFile
  (JNIEnv *, jclass, jlong, jbyteArray, jint, jint);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    writeFile
 * Signature: (J[BIII)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_writeFile
  (JNIEnv *, jclass, jlong, jbyteArray, jint, jint, jint);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    closeFile
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_closeFile
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileInfo
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQFile_getFileInfo
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    setFileLocale
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_setFileLocale
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    createFile
 * Signature: (JLjava/lang/String;JIII)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_createFile
  (JNIEnv *, jclass, jlong, jstring, jlong, jint, jint, jint);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    openFile
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_openFile
  (JNIEnv *, jclass, jlong, jstring, jint);

#ifdef __cplusplus
}
#endif
#endif