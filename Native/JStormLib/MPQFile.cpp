#include "MPQFile.h"
#include "Common.h"
#include <StormLib.h>
#include <JString.h>
#include <JArray.h>
#include <JniEnv.h>

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_de_deaod_jstormlib_MPQFile_getFileName
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    char fileName[MAX_PATH + 1]; // +1 because of Null termination

    if (!SFileGetFileName(reinterpret_cast<HANDLE>(file), fileName)) {
        ErrorCodeToException(env, GetLastError());
    }

    return jenv.NewStringUTF(fileName);
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    renameFile
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_renameFile
  (JNIEnv *env, jclass /*cls*/, jlong file, jstring oldFileName, jstring newFileName)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrOldFileName(env, oldFileName);
    JString jstrNewFileName(env, newFileName);

    if (!SFileRenameFile(reinterpret_cast<HANDLE>(file), jstrOldFileName.getCString(), jstrNewFileName.getCString())) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    removeFile
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_removeFile
  (JNIEnv *env, jclass /*cls*/, jlong mpq, jstring fileName, jint searchScope)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrFileName(env, fileName);

    if (!SFileRemoveFile(reinterpret_cast<HANDLE>(mpq), jstrFileName.getCString(), searchScope)) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileSize
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_getFileSize
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN() {
    jlong fileSizeHigh = 0;
    jlong fileSizeLow = 0;

    fileSizeLow |= SFileGetFileSize(reinterpret_cast<HANDLE>(file), reinterpret_cast<LPDWORD>(&fileSizeHigh));
    
    return fileSizeLow | (fileSizeHigh << 32);
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    setFilePointer
 * Signature: (JJI)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_setFilePointer
  (JNIEnv *env, jclass /*cls*/, jlong file, jlong newPosition, jint moveMethod)
JNIH_EXCEPTION_TRAP_BEGIN() {
    jint newPosLow = (newPosition & 0x00000000FFFFFFFFull);
    jlong newPosHigh = ((newPosition >> 32) & 0x00000000FFFFFFFFull);
    jlong result = 0;
    
    result = SFileSetFilePointer(reinterpret_cast<HANDLE>(file), newPosLow, reinterpret_cast<LONG*>(&newPosHigh), moveMethod);

    if (result == SFILE_INVALID_SIZE) {
        ErrorCodeToException(env, GetLastError());
    } else {
        return result | (newPosHigh << 32ull);
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    readFile
 * Signature: (J[BII)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_readFile
  (JNIEnv *env, jclass /*cls*/, jlong file, jbyteArray buffer, jint offset, jint bytesToRead)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JByteArray jBuffer(env, buffer);
    jint bytesRead = 0;
    jboolean result;

    result = SFileReadFile(reinterpret_cast<HANDLE>(file), (jBuffer.getData() + offset), bytesToRead, reinterpret_cast<LPDWORD>(&bytesRead), NULL);

    if ((!result) && (GetLastError() != ERROR_HANDLE_EOF)) {
        ErrorCodeToException(env, GetLastError());
    } else {
        return bytesRead;
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    writeFile
 * Signature: (J[BIII)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_writeFile
  (JNIEnv *env, jclass /*cls*/, jlong file, jbyteArray data, jint offset, jint length, jint compression)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JByteArray jData(env, data);

    if (!SFileWriteFile(reinterpret_cast<HANDLE>(file), (jData.getData() + offset), length, compression)) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    closeFile
 * Signature: (J)V
 */
JNIEXPORT jboolean JNICALL Java_de_deaod_jstormlib_MPQFile_closeFile
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN() {
    if (!SFileCloseFile(reinterpret_cast<HANDLE>(file))) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END

///*
// * Class:     de_deaod_jstormlib_MPQFile
// * Method:    getFileInfo
// * Signature: (JI)[B
// */
//JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQFile_getFileInfo
//  (JNIEnv *env, jclass /*cls*/, jlong file, jint infoType)
//JNIH_EXCEPTION_TRAP_BEGIN() {
//    jint dataSize = 0;
//    jboolean result;
//
//    result = SFileGetFileInfo(reinterpret_cast<HANDLE>(file), infoType, NULL, 0, reinterpret_cast<LPDWORD>(&dataSize));
//
//    if ((!result) && (GetLastError() != ERROR_INSUFFICIENT_BUFFER)) {
//        ErrorCodeToException(env, GetLastError());
//    } else {
//        JByteArray data(env, dataSize);
//        
//        result = SFileGetFileInfo(reinterpret_cast<HANDLE>(file), infoType, data.getData(), dataSize, reinterpret_cast<LPDWORD>(&dataSize));
//
//        if (!result) {
//            ErrorCodeToException(env, GetLastError());
//        }
//
//        return data.getArray();
//    }
//} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getHashIndexN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getHashIndexN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint hashIndex = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoHashIndex,
        &hashIndex,
        4,
        NULL
    );

    return hashIndex;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getCodename1N
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getCodename1N
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint codename1 = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoNameHash1,
        &codename1,
        4,
        NULL
    );

    return codename1;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getCodename2N
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getCodename2N
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint codename2 = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoNameHash2,
        &codename2,
        4,
        NULL
    );

    return codename2;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getLocaleN
 * Signature: (J)Lde/deaod/jstormlib/MPQLocale;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQFile_getLocaleN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint locale = 0;
    jobject result;
    jclass mpqLocale = jenv.FindClass(C_MPQLocale);
    jmethodID mpqLocaleFromInteger = jenv.GetStaticMethodID(mpqLocale, "fromInteger", JNI_METHOD_1(F_MPQLocale, JNI_int));

    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoLocale,
        &locale,
        4,
        NULL
    );

    result = jenv.CallStaticObjectMethod(mpqLocale, mpqLocaleFromInteger, locale);

    return result;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getBlockIndexN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getBlockIndexN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint blockIndex = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoFileIndex,
        &blockIndex,
        4,
        NULL
    );

    return blockIndex;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getFileSizeN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint fileSize = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoFileSize,
        &fileSize,
        4,
        NULL
    );

    return fileSize;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getCompressedSizeN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getCompressedSizeN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint compressedSize = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoCompressedSize,
        &compressedSize,
        4,
        NULL
    );

    return compressedSize;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFlagsN
 * Signature: (J)Lde/deaod/jstormlib/MPQFileFlags;
 */
