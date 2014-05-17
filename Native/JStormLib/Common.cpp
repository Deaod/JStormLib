#include "Common.h"
#include <JniEnv.h>
#include <Windows.h>
#include <StormLib.h>
#include <string>

void FillFindData(JNIEnv *env, SFILE_FIND_DATA* source, jobject target)
{
    JniEnv jenv(env);

    jstring fileName = jenv.NewStringUTF(source->cFileName);
    jenv.SetField(target, "fileName", F_String, &fileName);

    jstring plainName = jenv.NewStringUTF(source->szPlainName);
    jenv.SetField(target, "plainName", F_String, &plainName);

    jenv.SetField(target, "hashIndex", JNI_int, &(source->dwHashIndex));
    jenv.SetField(target, "blockIndex", JNI_int, &(source->dwBlockIndex));
    jenv.SetField(target, "fileSize", JNI_int, &(source->dwFileSize));
    jenv.SetField(target, "fileFlags", JNI_int, &(source->dwFileFlags));
    jenv.SetField(target, "compSize", JNI_int, &(source->dwCompSize));
    jenv.SetField(target, "fileTimeLo", JNI_int, &(source->dwFileTimeLo));
    jenv.SetField(target, "fileTimeHi", JNI_int, &(source->dwFileTimeHi));
    jenv.SetField(target, "locale", JNI_int, &(source->lcLocale));
}

jlong CPointerToJLong(void* pointer) {
#if defined(_WIN64)
    return reinterpret_cast<jlong>(pointer);
#else
    return 0x00000000FFFFFFFFll & reinterpret_cast<jlong>(pointer);
#endif
}

void ErrorCodeToException(JNIEnv *env, long error)
{
    JniEnv jenv(env);
    jclass clazz;
    switch(error) {
    case ERROR_SUCCESS:
        return;
    case ERROR_FILE_NOT_FOUND:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQFileNotFoundException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_ACCESS_DENIED:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQPermissionException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_INVALID_HANDLE:
        clazz = jenv.FindClass("java/lang/NullPointerException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_NOT_ENOUGH_MEMORY:
        clazz = jenv.FindClass("java/lang/OutOfMemoryError");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_BAD_FORMAT:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQFormatException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_NO_MORE_FILES:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQNoMoreFilesException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_HANDLE_EOF:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQUnexpectedEOFException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_NOT_SUPPORTED:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQUnsupportedException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_INVALID_PARAMETER:
        clazz = jenv.FindClass("java/lang/IllegalArgumentException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_DISK_FULL:
        clazz = jenv.FindClass("java/lang/OutOfMemoryError");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_ALREADY_EXISTS:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQAlreadyExistsException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_CAN_NOT_COMPLETE:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQUnknownException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_FILE_CORRUPT:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQFormatException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_INSUFFICIENT_BUFFER:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQInsufficientBufferException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_AVI_FILE:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQIsAVIException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_UNKNOWN_FILE_KEY:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQUnknownFileKeyException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_CHECKSUM_ERROR:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQChecksumException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_INTERNAL_FILE:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQInternalFileException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_BASE_FILE_MISSING:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQBaseFileMissingException");
        jenv.ThrowNew(clazz, "");
        break;
    case ERROR_MARKED_FOR_DELETE:
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQAlreadyDeletedException");
        jenv.ThrowNew(clazz, "");
        break;

    default: {
        char errNo[32];
        sprintf_s(errNo, "Error Number: 0x%X", error);
        clazz = jenv.FindClass("de/deaod/jstormlib/exceptions/MPQUnknownException");
        jenv.ThrowNew(clazz, errNo);
        break;
    }
    }
}