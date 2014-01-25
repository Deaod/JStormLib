#ifndef _JNIENV_H_
#define _JNIENV_H_

#include "JNIHelper.h"

class JniEnv {
private:
    JNIH_THREAD_LOCAL static JNIEnv *env;

    void checkJNIException(const char*);

public:

    JNIH_EXPORT JniEnv();

    JNIH_EXPORT JniEnv(JNIEnv *env);

    JNIH_EXPORT ~JniEnv();

    //

    JNIH_EXPORT jint GetVersion();
    JNIH_EXPORT jclass DefineClass(const char*, jobject, const jbyte*, jsize);
    JNIH_EXPORT jclass FindClass(const char*);
    JNIH_EXPORT jmethodID FromReflectedMethod(jobject);
    JNIH_EXPORT jfieldID FromReflectedField(jobject);

    JNIH_EXPORT jobject ToReflectedMethod(jclass, jmethodID, jboolean);

    JNIH_EXPORT jclass GetSuperclass(jclass);
    JNIH_EXPORT jboolean IsAssignableFrom(jclass, jclass);

    JNIH_EXPORT jobject ToReflectedField(jclass, jfieldID, jboolean);

    JNIH_EXPORT jint Throw(jthrowable);
    JNIH_EXPORT jint ThrowNew(jclass, const char*);
    JNIH_EXPORT jthrowable ExceptionOccurred();
    JNIH_EXPORT void ExceptionDescribe();
    JNIH_EXPORT void ExceptionClear();
    JNIH_EXPORT void FatalError(const char*);

    JNIH_EXPORT jint PushLocalFrame(jint);
    JNIH_EXPORT jobject PopLocalFrame(jobject);

    JNIH_EXPORT jobject NewGlobalRef(jobject);
    JNIH_EXPORT void DeleteGlobalRef(jobject);
    JNIH_EXPORT void DeleteLocalRef(jobject);

    JNIH_EXPORT jboolean IsSameObject(jobject, jobject);

    JNIH_EXPORT jobject NewLocalRef(jobject);
    JNIH_EXPORT jint EnsureLocalCapacity(jint);

    JNIH_EXPORT jobject AllocObject(jclass);
    JNIH_EXPORT jobject NewObject(jclass, jmethodID, ...);
    JNIH_EXPORT jobject NewObjectV(jclass, jmethodID, va_list);
    JNIH_EXPORT jobject NewObjectA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jclass GetObjectClass(jobject);
    JNIH_EXPORT jboolean IsInstanceOf(jobject, jclass);

    JNIH_EXPORT jmethodID GetMethodID(jclass, const char *name, const char *signature);

    JNIH_EXPORT jobject CallObjectMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jobject CallObjectMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jobject CallObjectMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jboolean CallBooleanMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jboolean CallBooleanMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jboolean CallBooleanMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jbyte CallByteMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jbyte CallByteMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jbyte CallByteMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jchar CallCharMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jchar CallCharMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jchar CallCharMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jshort CallShortMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jshort CallShortMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jshort CallShortMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jint CallIntMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jint CallIntMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jint CallIntMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jlong CallLongMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jlong CallLongMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jlong CallLongMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jfloat CallFloatMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jfloat CallFloatMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jfloat CallFloatMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jdouble CallDoubleMethod(jobject, jmethodID, ...);
    JNIH_EXPORT jdouble CallDoubleMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT jdouble CallDoubleMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT void CallVoidMethod(jobject, jmethodID, ...);
    JNIH_EXPORT void CallVoidMethodV(jobject, jmethodID, va_list);
    JNIH_EXPORT void CallVoidMethodA(jobject, jmethodID, const jvalue *);

