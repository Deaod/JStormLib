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
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_closeFile
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getHashIndexN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getHashIndexN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getCodename1N
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getCodename1N
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getCodename2N
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getCodename2N
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getLocaleN
 * Signature: (J)Lde/deaod/jstormlib/MPQLocale;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQFile_getLocaleN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getBlockIndexN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getBlockIndexN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getFileSizeN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getCompressedSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getCompressedSizeN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFlagsN
 * Signature: (J)Lde/deaod/jstormlib/MPQFileFlags;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQFile_getFlagsN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getPositionN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getPositionN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getKeyN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getKeyN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getKeyUnfixedN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getKeyUnfixedN
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileTimeN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_getFileTimeN
  (JNIEnv *, jclass, jlong);

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
