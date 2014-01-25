#include "JniEnv.h"

JNIH_THREAD_LOCAL JNIEnv* JniEnv::env = NULL;

void JniEnv::checkJNIException(const char* message) {
    if (env->ExceptionOccurred()) {
        throw new JNIException();
    }
}

JNIH_EXPORT JniEnv::JniEnv() {
}

JNIH_EXPORT JniEnv::JniEnv(JNIEnv *env) {
    if (JniEnv::env == NULL) {
        JniEnv::env = env;
    }
}

JNIH_EXPORT JniEnv::~JniEnv() {
}

JNIH_EXPORT jint JniEnv::GetVersion() {
    jint result = env->GetVersion();
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jclass JniEnv::DefineClass(const char *name, jobject loader, const jbyte *buf, jsize len) {
    jclass result = env->DefineClass(name, loader, buf, len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jclass JniEnv::FindClass(const char *name) {
    jclass result = env->FindClass(name);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jmethodID JniEnv::FromReflectedMethod(jobject method) {
    jmethodID result = env->FromReflectedMethod(method);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfieldID JniEnv::FromReflectedField(jobject field) {
    jfieldID result = env->FromReflectedField(field);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic) {
    jobject result = env->ToReflectedMethod(cls, methodID, isStatic);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jclass JniEnv::GetSuperclass(jclass sub) {
    jclass result = env->GetSuperclass(sub);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::IsAssignableFrom(jclass sub, jclass sup) {
    jboolean result = env->IsAssignableFrom(sub, sup);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic) {
    jobject result = env->ToReflectedField(cls,fieldID,isStatic);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jint JniEnv::Throw(jthrowable obj) {
    jint result = env->Throw(obj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::ThrowNew(jclass clazz, const char *msg) {
    jint result = env->ThrowNew(clazz, msg);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jthrowable JniEnv::ExceptionOccurred() {
    jthrowable result = env->ExceptionOccurred();
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::ExceptionDescribe() {
    env->ExceptionDescribe();
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ExceptionClear() {
    env->ExceptionClear();
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::FatalError(const char *msg) {
    env->FatalError(msg);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jint JniEnv::PushLocalFrame(jint capacity) {
    jint result = env->PushLocalFrame(capacity);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::PopLocalFrame(jobject result) {
    jobject result2 = env->PopLocalFrame(result);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result2;
}

JNIH_EXPORT jobject JniEnv::NewGlobalRef(jobject lobj) {
    jobject result = env->NewGlobalRef(lobj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::DeleteGlobalRef(jobject gref) {
    env->DeleteGlobalRef(gref);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::DeleteLocalRef(jobject obj) {
    env->DeleteLocalRef(obj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jboolean JniEnv::IsSameObject(jobject obj1, jobject obj2) {
    jboolean result = env->IsSameObject(obj1,obj2);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::NewLocalRef(jobject ref) {
    jobject result = env->NewLocalRef(ref);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::EnsureLocalCapacity(jint capacity) {
    jint result = env->EnsureLocalCapacity(capacity);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::AllocObject(jclass clazz) {
    jobject result = env->AllocObject(clazz);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::NewObject(jclass clazz, jmethodID methodID, ...) {
    va_list args;
    jobject result;
    va_start(args, methodID);
    result = env->NewObjectV(clazz,methodID,args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::NewObjectV(jclass clazz, jmethodID methodID, va_list args) {
    jobject result = env->NewObjectV(clazz,methodID,args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::NewObjectA(jclass clazz, jmethodID methodID, const jvalue *args) {
    jobject result = env->NewObjectA(clazz,methodID,args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jclass JniEnv::GetObjectClass(jobject obj) {
    jclass result = env->GetObjectClass(obj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::IsInstanceOf(jobject obj, jclass clazz) {
    jboolean result = env->IsInstanceOf(obj,clazz);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jmethodID JniEnv::GetMethodID(jclass cls, const char *name, const char *signature) {
    jmethodID result = env->GetMethodID(cls, name, signature);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::CallObjectMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jobject result;
    va_start(args, methodID);
    result = env->CallObjectMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::CallObjectMethodV(jobject obj, jmethodID methodID, va_list args) {
    jobject result = env->CallObjectMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::CallObjectMethodA(jobject obj, jmethodID methodID, const jvalue * args) {
    jobject result = env->CallObjectMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jboolean JniEnv::CallBooleanMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jboolean result;
    va_start(args, methodID);
    result = env->CallBooleanMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::CallBooleanMethodV(jobject obj, jmethodID methodID, va_list args) {
    jboolean result = env->CallBooleanMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::CallBooleanMethodA(jobject obj, jmethodID methodID, const jvalue * args) {
    jboolean result = env->CallBooleanMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jbyte JniEnv::CallByteMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jbyte result;
    va_start(args, methodID);
    result = env->CallByteMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::CallByteMethodV(jobject obj, jmethodID methodID, va_list args) {
    jbyte result = env->CallByteMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::CallByteMethodA(jobject obj, jmethodID methodID, const jvalue *args) {
    jbyte result = env->CallByteMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jchar JniEnv::CallCharMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jchar result;
    va_start(args, methodID);
    result = env->CallCharMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::CallCharMethodV(jobject obj, jmethodID methodID, va_list args) {
    jchar result = env->CallCharMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::CallCharMethodA(jobject obj, jmethodID methodID, const jvalue *args) {
    jchar result = env->CallCharMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jshort JniEnv::CallShortMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jshort result;
    va_start(args, methodID);
    result = env->CallShortMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::CallShortMethodV(jobject obj, jmethodID methodID, va_list args) {
    jshort result = env->CallShortMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::CallShortMethodA(jobject obj, jmethodID methodID, const jvalue *args) {
    jshort result = env->CallShortMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jint JniEnv::CallIntMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jint result;
    va_start(args, methodID);
    result = env->CallIntMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::CallIntMethodV(jobject obj, jmethodID methodID, va_list args) {
    jint result = env->CallIntMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::CallIntMethodA(jobject obj, jmethodID methodID, const jvalue *args) {
    jint result = env->CallIntMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jlong JniEnv::CallLongMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jlong result;
    va_start(args, methodID);
    result = env->CallLongMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::CallLongMethodV(jobject obj, jmethodID methodID, va_list args) {
    jlong result = env->CallLongMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::CallLongMethodA(jobject obj, jmethodID methodID, const jvalue *args) {
    jlong result = env->CallLongMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jfloat JniEnv::CallFloatMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jfloat result;
    va_start(args, methodID);
    result = env->CallFloatMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::CallFloatMethodV(jobject obj, jmethodID methodID, va_list args) {
    jfloat result = env->CallFloatMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::CallFloatMethodA(jobject obj, jmethodID methodID, const jvalue *args) {
    jfloat result = env->CallFloatMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jdouble JniEnv::CallDoubleMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    jdouble result;
    va_start(args, methodID);
    result = env->CallDoubleMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::CallDoubleMethodV(jobject obj, jmethodID methodID, va_list args) {
    jdouble result = env->CallDoubleMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::CallDoubleMethodA(jobject obj, jmethodID methodID, const jvalue *args) {
    jdouble result = env->CallDoubleMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT void JniEnv::CallVoidMethod(jobject obj, jmethodID methodID, ...) {
    va_list args;
    va_start(args, methodID);
    env->CallVoidMethodV(obj, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::CallVoidMethodV(jobject obj, jmethodID methodID, va_list args) {
    env->CallVoidMethodV(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::CallVoidMethodA(jobject obj, jmethodID methodID, const jvalue * args) {
    env->CallVoidMethodA(obj, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jobject JniEnv::CallNonvirtualObjectMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jobject result;
    va_start(args, methodID);
    result = env->CallNonvirtualObjectMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::CallNonvirtualObjectMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jobject result = env->CallNonvirtualObjectMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::CallNonvirtualObjectMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue * args) {
    jobject result = env->CallNonvirtualObjectMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jboolean JniEnv::CallNonvirtualBooleanMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jboolean result;
    va_start(args, methodID);
    result = env->CallNonvirtualBooleanMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::CallNonvirtualBooleanMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jboolean result = env->CallNonvirtualBooleanMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::CallNonvirtualBooleanMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue * args) {
    jboolean result = env->CallNonvirtualBooleanMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jbyte JniEnv::CallNonvirtualByteMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jbyte result;
    va_start(args, methodID);
    result = env->CallNonvirtualByteMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::CallNonvirtualByteMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jbyte result = env->CallNonvirtualByteMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::CallNonvirtualByteMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue *args) {
    jbyte result = env->CallNonvirtualByteMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jchar JniEnv::CallNonvirtualCharMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jchar result;
    va_start(args, methodID);
    result = env->CallNonvirtualCharMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::CallNonvirtualCharMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jchar result = env->CallNonvirtualCharMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::CallNonvirtualCharMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue *args) {
    jchar result = env->CallNonvirtualCharMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jshort JniEnv::CallNonvirtualShortMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jshort result;
    va_start(args, methodID);
    result = env->CallNonvirtualShortMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::CallNonvirtualShortMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jshort result = env->CallNonvirtualShortMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::CallNonvirtualShortMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue *args) {
    jshort result = env->CallNonvirtualShortMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jint JniEnv::CallNonvirtualIntMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jint result;
    va_start(args, methodID);
    result = env->CallNonvirtualIntMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::CallNonvirtualIntMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jint result = env->CallNonvirtualIntMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::CallNonvirtualIntMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue *args) {
    jint result = env->CallNonvirtualIntMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jlong JniEnv::CallNonvirtualLongMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jlong result;
    va_start(args, methodID);
    result = env->CallNonvirtualLongMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::CallNonvirtualLongMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jlong result = env->CallNonvirtualLongMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::CallNonvirtualLongMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue *args) {
    jlong result = env->CallNonvirtualLongMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jfloat JniEnv::CallNonvirtualFloatMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jfloat result;
    va_start(args, methodID);
    result = env->CallNonvirtualFloatMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::CallNonvirtualFloatMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jfloat result = env->CallNonvirtualFloatMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::CallNonvirtualFloatMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue *args) {
    jfloat result = env->CallNonvirtualFloatMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jdouble JniEnv::CallNonvirtualDoubleMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    jdouble result;
    va_start(args, methodID);
    result = env->CallNonvirtualDoubleMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::CallNonvirtualDoubleMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    jdouble result = env->CallNonvirtualDoubleMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::CallNonvirtualDoubleMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue *args) {
    jdouble result = env->CallNonvirtualDoubleMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT void JniEnv::CallNonvirtualVoidMethod(jobject obj, jclass cls, jmethodID methodID, ...) {
    va_list args;
    va_start(args, methodID);
    env->CallNonvirtualVoidMethodV(obj, cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::CallNonvirtualVoidMethodV(jobject obj, jclass cls, jmethodID methodID, va_list args) {
    env->CallNonvirtualVoidMethodV(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::CallNonvirtualVoidMethodA(jobject obj, jclass cls, jmethodID methodID, const jvalue * args) {
    env->CallNonvirtualVoidMethodA(obj, cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jfieldID JniEnv::GetFieldID(jclass clazz, const char *name, const char *sig) {
    jfieldID result = env->GetFieldID(clazz,name,sig);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::GetObjectField(jobject obj, jfieldID fieldID) {
    jobject result = env->GetObjectField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::GetBooleanField(jobject obj, jfieldID fieldID) {
    jboolean result = env->GetBooleanField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::GetByteField(jobject obj, jfieldID fieldID) {
    jbyte result = env->GetByteField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::GetCharField(jobject obj, jfieldID fieldID) {
    jchar result = env->GetCharField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::GetShortField(jobject obj, jfieldID fieldID) {
    jshort result = env->GetShortField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::GetIntField(jobject obj, jfieldID fieldID) {
    jint result = env->GetIntField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::GetLongField(jobject obj, jfieldID fieldID) {
    jlong result = env->GetLongField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::GetFloatField(jobject obj, jfieldID fieldID) {
    jfloat result = env->GetFloatField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::GetDoubleField(jobject obj, jfieldID fieldID) {
    jdouble result = env->GetDoubleField(obj,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT void JniEnv::SetObjectField(jobject obj, jfieldID fieldID, jobject val) {
    env->SetObjectField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetBooleanField(jobject obj, jfieldID fieldID, jboolean val) {
    env->SetBooleanField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetByteField(jobject obj, jfieldID fieldID, jbyte val) {
    env->SetByteField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetCharField(jobject obj, jfieldID fieldID, jchar val) {
    env->SetCharField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetShortField(jobject obj, jfieldID fieldID, jshort val) {
    env->SetShortField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetIntField(jobject obj, jfieldID fieldID, jint val) {
    env->SetIntField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetLongField(jobject obj, jfieldID fieldID, jlong val) {
    env->SetLongField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetFloatField(jobject obj, jfieldID fieldID, jfloat val) {
    env->SetFloatField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetDoubleField(jobject obj, jfieldID fieldID, jdouble val) {
    env->SetDoubleField(obj,fieldID,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT void JniEnv::SetField(jobject obj, const char* fieldName, const char* fieldSignature, void* newData) {
    jclass cls = this->GetObjectClass(obj);
    jfieldID fid = this->GetFieldID(cls, fieldName, fieldSignature);

    // inspect the first character of the signature
    switch(*fieldSignature) {
    case JNIC_ARRAY:
    case JNIC_CLASS:
        this->SetObjectField(obj, fid, *(reinterpret_cast<jobject*>(newData)));
        break;
    case JNIC_BYTE:
        this->SetByteField(obj, fid, *(reinterpret_cast<jbyte*>(newData)));
        break;
    case JNIC_CHAR:
        this->SetCharField(obj, fid, *(reinterpret_cast<jchar*>(newData)));
        break;
    case JNIC_SHORT:
        this->SetShortField(obj, fid, *(reinterpret_cast<jshort*>(newData)));
        break;
    case JNIC_INT:
        this->SetIntField(obj, fid, *(reinterpret_cast<jint*>(newData)));
        break;
    case JNIC_LONG:
        this->SetLongField(obj, fid, *(reinterpret_cast<jlong*>(newData)));
        break;
    case JNIC_FLOAT:
        this->SetFloatField(obj, fid, *(reinterpret_cast<jfloat*>(newData)));
        break;
    case JNIC_DOUBLE:
        this->SetDoubleField(obj, fid, *(reinterpret_cast<jdouble*>(newData)));
        break;
    case JNIC_BOOLEAN:
        this->SetBooleanField(obj, fid, *(reinterpret_cast<jboolean*>(newData)));
        break;
    }
}

JNIH_EXPORT jmethodID JniEnv::GetStaticMethodID(jclass cls, const char* name, const char* signature) {
    jmethodID result = env->GetStaticMethodID(cls, name, signature);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::CallStaticObjectMethod(jclass cls, jmethodID methodID, ...){
    va_list args;
    jobject result;
    va_start(args, methodID);
    result = env->CallStaticObjectMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::CallStaticObjectMethodV(jclass cls, jmethodID methodID, va_list args) {
    jobject result = env->CallStaticObjectMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::CallStaticObjectMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jobject result = env->CallStaticObjectMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jboolean JniEnv::CallStaticBooleanMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jboolean result;
    va_start(args, methodID);
    result = env->CallStaticBooleanMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::CallStaticBooleanMethodV(jclass cls, jmethodID methodID, va_list args) {
    jboolean result = env->CallStaticBooleanMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::CallStaticBooleanMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jboolean result = env->CallStaticBooleanMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jbyte JniEnv::CallStaticByteMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jbyte result;
    va_start(args, methodID);
    result = env->CallStaticByteMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::CallStaticByteMethodV(jclass cls, jmethodID methodID, va_list args) {
    jbyte result = env->CallStaticByteMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::CallStaticByteMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jbyte result = env->CallStaticByteMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jchar JniEnv::CallStaticCharMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jchar result;
    va_start(args, methodID);
    result = env->CallStaticCharMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::CallStaticCharMethodV(jclass cls, jmethodID methodID, va_list args) {
    jchar result = env->CallStaticCharMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::CallStaticCharMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jchar result = env->CallStaticCharMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jshort JniEnv::CallStaticShortMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jshort result;
    va_start(args, methodID);
    result = env->CallStaticShortMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::CallStaticShortMethodV(jclass cls, jmethodID methodID, va_list args) {
    jshort result = env->CallStaticShortMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::CallStaticShortMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jshort result = env->CallStaticShortMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jint JniEnv::CallStaticIntMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jint result;
    va_start(args, methodID);
    result = env->CallStaticIntMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::CallStaticIntMethodV(jclass cls, jmethodID methodID, va_list args) {
    jint result = env->CallStaticIntMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::CallStaticIntMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jint result = env->CallStaticIntMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jlong JniEnv::CallStaticLongMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jlong result;
    va_start(args, methodID);
    result = env->CallStaticLongMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::CallStaticLongMethodV(jclass cls, jmethodID methodID, va_list args) {
    jlong result = env->CallStaticLongMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::CallStaticLongMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jlong result = env->CallStaticLongMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jfloat JniEnv::CallStaticFloatMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jfloat result;
    va_start(args, methodID);
    result = env->CallStaticFloatMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::CallStaticFloatMethodV(jclass cls, jmethodID methodID, va_list args) {
    jfloat result = env->CallStaticFloatMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::CallStaticFloatMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jfloat result = env->CallStaticFloatMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT jdouble JniEnv::CallStaticDoubleMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    jdouble result;
    va_start(args, methodID);
    result = env->CallStaticDoubleMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::CallStaticDoubleMethodV(jclass cls, jmethodID methodID, va_list args) {
    jdouble result = env->CallStaticDoubleMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::CallStaticDoubleMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    jdouble result = env->CallStaticDoubleMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}


JNIH_EXPORT void JniEnv::CallStaticVoidMethod(jclass cls, jmethodID methodID, ...) {
    va_list args;
    va_start(args, methodID);
    env->CallStaticVoidMethodV(cls, methodID, args);
    va_end(args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT void JniEnv::CallStaticVoidMethodV(jclass cls, jmethodID methodID, va_list args) {
    env->CallStaticVoidMethodV(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT void JniEnv::CallStaticVoidMethodA(jclass cls, jmethodID methodID, const jvalue* args) {
    env->CallStaticVoidMethodA(cls, methodID, args);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}


JNIH_EXPORT jfieldID JniEnv::GetStaticFieldID(jclass clazz, const char *name, const char *sig) {
    jfieldID result = env->GetStaticFieldID(clazz,name,sig);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::GetStaticObjectField(jclass clazz, jfieldID fieldID) {
    jobject result = env->GetStaticObjectField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jboolean JniEnv::GetStaticBooleanField(jclass clazz, jfieldID fieldID) {
    jboolean result = env->GetStaticBooleanField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte JniEnv::GetStaticByteField(jclass clazz, jfieldID fieldID) {
    jbyte result = env->GetStaticByteField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar JniEnv::GetStaticCharField(jclass clazz, jfieldID fieldID) {
    jchar result = env->GetStaticCharField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort JniEnv::GetStaticShortField(jclass clazz, jfieldID fieldID) {
    jshort result = env->GetStaticShortField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::GetStaticIntField(jclass clazz, jfieldID fieldID) {
    jint result = env->GetStaticIntField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::GetStaticLongField(jclass clazz, jfieldID fieldID) {
    jlong result = env->GetStaticLongField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat JniEnv::GetStaticFloatField(jclass clazz, jfieldID fieldID) {
    jfloat result = env->GetStaticFloatField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble JniEnv::GetStaticDoubleField(jclass clazz, jfieldID fieldID) {
    jdouble result = env->GetStaticDoubleField(clazz,fieldID);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT void JniEnv::SetStaticObjectField(jclass clazz, jfieldID fieldID, jobject value) {
    env->SetStaticObjectField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticBooleanField(jclass clazz, jfieldID fieldID, jboolean value) {
    env->SetStaticBooleanField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticByteField(jclass clazz, jfieldID fieldID, jbyte value) {
    env->SetStaticByteField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticCharField(jclass clazz, jfieldID fieldID, jchar value) {
    env->SetStaticCharField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticShortField(jclass clazz, jfieldID fieldID, jshort value) {
    env->SetStaticShortField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticIntField(jclass clazz, jfieldID fieldID, jint value) {
    env->SetStaticIntField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticLongField(jclass clazz, jfieldID fieldID, jlong value) {
    env->SetStaticLongField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticFloatField(jclass clazz, jfieldID fieldID, jfloat value) {
    env->SetStaticFloatField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetStaticDoubleField(jclass clazz, jfieldID fieldID, jdouble value) {
    env->SetStaticDoubleField(clazz,fieldID,value);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT void JniEnv::SetStaticField(jclass cls, const char* fieldName, const char* fieldSignature, void* newData) {
    jfieldID fid = this->GetFieldID(cls, fieldName, fieldSignature);

    // inspect the first character of the signature
    switch(*fieldSignature) {
    case JNIC_ARRAY:
    case JNIC_CLASS:
        this->SetStaticObjectField(cls, fid, *(reinterpret_cast<jobject*>(newData)));
        break;
    case JNIC_BYTE:
        this->SetStaticByteField(cls, fid, *(reinterpret_cast<jbyte*>(newData)));
        break;
    case JNIC_CHAR:
        this->SetStaticCharField(cls, fid, *(reinterpret_cast<jchar*>(newData)));
        break;
    case JNIC_SHORT:
        this->SetStaticShortField(cls, fid, *(reinterpret_cast<jshort*>(newData)));
        break;
    case JNIC_INT:
        this->SetStaticIntField(cls, fid, *(reinterpret_cast<jint*>(newData)));
        break;
    case JNIC_LONG:
        this->SetStaticLongField(cls, fid, *(reinterpret_cast<jlong*>(newData)));
        break;
    case JNIC_FLOAT:
        this->SetStaticFloatField(cls, fid, *(reinterpret_cast<jfloat*>(newData)));
        break;
    case JNIC_DOUBLE:
        this->SetStaticDoubleField(cls, fid, *(reinterpret_cast<jdouble*>(newData)));
        break;
    case JNIC_BOOLEAN:
        this->SetStaticBooleanField(cls, fid, *(reinterpret_cast<jboolean*>(newData)));
        break;
    }
}

JNIH_EXPORT jstring JniEnv::NewString(const jchar *unicode, jsize len) {
    jstring result = env->NewString(unicode,len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jsize JniEnv::GetStringLength(jstring str) {
    jsize result = env->GetStringLength(str);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT const jchar *JniEnv::GetStringChars(jstring str, jboolean *isCopy) {
    const jchar* result = env->GetStringChars(str,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::ReleaseStringChars(jstring str, const jchar *chars) {
    env->ReleaseStringChars(str,chars);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jstring JniEnv::NewStringUTF(const char *utf) {
    jstring result = env->NewStringUTF(utf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jsize JniEnv::GetStringUTFLength(jstring str) {
    jsize result = env->GetStringUTFLength(str);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT const char* JniEnv::GetStringUTFChars(jstring str, jboolean *isCopy) {
    const char* result = env->GetStringUTFChars(str,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::ReleaseStringUTFChars(jstring str, const char* chars) {
    env->ReleaseStringUTFChars(str,chars);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jsize JniEnv::GetArrayLength(jarray array) {
    jsize result = env->GetArrayLength(array);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobjectArray JniEnv::NewObjectArray(jsize len, jclass clazz, jobject init) {
    jobjectArray result = env->NewObjectArray(len,clazz,init);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobject JniEnv::GetObjectArrayElement(jobjectArray array, jsize index) {
    jobject result = env->GetObjectArrayElement(array,index);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::SetObjectArrayElement(jobjectArray array, jsize index, jobject val) {
    env->SetObjectArrayElement(array,index,val);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jbooleanArray JniEnv::NewBooleanArray(jsize len) {
    jbooleanArray result = env->NewBooleanArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyteArray JniEnv::NewByteArray(jsize len) {
    jbyteArray result = env->NewByteArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jcharArray JniEnv::NewCharArray(jsize len) {
    jcharArray result = env->NewCharArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshortArray JniEnv::NewShortArray(jsize len) {
    jshortArray result = env->NewShortArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jintArray JniEnv::NewIntArray(jsize len) {
    jintArray result = env->NewIntArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlongArray JniEnv::NewLongArray(jsize len) {
    jlongArray result = env->NewLongArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloatArray JniEnv::NewFloatArray(jsize len) {
    jfloatArray result = env->NewFloatArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdoubleArray JniEnv::NewDoubleArray(jsize len) {
    jdoubleArray result = env->NewDoubleArray(len);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jboolean * JniEnv::GetBooleanArrayElements(jbooleanArray array, jboolean *isCopy) {
    jboolean* result = env->GetBooleanArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jbyte * JniEnv::GetByteArrayElements(jbyteArray array, jboolean *isCopy) {
    jbyte* result = env->GetByteArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jchar * JniEnv::GetCharArrayElements(jcharArray array, jboolean *isCopy) {
    jchar* result = env->GetCharArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jshort * JniEnv::GetShortArrayElements(jshortArray array, jboolean *isCopy) {
    jshort* result = env->GetShortArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint * JniEnv::GetIntArrayElements(jintArray array, jboolean *isCopy) {
    jint* result = env->GetIntArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong * JniEnv::GetLongArrayElements(jlongArray array, jboolean *isCopy) {
    jlong* result = env->GetLongArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jfloat * JniEnv::GetFloatArrayElements(jfloatArray array, jboolean *isCopy) {
    jfloat* result = env->GetFloatArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jdouble * JniEnv::GetDoubleArrayElements(jdoubleArray array, jboolean *isCopy) {
    jdouble* result = env->GetDoubleArrayElements(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT void JniEnv::ReleaseBooleanArrayElements(jbooleanArray array, jboolean *elems, jint mode) {
    env->ReleaseBooleanArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ReleaseByteArrayElements(jbyteArray array, jbyte *elems, jint mode) {
    env->ReleaseByteArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ReleaseCharArrayElements(jcharArray array, jchar *elems, jint mode) {
    env->ReleaseCharArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ReleaseShortArrayElements(jshortArray array, jshort *elems, jint mode) {
    env->ReleaseShortArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ReleaseIntArrayElements(jintArray array, jint *elems, jint mode) {
    env->ReleaseIntArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ReleaseLongArrayElements(jlongArray array, jlong *elems, jint mode) {
    env->ReleaseLongArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ReleaseFloatArrayElements(jfloatArray array, jfloat *elems, jint mode) {
    env->ReleaseFloatArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::ReleaseDoubleArrayElements(jdoubleArray array, jdouble *elems, jint mode) {
    env->ReleaseDoubleArrayElements(array,elems,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT void JniEnv::GetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, jboolean *buf) {
    env->GetBooleanArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetByteArrayRegion(jbyteArray array, jsize start, jsize len, jbyte *buf) {
    env->GetByteArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetCharArrayRegion(jcharArray array, jsize start, jsize len, jchar *buf) {
    env->GetCharArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetShortArrayRegion(jshortArray array, jsize start, jsize len, jshort *buf) {
    env->GetShortArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetIntArrayRegion(jintArray array, jsize start, jsize len, jint *buf) {
    env->GetIntArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetLongArrayRegion(jlongArray array, jsize start, jsize len, jlong *buf) {
    env->GetLongArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetFloatArrayRegion(jfloatArray array, jsize start, jsize len, jfloat *buf) {
    env->GetFloatArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, jdouble *buf) {
    env->GetDoubleArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT void JniEnv::SetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, const jboolean *buf) {
    env->SetBooleanArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetByteArrayRegion(jbyteArray array, jsize start, jsize len, const jbyte *buf) {
    env->SetByteArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetCharArrayRegion(jcharArray array, jsize start, jsize len, const jchar *buf) {
    env->SetCharArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetShortArrayRegion(jshortArray array, jsize start, jsize len, const jshort *buf) {
    env->SetShortArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetIntArrayRegion(jintArray array, jsize start, jsize len, const jint *buf) {
    env->SetIntArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetLongArrayRegion(jlongArray array, jsize start, jsize len, const jlong *buf) {
    env->SetLongArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetFloatArrayRegion(jfloatArray array, jsize start, jsize len, const jfloat *buf) {
    env->SetFloatArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::SetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, const jdouble *buf) {
    env->SetDoubleArrayRegion(array,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jint JniEnv::RegisterNatives(jclass clazz, const JNINativeMethod *methods, jint nMethods) {
    jint result = env->RegisterNatives(clazz,methods,nMethods);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::UnregisterNatives(jclass clazz) {
    jint result = env->UnregisterNatives(clazz);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jint JniEnv::MonitorEnter(jobject obj) {
    jint result = env->MonitorEnter(obj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jint JniEnv::MonitorExit(jobject obj) {
    jint result = env->MonitorExit(obj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jint JniEnv::GetJavaVM(JavaVM **vm) {
    jint result = env->GetJavaVM(vm);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT void JniEnv::GetStringRegion(jstring str, jsize start, jsize len, jchar *buf) {
    env->GetStringRegion(str,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}
JNIH_EXPORT void JniEnv::GetStringUTFRegion(jstring str, jsize start, jsize len, char *buf) {
    env->GetStringUTFRegion(str,start,len,buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT void * JniEnv::GetPrimitiveArrayCritical(jarray array, jboolean *isCopy) {
    void* result = env->GetPrimitiveArrayCritical(array,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::ReleasePrimitiveArrayCritical(jarray array, void *carray, jint mode) {
    env->ReleasePrimitiveArrayCritical(array,carray,mode);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT const jchar * JniEnv::GetStringCritical(jstring string, jboolean *isCopy) {
    const jchar* result = env->GetStringCritical(string,isCopy);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::ReleaseStringCritical(jstring string, const jchar *cstring) {
    env->ReleaseStringCritical(string,cstring);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jweak JniEnv::NewWeakGlobalRef(jobject obj) {
    jweak result = env->NewWeakGlobalRef(obj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void JniEnv::DeleteWeakGlobalRef(jweak ref) {
    env->DeleteWeakGlobalRef(ref);
    checkJNIException(JNIH_CURRENT_FUNCTION);
}

JNIH_EXPORT jboolean JniEnv::ExceptionCheck() {
    jboolean result = env->ExceptionCheck();
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}

JNIH_EXPORT jobject JniEnv::NewDirectByteBuffer(void* address, jlong capacity) {
    jobject result = env->NewDirectByteBuffer(address, capacity);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT void* JniEnv::GetDirectBufferAddress(jobject buf) {
    void* result = env->GetDirectBufferAddress(buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jlong JniEnv::GetDirectBufferCapacity(jobject buf) {
    jlong result = env->GetDirectBufferCapacity(buf);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}
JNIH_EXPORT jobjectRefType JniEnv::GetObjectRefType(jobject obj) {
    jobjectRefType result = env->GetObjectRefType(obj);
    checkJNIException(JNIH_CURRENT_FUNCTION);
    return result;
}