    JNIH_EXPORT jobject CallNonvirtualObjectMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jobject CallNonvirtualObjectMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jobject CallNonvirtualObjectMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jboolean CallNonvirtualBooleanMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jboolean CallNonvirtualBooleanMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jboolean CallNonvirtualBooleanMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jbyte CallNonvirtualByteMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jbyte CallNonvirtualByteMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jbyte CallNonvirtualByteMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jchar CallNonvirtualCharMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jchar CallNonvirtualCharMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jchar CallNonvirtualCharMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jshort CallNonvirtualShortMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jshort CallNonvirtualShortMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jshort CallNonvirtualShortMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jint CallNonvirtualIntMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jint CallNonvirtualIntMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jint CallNonvirtualIntMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jlong CallNonvirtualLongMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jlong CallNonvirtualLongMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jlong CallNonvirtualLongMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jfloat CallNonvirtualFloatMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jfloat CallNonvirtualFloatMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jfloat CallNonvirtualFloatMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jdouble CallNonvirtualDoubleMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT jdouble CallNonvirtualDoubleMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT jdouble CallNonvirtualDoubleMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT void CallNonvirtualVoidMethod(jobject, jclass, jmethodID, ...);
    JNIH_EXPORT void CallNonvirtualVoidMethodV(jobject, jclass, jmethodID, va_list);
    JNIH_EXPORT void CallNonvirtualVoidMethodA(jobject, jclass, jmethodID, const jvalue *);

    JNIH_EXPORT jfieldID GetFieldID(jclass, const char* name, const char* signature);

    JNIH_EXPORT jobject GetObjectField(jobject, jfieldID);
    JNIH_EXPORT jboolean GetBooleanField(jobject, jfieldID);
    JNIH_EXPORT jbyte GetByteField(jobject, jfieldID);
    JNIH_EXPORT jchar GetCharField(jobject, jfieldID);
    JNIH_EXPORT jshort GetShortField(jobject, jfieldID);
    JNIH_EXPORT jint GetIntField(jobject, jfieldID);
    JNIH_EXPORT jlong GetLongField(jobject, jfieldID);
    JNIH_EXPORT jfloat GetFloatField(jobject, jfieldID);
    JNIH_EXPORT jdouble GetDoubleField(jobject, jfieldID);

    JNIH_EXPORT void SetObjectField(jobject, jfieldID, jobject);
    JNIH_EXPORT void SetBooleanField(jobject, jfieldID, jboolean);
    JNIH_EXPORT void SetByteField(jobject, jfieldID, jbyte);
    JNIH_EXPORT void SetCharField(jobject, jfieldID, jchar);
    JNIH_EXPORT void SetShortField(jobject, jfieldID, jshort);
    JNIH_EXPORT void SetIntField(jobject, jfieldID, jint);
    JNIH_EXPORT void SetLongField(jobject, jfieldID, jlong);
    JNIH_EXPORT void SetFloatField(jobject, jfieldID, jfloat);
    JNIH_EXPORT void SetDoubleField(jobject, jfieldID, jdouble);

    JNIH_EXPORT void SetField(jobject, const char* fieldName, const char* fieldSignature, void* newData);

    JNIH_EXPORT jmethodID GetStaticMethodID(jclass, const char* name, const char* signature);

    JNIH_EXPORT jobject CallStaticObjectMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jobject CallStaticObjectMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jobject CallStaticObjectMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jboolean CallStaticBooleanMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jboolean CallStaticBooleanMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jboolean CallStaticBooleanMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jbyte CallStaticByteMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jbyte CallStaticByteMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jbyte CallStaticByteMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jchar CallStaticCharMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jchar CallStaticCharMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jchar CallStaticCharMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jshort CallStaticShortMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jshort CallStaticShortMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jshort CallStaticShortMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jint CallStaticIntMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jint CallStaticIntMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jint CallStaticIntMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jlong CallStaticLongMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jlong CallStaticLongMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jlong CallStaticLongMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jfloat CallStaticFloatMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jfloat CallStaticFloatMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jfloat CallStaticFloatMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jdouble CallStaticDoubleMethod(jclass, jmethodID, ...);
    JNIH_EXPORT jdouble CallStaticDoubleMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT jdouble CallStaticDoubleMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT void CallStaticVoidMethod(jclass, jmethodID, ...);
    JNIH_EXPORT void CallStaticVoidMethodV(jclass, jmethodID, va_list);
    JNIH_EXPORT void CallStaticVoidMethodA(jclass, jmethodID, const jvalue*);

    JNIH_EXPORT jfieldID GetStaticFieldID(jclass, const char* name, const char* signature);

