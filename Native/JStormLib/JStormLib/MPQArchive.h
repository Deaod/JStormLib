/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_deaod_jstormlib_MPQArchive */

#ifndef _Included_de_deaod_jstormlib_MPQArchive
#define _Included_de_deaod_jstormlib_MPQArchive
#ifdef __cplusplus
extern "C" {
#endif
#undef de_deaod_jstormlib_MPQArchive_MAX_FILE_COUNT_MIN
#define de_deaod_jstormlib_MPQArchive_MAX_FILE_COUNT_MIN 4L
#undef de_deaod_jstormlib_MPQArchive_MAX_FILE_COUNT_MAX
#define de_deaod_jstormlib_MPQArchive_MAX_FILE_COUNT_MAX 524288L
#undef de_deaod_jstormlib_MPQArchive_DEFAULT_MAX_FILE_COUNT
#define de_deaod_jstormlib_MPQArchive_DEFAULT_MAX_FILE_COUNT 4L
/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    createArchive
 * Signature: (Ljava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_createArchive
  (JNIEnv *, jclass, jstring, jint, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    openArchive
 * Signature: (Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_openArchive
  (JNIEnv *, jclass, jstring, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    addListFile
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_addListFile
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setLocale
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setLocale
  (JNIEnv *, jclass, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getNativeLocale
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getNativeLocale
  (JNIEnv *, jclass);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    flushArchive
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_flushArchive
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    closeArchive
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_closeArchive
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setMaxFileCount
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setMaxFileCount
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    compactArchive
 * Signature: (JLjava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_compactArchive
  (JNIEnv *, jclass, jlong, jstring, jboolean);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setCompactCallback
 * Signature: (JLde/deaod/jstormlib/MPQCompactCallback;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setCompactCallback
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    openPatchArchive
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_openPatchArchive
  (JNIEnv *, jclass, jlong, jstring, jstring, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    isPatchedArchive
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_isPatchedArchive
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    addFileEx
 * Signature: (JLjava/lang/String;Ljava/lang/String;III)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_addFileEx
  (JNIEnv *, jclass, jlong, jstring, jstring, jint, jint, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setAddFileCallback
 * Signature: (JLde/deaod/jstormlib/MPQAddFileCallback;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setAddFileCallback
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    hasFile
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_hasFile
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getArchiveInfo
 * Signature: (JI)[B
 */
JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQArchive_getArchiveInfo
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    verifyFile
 * Signature: (JLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_verifyFile
  (JNIEnv *, jclass, jlong, jstring, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    verifyArchive
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_verifyArchive
  (JNIEnv *, jclass, jlong);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    extractFile
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_extractFile
  (JNIEnv *, jclass, jlong, jstring, jstring, jint);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    findFirstFile
 * Signature: (JLjava/lang/String;Lde/deaod/jstormlib/data/MPQFindData;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_findFirstFile
  (JNIEnv *, jclass, jlong, jstring, jobject, jstring);

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    listFindFirstFile
 * Signature: (JLjava/lang/String;Ljava/lang/String;Lde/deaod/jstormlib/data/MPQFindData;)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_listFindFirstFile
  (JNIEnv *, jclass, jlong, jstring, jstring, jobject);

#ifdef __cplusplus
}
#endif
#endif
