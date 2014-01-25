#ifndef _JARRAY_H_
#define _JARRAY_H_

#include "JniEnv.h"
#include "JniHelper.h"

template<typename arrayType> class JArrayType;

template<> class JArrayType<jbyteArray> {
    typedef jbyteArray _JArrayType;
public:
    typedef jbyte _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetByteArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetByteArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetByteArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseByteArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewByteArray(length);
    }
};

template<> class JArrayType<jshortArray> {
    typedef jshortArray _JArrayType;
public:
    typedef jshort _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetShortArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetShortArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetShortArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseShortArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewShortArray(length);
    }
};

template<> class JArrayType<jintArray> {
    typedef jintArray _JArrayType;
public:
    typedef jint _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetIntArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetIntArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetIntArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseIntArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewIntArray(length);
    }
};

template<> class JArrayType<jlongArray> {
    typedef jlongArray _JArrayType;
public:
    typedef jlong _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetLongArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetLongArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetLongArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseLongArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewLongArray(length);
    }
};

template<> class JArrayType<jfloatArray> {
    typedef jfloatArray _JArrayType;
public:
    typedef jfloat _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetFloatArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetFloatArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetFloatArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseFloatArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewFloatArray(length);
    }
};

template<> class JArrayType<jdoubleArray> {
    typedef jdoubleArray _JArrayType;
public:
    typedef jdouble _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetDoubleArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetDoubleArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetDoubleArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseDoubleArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewDoubleArray(length);
    }
};

template<> class JArrayType<jcharArray> {
    typedef jcharArray _JArrayType;
public:
    typedef jchar _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetCharArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetCharArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetCharArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseCharArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewCharArray(length);
    }
};

template<> class JArrayType<jbooleanArray> {
    typedef jbooleanArray _JArrayType;
public:
    typedef jboolean _JType;

    static void getRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, _JType* dest) {
        jEnv->GetBooleanArrayRegion(jArray, offset, length, dest);
    }

    static _JType* get(JniEnv* jEnv, _JArrayType jArray) {
        return jEnv->GetBooleanArrayElements(jArray, NULL);
    }

    static void setRegion(JniEnv* jEnv, _JArrayType jArray, jsize offset, jsize length, const _JType* source) {
        jEnv->SetBooleanArrayRegion(jArray, offset, length, source);
    }

    static void set(JniEnv* jEnv, _JArrayType jArray, _JType* data, jint mode) {
        jEnv->ReleaseBooleanArrayElements(jArray, data, mode);
    }

    static _JArrayType create(JniEnv *jEnv, jsize length) {
        return jEnv->NewBooleanArray(length);
    }
};

static enum JArrayAction {
    RELEASE = 0,
    COMMIT = JNI_COMMIT,
    ABORT = JNI_ABORT
};

template<typename arrayType>
class JArray {
    typedef typename JArrayType<arrayType>::_JType JType;
    JniEnv _env;
    arrayType _array;
    JType* _data;

    enum JArraySource {
        NONE,
        ELEMENTS,
        REGION
    } _filled;

    jsize _offset;
    jsize _length;
public:
    JNIH_EXPORT JArray(JniEnv env) : _env(env) {
    }

    JNIH_EXPORT JArray(JniEnv env, jsize length) : _env(env) {
        arrayType array = JArrayType<arrayType>::create(&(this->_env), length);
        this->get(array);
    }

    JNIH_EXPORT JArray(JniEnv env, arrayType array) : _env(env) {
        this->get(array);
    }

    JNIH_EXPORT JArray(JniEnv env, arrayType array, jsize offset, jsize length) : _env(env) {
        this->get(array, offset, length);
    }

    JNIH_EXPORT JArray(JArray<arrayType> &other) : _env(other._env) {
        switch(other._filled) {
        case JArraySource::REGION:
            this->get(other._array, other._offset, other._length);
            break;

        case JArraySource::ELEMENTS:
            this->get(other._array);
            break;
        }
    }

    JNIH_EXPORT JArray<arrayType>& operator=(JArray<arrayType> &other) {
        if (this != &other) {
            this->release();
            this->_env = other._env;
            switch(other._filled) {
            case JArraySource::REGION:
                this->get(other._array, other._offset, other._length);
                break;

            case JArraySource::ELEMENTS:
                this->get(other._array);
                break;
            }
        }
        return *this;
    }

    JNIH_EXPORT ~JArray() {
        this->release();
    }

    JNIH_EXPORT void get(arrayType array) {
        this->_data = JArrayType<arrayType>::get(&(this->_env), array);
        this->_filled = JArraySource::ELEMENTS;
        this->_array = array;
    }

    JNIH_EXPORT void get(arrayType array, jsize offset, jsize length) {
        JArrayType<arrayType>::getRegion(&(this->_env), array, offset, length, this->_data);
        this->_filled = JArraySource::REGION;
        this->_array = array;
        this->_offset = offset;
        this->_length = length;
    }

    JNIH_EXPORT JType* getData() {
        return this->_data;
    }

    JNIH_EXPORT arrayType getArray() {
        return this->_array;
    }

    JNIH_EXPORT jsize getLength() {
        return this->_length;
    }

    JNIH_EXPORT void release() {
        switch(this->_filled) {
        case JArraySource::ELEMENTS:
            JArrayType<arrayType>::set(&(this->_env), this->_array, this->_data, JArrayAction::RELEASE);
            break;

        case JArraySource::REGION:
            JArrayType<arrayType>::setRegion(&(this->_env), this->_array, this->_offset, this->_length, this->_data);
            break;
        }
        this->_filled = JArraySource::NONE;
    }

    JNIH_EXPORT void commit() {
        switch(this->_filled) {
        case JArraySource::ELEMENTS:
            JArrayType<arrayType>::set(&(this->_env), this->_array, this->_data, JArrayAction::COMMIT);
            break;

        case JArraySource::REGION:
             JArrayType<arrayType>::setRegion(&(this->_env), this->_array, this->_offset, this->_length, this->_data);
            break;
        }
    }

    JNIH_EXPORT void abort() {
        switch(this->_filled) {
        case JArraySource::ELEMENTS:
            JArrayType<arrayType>::set(&(this->_env), this->_array, this->_data, JArrayAction::ABORT);
            break;
        }
        this->_filled = JArraySource::NONE;
    }

};

typedef JArray<jbyteArray> JByteArray;
typedef JArray<jshortArray> JShortArray;
typedef JArray<jintArray> JIntArray;
typedef JArray<jlongArray> JLongArray;
typedef JArray<jfloatArray> JFloatArray;
typedef JArray<jdoubleArray> JDoubleArray;
typedef JArray<jcharArray> JCharArray;
typedef JArray<jbooleanArray> JBooleanArray;

#endif // !_JARRAY_H_