    JNIH_EXPORT jobject GetStaticObjectField(jclass, jfieldID);
    JNIH_EXPORT jboolean GetStaticBooleanField(jclass, jfieldID);
    JNIH_EXPORT jbyte GetStaticByteField(jclass, jfieldID);
    JNIH_EXPORT jchar GetStaticCharField(jclass, jfieldID);
    JNIH_EXPORT jshort GetStaticShortField(jclass, jfieldID);
    JNIH_EXPORT jint GetStaticIntField(jclass, jfieldID);
    JNIH_EXPORT jlong GetStaticLongField(jclass, jfieldID);
    JNIH_EXPORT jfloat GetStaticFloatField(jclass, jfieldID);
    JNIH_EXPORT jdouble GetStaticDoubleField(jclass, jfieldID);

    JNIH_EXPORT void SetStaticObjectField(jclass, jfieldID, jobject);
    JNIH_EXPORT void SetStaticBooleanField(jclass, jfieldID, jboolean);
    JNIH_EXPORT void SetStaticByteField(jclass, jfieldID, jbyte);
    JNIH_EXPORT void SetStaticCharField(jclass, jfieldID, jchar);
    JNIH_EXPORT void SetStaticShortField(jclass, jfieldID, jshort);
    JNIH_EXPORT void SetStaticIntField(jclass, jfieldID, jint);
    JNIH_EXPORT void SetStaticLongField(jclass, jfieldID, jlong);
    JNIH_EXPORT void SetStaticFloatField(jclass, jfieldID, jfloat);
    JNIH_EXPORT void SetStaticDoubleField(jclass, jfieldID, jdouble);

    JNIH_EXPORT void SetStaticField(jclass, const char* fieldName, const char* fieldSignature, void* newData);

    JNIH_EXPORT jstring NewString(const jchar*, jsize);
    JNIH_EXPORT jsize GetStringLength(jstring);
    JNIH_EXPORT const jchar *GetStringChars(jstring, jboolean*);
    JNIH_EXPORT void ReleaseStringChars(jstring, const jchar*);

    JNIH_EXPORT jstring NewStringUTF(const char*);
    JNIH_EXPORT jsize GetStringUTFLength(jstring);
    JNIH_EXPORT const char* GetStringUTFChars(jstring, jboolean*);
    JNIH_EXPORT void ReleaseStringUTFChars(jstring, const char*);

    JNIH_EXPORT jsize GetArrayLength(jarray);

    JNIH_EXPORT jobjectArray NewObjectArray(jsize, jclass, jobject);
    JNIH_EXPORT jobject GetObjectArrayElement(jobjectArray, jsize);
    JNIH_EXPORT void SetObjectArrayElement(jobjectArray, jsize, jobject);

    JNIH_EXPORT jbooleanArray NewBooleanArray(jsize);
    JNIH_EXPORT jbyteArray NewByteArray(jsize);
    JNIH_EXPORT jcharArray NewCharArray(jsize);
    JNIH_EXPORT jshortArray NewShortArray(jsize);
    JNIH_EXPORT jintArray NewIntArray(jsize);
    JNIH_EXPORT jlongArray NewLongArray(jsize);
    JNIH_EXPORT jfloatArray NewFloatArray(jsize);
    JNIH_EXPORT jdoubleArray NewDoubleArray(jsize);

    JNIH_EXPORT jboolean* GetBooleanArrayElements(jbooleanArray, jboolean*);
    JNIH_EXPORT jbyte* GetByteArrayElements(jbyteArray, jboolean*);
    JNIH_EXPORT jchar* GetCharArrayElements(jcharArray, jboolean*);
    JNIH_EXPORT jshort* GetShortArrayElements(jshortArray, jboolean*);
    JNIH_EXPORT jint* GetIntArrayElements(jintArray, jboolean*);
    JNIH_EXPORT jlong* GetLongArrayElements(jlongArray, jboolean*);
    JNIH_EXPORT jfloat* GetFloatArrayElements(jfloatArray, jboolean*);
    JNIH_EXPORT jdouble* GetDoubleArrayElements(jdoubleArray, jboolean*);

