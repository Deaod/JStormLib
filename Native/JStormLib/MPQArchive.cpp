#include "MPQArchive.h"
#include "Common.h"
#include <StormLib.h>
#include <JString.h>
#include <JArray.h>
#include <JniEnv.h>
#include <JniHelper.h>
#include <memory>
#include <algorithm>

using std::unique_ptr;

#define C_MPQCompactCallback "de/deaod/jstormlib/MPQCompactCallback"
#define F_MPQCompactCallback JNI_ClassToField(C_MPQCompactCallback)

#define M_compactArchiveCallback "compactArchiveCallback"
#define S_compactArchiveCallback JNI_METHOD_4(JNI_void, F_MPQCompactCallback, JNI_int, JNI_long, JNI_long)

#define C_MPQAddFileCallback "de/deaod/jstormlib/MPQAddFileCallback"
#define F_MPQAddFileCallback JNI_ClassToField(C_MPQAddFileCallback)

#define M_addFileCallback "addFileCallback"
#define S_addFileCallback JNI_METHOD_4(JNI_void, F_MPQAddFileCallback, JNI_int, JNI_int, JNI_boolean)

#define C_MPQBlock "de/deaod/jstormlib/data/MPQBlock"
#define C_MPQHash "de/deaod/jstormlib/data/MPQHash"
#define C_MPQUserDataHeader "de/deaod/jstormlib/data/MPQUserDataHeader"

#define F_MPQBlock JNI_ClassToField(C_MPQBlock)
#define F_MPQHash JNI_ClassToField(C_MPQHash)
#define F_MPQUserDataHeader JNI_ClassToField(C_MPQUserDataHeader)

class MPQCallbackData {
    jclass clazz;
    jobject callback;

public:

    jclass getClass() {
        return this->clazz;
    }

    jobject getCallback() {
        return this->callback;
    }

    void setClass(jclass cls) {
        JniEnv jenv;
        
        if (this->clazz) {
            jenv.DeleteGlobalRef(this->clazz);
        }

        if (cls) {
            this->clazz = reinterpret_cast<jclass>(jenv.NewGlobalRef(cls));
        } else {
            this->clazz = cls;
        }
    }

    void setCallback(jobject callback) {
        JniEnv jenv;

        if (this->callback) {
            jenv.DeleteGlobalRef(this->callback);
        }

        if (callback) {
            this->callback = jenv.NewGlobalRef(callback);
        } else {
            this->callback = callback;
        }
    }