JNIEXPORT jobject JNICALL Java_de_deaod_jstormlib_MPQFile_getFlagsN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint flags = 0;
    jobject result;
    jclass mpqFileFlags = jenv.FindClass(C_MPQFileFlags);
    jmethodID mpqFileFlagsFromInteger = jenv.GetStaticMethodID(mpqFileFlags, "fromInteger", JNI_METHOD_1(F_MPQFileFlags, JNI_int));

    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoFlags,
        &flags,
        4,
        NULL
    );

    result = jenv.CallStaticObjectMethod(mpqFileFlags, mpqFileFlagsFromInteger, flags);

    return result;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getPositionN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getPositionN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint position = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoByteOffset,
        &position,
        4,
        NULL
    );

    return position;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getKeyN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getKeyN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint key = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoEncryptionKey,
        &key,
        4,
        NULL
    );

    return key;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getKeyUnfixedN
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_deaod_jstormlib_MPQFile_getKeyUnfixedN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint keyUnfixed = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoEncryptionKeyRaw,
        &keyUnfixed,
        4,
        NULL
    );

    return keyUnfixed;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    getFileTimeN
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_getFileTimeN
  (JNIEnv *env, jclass /*cls*/, jlong file)
JNIH_EXCEPTION_TRAP_BEGIN_EX(env, jenv) {
    jint fileTime = 0;
    SFileGetFileInfo(
        reinterpret_cast<HANDLE>(file),
        SFileInfoClass::SFileInfoFileTime,
        &fileTime,
        4,
        NULL
    );

    return fileTime;
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    setFileLocale
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_de_deaod_jstormlib_MPQFile_setFileLocale
  (JNIEnv *env, jclass /*cls*/, jlong file, jint newLocale)
JNIH_EXCEPTION_TRAP_BEGIN() {
    if (!SFileSetFileLocale(reinterpret_cast<HANDLE>(file), newLocale)) {
        ErrorCodeToException(env, GetLastError());
    }
} JNIH_EXCEPTION_TRAP_END2

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    createFile
 * Signature: (JLjava/lang/String;JIII)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_createFile
  (JNIEnv *env, jclass /*cls*/, jlong mpq, jstring archivedName, jlong fileTime,
  jint fileSize, jint locale, jint flags)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrArchivedName(env, archivedName);
    jlong file = 0;

    jboolean result = SFileCreateFile(
        reinterpret_cast<HANDLE>(mpq),
        jstrArchivedName.getCString(),
        fileTime,
        fileSize,
        locale,
        flags,
        reinterpret_cast<HANDLE*>(&file)
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        return file;
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQFile
 * Method:    openFile
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_de_deaod_jstormlib_MPQFile_openFile
  (JNIEnv *env, jclass /*cls*/, jlong mpq, jstring name, jint scope)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JString jstrName(env, name);
    jlong file = 0;

    jboolean result = SFileOpenFileEx(
        reinterpret_cast<HANDLE>(mpq),
        jstrName.getCString(),
        scope,
        reinterpret_cast<HANDLE*>(&file)
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        return file;
    }
} JNIH_EXCEPTION_TRAP_END