    JNIH_EXPORT void ReleaseBooleanArrayElements(jbooleanArray, jboolean*, jint);
    JNIH_EXPORT void ReleaseByteArrayElements(jbyteArray, jbyte*, jint);
    JNIH_EXPORT void ReleaseCharArrayElements(jcharArray, jchar*, jint);
    JNIH_EXPORT void ReleaseShortArrayElements(jshortArray, jshort*, jint);
    JNIH_EXPORT void ReleaseIntArrayElements(jintArray, jint*, jint);
    JNIH_EXPORT void ReleaseLongArrayElements(jlongArray, jlong*, jint);
    JNIH_EXPORT void ReleaseFloatArrayElements(jfloatArray, jfloat*, jint);
    JNIH_EXPORT void ReleaseDoubleArrayElements(jdoubleArray, jdouble*, jint);

    JNIH_EXPORT void GetBooleanArrayRegion(jbooleanArray, jsize, jsize, jboolean*);
    JNIH_EXPORT void GetByteArrayRegion(jbyteArray, jsize, jsize, jbyte*);
    JNIH_EXPORT void GetCharArrayRegion(jcharArray, jsize, jsize, jchar*);
    JNIH_EXPORT void GetShortArrayRegion(jshortArray, jsize, jsize, jshort*);
    JNIH_EXPORT void GetIntArrayRegion(jintArray, jsize, jsize, jint*);
    JNIH_EXPORT void GetLongArrayRegion(jlongArray, jsize, jsize, jlong*);
    JNIH_EXPORT void GetFloatArrayRegion(jfloatArray, jsize, jsize, jfloat*);
    JNIH_EXPORT void GetDoubleArrayRegion(jdoubleArray, jsize, jsize, jdouble*);

    JNIH_EXPORT void SetBooleanArrayRegion(jbooleanArray, jsize, jsize, const jboolean*);
    JNIH_EXPORT void SetByteArrayRegion(jbyteArray, jsize, jsize, const jbyte*);
    JNIH_EXPORT void SetCharArrayRegion(jcharArray, jsize, jsize, const jchar*);
    JNIH_EXPORT void SetShortArrayRegion(jshortArray, jsize, jsize, const jshort*);
    JNIH_EXPORT void SetIntArrayRegion(jintArray, jsize, jsize, const jint*);
    JNIH_EXPORT void SetLongArrayRegion(jlongArray, jsize, jsize, const jlong*);
    JNIH_EXPORT void SetFloatArrayRegion(jfloatArray, jsize, jsize, const jfloat*);
    JNIH_EXPORT void SetDoubleArrayRegion(jdoubleArray, jsize, jsize, const jdouble*);

    JNIH_EXPORT jint RegisterNatives(jclass, const JNINativeMethod*, jint);
    JNIH_EXPORT jint UnregisterNatives(jclass);

    JNIH_EXPORT jint MonitorEnter(jobject);
    JNIH_EXPORT jint MonitorExit(jobject);

    JNIH_EXPORT jint GetJavaVM(JavaVM**);

    JNIH_EXPORT void GetStringRegion(jstring, jsize, jsize, jchar*);
    JNIH_EXPORT void GetStringUTFRegion(jstring, jsize, jsize, char*);

    JNIH_EXPORT void* GetPrimitiveArrayCritical(jarray, jboolean*);
    JNIH_EXPORT void ReleasePrimitiveArrayCritical(jarray, void*, jint);

    JNIH_EXPORT const jchar* GetStringCritical(jstring, jboolean*);
    JNIH_EXPORT void ReleaseStringCritical(jstring, const jchar*);

    JNIH_EXPORT jweak NewWeakGlobalRef(jobject);
    JNIH_EXPORT void DeleteWeakGlobalRef(jweak);

    JNIH_EXPORT jboolean ExceptionCheck();

    JNIH_EXPORT jobject NewDirectByteBuffer(void*, jlong);
    JNIH_EXPORT void* GetDirectBufferAddress(jobject);
    JNIH_EXPORT jlong GetDirectBufferCapacity(jobject);
    JNIH_EXPORT jobjectRefType GetObjectRefType(jobject);
};

#endif // !_JNIENV_H_