    ~MPQCallbackData() {
        JniEnv jenv;
        
        if (this->clazz) {
            jenv.DeleteGlobalRef(this->clazz);
        }
        
        if (this->callback) {
            jenv.DeleteGlobalRef(this->callback);
        }
    }
};

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    createArchive
 * Signature: (Ljava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_createArchive
  (JNIEnv *env, jclass /*clazz*/, jstring name, jint flags, jint maxFileCount)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JTString jstr_name(env, name);
    jlong mpqHandle = 0;

    jboolean result = SFileCreateArchive(
        reinterpret_cast<const TCHAR*>(jstr_name.getCString()),
        flags,
        maxFileCount,
        reinterpret_cast<HANDLE*>(&mpqHandle)
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    }

    return mpqHandle;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    openArchive
 * Signature: (Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_openArchive
  (JNIEnv *env, jclass /*clazz*/, jstring name, jint flags)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JTString jstr_name(env, name);
    jlong mpqHandle = 0;
    JString aname(env, name);

    jboolean result = SFileOpenArchive(
        jstr_name.getCString(),
        0,
        flags,
        reinterpret_cast<HANDLE*>(&mpqHandle)
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    }

    return mpqHandle;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    addListFile
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_addListFile
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring name)
JNIH_EXCEPTION_TRAP_BEGIN() {
    jint error;
    JString jstr_name(env, name);

    error = SFileAddListFile(reinterpret_cast<HANDLE>(mpq), jstr_name.getCString());
    
    ErrorCodeToException(env, error);

} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setLocale
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setLocale
  (JNIEnv *env, jclass /*clazz*/, jint locale)
{
    SFileSetLocale(locale);
}

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getNativeLocale
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getNativeLocale
  (JNIEnv *env, jclass /*clazz*/)
{
    return SFileGetLocale();
}

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    flushArchive
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_flushArchive
  (JNIEnv *env, jclass /*clazz*/, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN() {
    if (!SFileFlushArchive(reinterpret_cast<HANDLE>(mpq))) {
        ErrorCodeToException(env, GetLastError()); 
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    closeArchive
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_closeArchive
  (JNIEnv *env, jclass /*clazz*/, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN() {
    if (!SFileCloseArchive(reinterpret_cast<HANDLE>(mpq))) {
        ErrorCodeToException(env, GetLastError()); 
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setMaxFileCount
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setMaxFileCount
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jint maxFileCount)
JNIH_EXCEPTION_TRAP_BEGIN() {
    if (!SFileSetMaxFileCount(reinterpret_cast<HANDLE>(mpq), maxFileCount)) {
        ErrorCodeToException(env, GetLastError()); 
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    compactArchive
 * Signature: (JLjava/lang/String;Z)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_compactArchive
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring listFile, jboolean /*reserved*/)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrListFile(env, listFile);
    
    if (!SFileCompactArchive(reinterpret_cast<HANDLE>(mpq), jstrListFile.getCString(), 0)) {
        ErrorCodeToException(env, GetLastError()); 
    }
} JNIH_EXCEPTION_TRAP_END2

static void WINAPI DefaultCompactCallback(void* userData, DWORD workType, ULONGLONG bytesProcessed, ULONGLONG bytesTotal) {
    MPQCallbackData *callbackData = reinterpret_cast<MPQCallbackData*>(userData);
    
    JniEnv env;
    jmethodID methodID = env.GetStaticMethodID(callbackData->getClass(), M_compactArchiveCallback, S_compactArchiveCallback);
    env.CallStaticVoidMethod(callbackData->getClass(), methodID, callbackData->getCallback(), workType, bytesProcessed, bytesTotal);

    if (workType == CCB_CLOSING_ARCHIVE) {
        delete callbackData;
    }
}

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setCompactCallback
 * Signature: (JLde/deaod/jstormlib/MPQCompactCallback;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setCompactCallback
  (JNIEnv *env, jclass clazz, jlong mpq, jobject callback)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    MPQCallbackData *callbackData = new MPQCallbackData;
    callbackData->setClass(clazz);
    callbackData->setCallback(callback);

    SFileSetCompactCallback(reinterpret_cast<HANDLE>(mpq), &DefaultCompactCallback, callbackData);
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    openPatchArchive
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_openPatchArchive
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring name, jstring patchPathPrefix, jint flags)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JTString jstrName(env, name);
    JString jstrPatchPathPrefix(env, patchPathPrefix);

    jboolean result = SFileOpenPatchArchive(
        reinterpret_cast<HANDLE>(mpq),
        reinterpret_cast<const TCHAR*>(jstrName.getCString()),
        jstrPatchPathPrefix.getCString(),
        flags
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    isPatchedArchive
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_isPatchedArchive
  (JNIEnv *env, jclass /*clazz*/, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN() {
    return SFileIsPatchedArchive(reinterpret_cast<HANDLE>(mpq));
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    addFileEx
 * Signature: (JLjava/lang/String;Ljava/lang/String;III)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_addFileEx
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring fileName, jstring archivedName, jint flags,
  jint compression, jint compressionNext)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JTString jstrFileName(env, fileName);
    JString jstrArchivedName(env, archivedName);

    jboolean result = SFileAddFileEx(
        reinterpret_cast<HANDLE>(mpq),
        reinterpret_cast<const TCHAR*>(jstrFileName.getCString()),
        jstrArchivedName.getCString(),
        flags,
        compression,
        compressionNext
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END

static void WINAPI DefaultAddFileCallback(void * userData, DWORD bytesWritten, DWORD bytesTotal, bool finalCall) {
    MPQCallbackData *callbackData = reinterpret_cast<MPQCallbackData*>(userData);

    JniEnv env;
    jmethodID methodID = env.GetStaticMethodID(callbackData->getClass(), M_addFileCallback, S_addFileCallback);
    env.CallStaticVoidMethod(callbackData->getClass(), methodID, callbackData->getCallback(), bytesWritten, bytesTotal, finalCall);

    if (finalCall) {
        delete callbackData;
    }
}

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    setAddFileCallback
 * Signature: (JLde/deaod/jstormlib/MPQAddFileCallback;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_setAddFileCallback
  (JNIEnv *env, jclass clazz, jlong mpq, jobject callback)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    MPQCallbackData *callbackData = new MPQCallbackData;
    callbackData->setClass(clazz);
    callbackData->setCallback(callback);

    SFileSetAddFileCallback(reinterpret_cast<HANDLE>(mpq), &DefaultAddFileCallback, callbackData);
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    hasFile
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_hasFile
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring name)
JNIH_EXCEPTION_TRAP_BEGIN() {
    jboolean result;
    JString jstrName(env, name);
    
    result = SFileHasFile(reinterpret_cast<HANDLE>(mpq), jstrName.getCString());
    if ((!result) && (GetLastError() != ERROR_FILE_NOT_FOUND)) {
        ErrorCodeToException(env, GetLastError());
    }
    return result;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getArchiveInfo
 * Signature: (JI)[B
 */
//JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQArchive_getArchiveInfo
//  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jint infoType)
//JNIH_EXCEPTION_TRAP_BEGIN() {
//    jint dataSize = 0;
//    jboolean result;
//
//    result = SFileGetFileInfo(reinterpret_cast<HANDLE>(mpq), infoType, NULL, 0, reinterpret_cast<LPDWORD>(&dataSize));
//
//    if ((!result) && (GetLastError() != ERROR_INSUFFICIENT_BUFFER)) {
//        ErrorCodeToException(env, GetLastError());
//    } else {
//        JByteArray data(env, dataSize);
//        
//        result = SFileGetFileInfo(reinterpret_cast<HANDLE>(mpq), infoType, data.getData(), dataSize, reinterpret_cast<LPDWORD>(&dataSize));
//
//        if (!result) {
//            ErrorCodeToException(env, GetLastError());
//        }
//
//        return data.getArray();
//    }
//} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getArchiveNameN
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_de_deaod_jstormlib_MPQArchive_getArchiveNameN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    DWORD length;

    SFileGetFileInfo(reinterpret_cast<HANDLE>(mpq), SFileMpqFileName, NULL, 0, &length);

    unique_ptr<TCHAR[]> archiveName(new TCHAR[length]);
    BOOL success = SFileGetFileInfo(reinterpret_cast<HANDLE>(mpq), SFileMpqFileName, archiveName.get(), length, &length);

    if (success) {
        JTString str(env, archiveName.get());
        return str.getJString();
    } else {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getUserDataOffsetN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_getUserDataOffsetN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getUserDataHeaderN
 * Signature: (J)Lde/deaod/jstormlib/data/MPQUserDataHeader;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQArchive_getUserDataHeaderN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    TMPQUserData header;

    BOOL success = SFileGetFileInfo(reinterpret_cast<HANDLE>(mpq), SFileMpqUserDataHeader, &header, sizeof(header), NULL);

    if (success) {
        jclass mpqUserDataHeaderClass = jenv.FindClass(C_MPQUserDataHeader);
        jmethodID constructor = jenv.GetMethodID(mpqUserDataHeaderClass, JNI_Constructor, JNI_CONSTRUCTOR_3(JNI_int, JNI_int, JNI_int));

        return jenv.NewObject(mpqUserDataHeaderClass, constructor, header.cbUserDataSize, header.dwHeaderOffs, header.cbUserDataHeader);
    } else {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getUserDataN
 * Signature: (J)[B
 */
JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQArchive_getUserDataN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    DWORD length;
    SFileGetFileInfo(reinterpret_cast<HANDLE>(mpq), SFileMpqUserData, NULL, 0, &length);

    unique_ptr<BYTE[]> userData(new BYTE[length]);
    BOOL success = SFileGetFileInfo(reinterpret_cast<HANDLE>(mpq), SFileMpqUserData, userData.get(), length, &length);

    if (success) {
        JByteArray result(env, length);

        memcpy(result.getData(), userData.get(), length);
        result.release();

        return result.getArray();
    } else {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHeaderOffsetN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_getHeaderOffsetN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHeaderSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getHeaderSizeN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHeaderN
 * Signature: (J)Lde/deaod/jstormlib/data/MPQHeader;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQArchive_getHeaderN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    //TMPQHeader header;


} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHetTableOffsetN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_getHetTableOffsetN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHetTableSizeN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_getHetTableSizeN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHetHeaderN
 * Signature: (J)Lde/deaod/jstormlib/data/MPQHetHeader;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQArchive_getHetHeaderN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHetTableN
 * Signature: (J)Lde/deaod/jstormlib/data/MPQHetTable;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQArchive_getHetTableN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getBetTableOffsetN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_getBetTableOffsetN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getBetTableSizeN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_getBetTableSizeN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getBetHeaderN
 * Signature: (J)Lde/deaod/jstormlib/data/MPQBetHeader;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQArchive_getBetHeaderN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getBetTableN
 * Signature: (J)Lde/deaod/jstormlib/data/MPQBetTable;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQArchive_getBetTableN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {

} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getArchiveSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getArchiveSizeN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint archiveSize = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqArchiveSize,
        &archiveSize,
        4,
        NULL
    );

    return archiveSize;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getHashTableSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getHashTableSizeN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint hashTableSize = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqHashTableSize,
        &hashTableSize,
        4,
        NULL
    );

    return hashTableSize;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getBlockTableSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getBlockTableSizeN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint blockTableSize = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqBlockTableSize,
        &blockTableSize,
        4,
        NULL
    );

    return blockTableSize;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getMPQDataN
 * Signature: (J)[Lde/deaod/jstormlib/data/MPQHash;
 */
JNIEXPORT jobjectArray JNICALL Java_de_deaod_jstormlib_MPQArchive_getMPQDataN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jclass blockClass = jenv.FindClass(C_MPQBlock);
    jclass hashClass = jenv.FindClass(C_MPQHash);
    jclass localeClass = jenv.FindClass(C_MPQLocale);
    jclass fileFlagsClass = jenv.FindClass(C_MPQFileFlags);

    jmethodID hashConstructor = jenv.GetMethodID(hashClass, JNI_Constructor, JNI_CONSTRUCTOR_0());
    jmethodID blockConstructor = jenv.GetMethodID(blockClass, JNI_Constructor, JNI_CONSTRUCTOR_0());
    jmethodID localeFromInteger = jenv.GetStaticMethodID(localeClass, "fromInteger", JNI_METHOD_1(F_MPQLocale, JNI_int));
    jmethodID fileFlagsFromInteger = jenv.GetStaticMethodID(fileFlagsClass, "fromInteger", JNI_METHOD_1(F_MPQFileFlags, JNI_int));

    jobject emptyBlock = NULL;
    jobject deletedBlock = NULL;

    {
        jfieldID field = jenv.GetStaticFieldID(blockClass, "EMPTY", F_MPQBlock);
        emptyBlock = jenv.GetStaticObjectField(blockClass, field);
        field = jenv.GetStaticFieldID(blockClass, "DELETED", F_MPQBlock);
        deletedBlock = jenv.GetStaticObjectField(blockClass, field);
    }

    DWORD lengthNeeded = 0;
    jint hashTableSize = 0;
    jint blockTableSize = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqHashTableSize,
        &hashTableSize,
        4,
        &lengthNeeded
    );
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqBlockTableSize,
        &blockTableSize,
        4,
        &lengthNeeded
    );

    unique_ptr<TMPQHash[]> hashTable(new TMPQHash[hashTableSize]);
    unique_ptr<TMPQBlock[]> blockTable(new TMPQBlock[blockTableSize]);
    unique_ptr<jobject[]> blockTableCache(new jobject[blockTableSize]);
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqHashTable,
        hashTable.get(),
        sizeof(TMPQHash) * hashTableSize,
        &lengthNeeded
    );
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqBlockTable,
        blockTable.get(),
        sizeof(TMPQBlock) * blockTableSize,
        &lengthNeeded
    );

    memset(blockTableCache.get(), 0, sizeof(jobject) * blockTableSize);

    jobjectArray hashArray = jenv.NewObjectArray(hashTableSize, hashClass, NULL);

    for(int i = 0; i < hashTableSize; i++) {
        jobject hash = jenv.NewObject(hashClass, hashConstructor);
        jenv.SetField(hash, "filePathHashA", JNI_int, &(hashTable[i].dwName1));
        jenv.SetField(hash, "filePathHashB", JNI_int, &(hashTable[i].dwName2));

        jobject locale = jenv.CallStaticObjectMethod(localeClass, localeFromInteger, hashTable[i].lcLocale);
        jenv.SetField(hash, "locale", F_MPQLocale, &locale);

        jobject block = NULL;
        DWORD blockIndex = hashTable[i].dwBlockIndex;
        switch(blockIndex) {
        case HASH_ENTRY_FREE:
            block = emptyBlock;
            break;

        case HASH_ENTRY_DELETED:
            block = deletedBlock;
            break;

        default:
            if (blockTableCache[blockIndex] == NULL) {
                block = jenv.NewObject(blockClass, blockConstructor);

                // initialize block
                jenv.SetField(block, "filePosition", JNI_int, &(blockTable[blockIndex].dwFilePos));
                jenv.SetField(block, "compressedSize", JNI_int, &(blockTable[blockIndex].dwCSize));
                jenv.SetField(block, "fileSize", JNI_int, &(blockTable[blockIndex].dwFSize));

                jobject flags = jenv.CallStaticObjectMethod(fileFlagsClass, fileFlagsFromInteger, blockTable[blockIndex].dwFlags);
                jenv.SetField(block, "flags", F_MPQFileFlags, &flags);

                blockTableCache[blockIndex] = block;
            } else {
                block = blockTableCache[blockIndex];
            }
            break;
        }

        jenv.SetField(hash, "block", F_MPQBlock, blockTableCache[blockIndex]);

        //

        jenv.SetObjectArrayElement(hashArray, i, hash);
    }

    return hashArray;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getSectorSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getSectorSizeN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint sectorSize = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqSectorSize,
        &sectorSize,
        4,
        NULL
    );

    return sectorSize;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    getFilesCountN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_getFilesCountN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint filesCount = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqNumberOfFiles,
        &filesCount,
        4,
        NULL
    );

    return filesCount;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    isReadOnlyN
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQArchive_isReadOnlyN
  (JNIEnv *env, jclass, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint readOnly = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(mpq),
        SFileInfoClass::SFileMpqIsReadOnly,
        &readOnly,
        4,
        NULL
    );

    return readOnly != 0;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    verifyFile
 * Signature: (JLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_verifyFile
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring fileName, jint flags)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrFileName(env, fileName);
    return SFileVerifyFile(reinterpret_cast<HANDLE>(mpq), jstrFileName.getCString(), flags);
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    verifyArchive
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQArchive_verifyArchive
  (JNIEnv *env, jclass /*clazz*/, jlong mpq)
JNIH_EXCEPTION_TRAP_BEGIN() {
    return SFileVerifyArchive(reinterpret_cast<HANDLE>(mpq));
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    extractFile
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)Z
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQArchive_extractFile
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring toExtract, jstring extracted, jint searchScope)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrToExtract(env, toExtract);
    JTString jstrExtracted(env, extracted);

    jboolean result = SFileExtractFile(
        reinterpret_cast<HANDLE>(mpq),
        jstrToExtract.getCString(),
        reinterpret_cast<const TCHAR*>(jstrExtracted.getCString()),
        searchScope
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    findFirstFile
 * Signature: (JLjava/lang/String;Lde/deaod/jstormlib/data/MPQFindData;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_findFirstFile
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring mask, jobject fileFindData, jstring listFile)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrMask(env, mask);
    JString jstrListFile(env, listFile);
    SFILE_FIND_DATA findData;
    jlong searchHandle = 0;

    searchHandle = CPointerToJLong(SFileFindFirstFile(reinterpret_cast<HANDLE>(mpq), jstrMask.getCString(), &findData, jstrListFile.getCString()));

    if (searchHandle == NULL) {
        ErrorCodeToException(env, GetLastError());
    } else {
        FillFindData(env, &findData, fileFindData);

        return searchHandle;
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQArchive
 * Method:    listFindFirstFile
 * Signature: (JLjava/lang/String;Ljava/lang/String;Lde/deaod/jstormlib/data/MPQFindData;)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQArchive_listFindFirstFile
  (JNIEnv *env, jclass /*clazz*/, jlong mpq, jstring listFile, jstring mask, jobject fileFindData)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrListFile(env, listFile);
    JString jstrMask(env, mask);
    SFILE_FIND_DATA findData;
    jlong searchHandle = 0;

    searchHandle = CPointerToJLong(SListFileFindFirstFile(reinterpret_cast<HANDLE>(mpq), jstrListFile.getCString(), jstrMask.getCString(), &findData));

    if (searchHandle == NULL) {
        ErrorCodeToException(env, GetLastError());
    } else {
        FillFindData(env, &findData, fileFindData);

        return searchHandle;
    }
} JNIH_EXCEPTION_TRAP_END