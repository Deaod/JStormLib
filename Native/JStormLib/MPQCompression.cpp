#include "MPQCompression.h"
#include "Common.h"
#include <StormLib.h>
#include <JString.h>
#include <JArray.h>
#include <JniEnv.h>

/*
 * Class:     de_deaod_jstormlib_MPQCompression
 * Method:    implode
 * Signature: ([BII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQCompression_implode
  (JNIEnv *env, jclass /*cls*/, jbyteArray inBuffer, jint inBufferOffset, jint inBufferLength)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JByteArray jInBuffer(env, inBuffer);
    JByteArray tempBuffer(env, inBufferLength);
    jsize outBufferLength = inBufferLength;

    jboolean result = SCompImplode(
        tempBuffer.getData(),
        reinterpret_cast<int*>(&outBufferLength),
        (jInBuffer.getData() + inBufferOffset),
        inBufferLength
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        JByteArray outBuffer(env, outBufferLength);
        memcpy(outBuffer.getData(), tempBuffer.getData(), outBufferLength);

        return outBuffer.getArray();
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQCompression
 * Method:    explode
 * Signature: ([BIII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQCompression_explode
  (JNIEnv *env, jclass /*cls*/, jbyteArray inBuffer, jint inBufferOffset, jint inBufferLength, jint outBufferLength)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JByteArray jInBuffer(env, inBuffer);
    JByteArray tempBuffer(env, outBufferLength);
    jint decompressedSize = outBufferLength;

    jboolean result = SCompExplode(
        tempBuffer.getData(),
        reinterpret_cast<int*>(&decompressedSize),
        (jInBuffer.getData() + inBufferOffset),
        inBufferLength
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        JByteArray outBuffer(env, decompressedSize);
        memcpy(outBuffer.getData(), tempBuffer.getData(), decompressedSize);

        return outBuffer.getArray();
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQCompression
 * Method:    compress
 * Signature: ([BIIII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQCompression_compress
  (JNIEnv *env, jclass /*cls*/, jbyteArray inBuffer, jint inBufferOffset, jint inBufferLength, jint compressionMask, jint compressionLevel)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JByteArray jInBuffer(env, inBuffer);
    JByteArray tempBuffer(env, inBufferLength);
    jsize outBufferLength = inBufferLength;


    jboolean result = SCompCompress(
        tempBuffer.getData(),
        reinterpret_cast<int*>(&outBufferLength),
        (jInBuffer.getData() + inBufferOffset),
        inBufferLength,
        compressionMask,
        0,
        compressionLevel
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        JByteArray outBuffer(env, outBufferLength);
        memcpy(outBuffer.getData(), tempBuffer.getData(), outBufferLength);

        return outBuffer.getArray();
    }
} JNIH_EXCEPTION_TRAP_END

/*
 * Class:     de_deaod_jstormlib_MPQCompression
 * Method:    decompress
 * Signature: ([BIII)[B
 */
JNIEXPORT jbyteArray JNICALL Java_de_deaod_jstormlib_MPQCompression_decompress
  (JNIEnv *env, jclass /*cls*/, jbyteArray inBuffer, jint inBufferOffset, jint inBufferLength, jint outBufferLength)
JNIH_EXCEPTION_TRAP_BEGIN() {
    JByteArray jInBuffer(env, inBuffer);
    JByteArray tempBuffer(env, outBufferLength);
    jint decompressedSize = outBufferLength;

    jboolean result = SCompDecompress(
        tempBuffer.getData(),
        reinterpret_cast<int*>(&decompressedSize),
        jInBuffer.getData(),
        inBufferLength
    );

    if (!result) {
        ErrorCodeToException(env, GetLastError());
    } else {
        JByteArray outBuffer(env, decompressedSize);
        memcpy(outBuffer.getData(), tempBuffer.getData(), decompressedSize);

        return outBuffer.getArray();
    }
} JNIH_EXCEPTION_TRAP_END
