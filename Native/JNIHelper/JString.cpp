#include "JString.h"
#include <cstring>

JNIH_EXPORT JString::JString(JNIEnv* env) 
    : _env(env), _jstr(NULL), _str(NULL), _length(0), _released(true) {
}

JNIH_EXPORT JString::JString(JNIEnv* env, jstring jstr) 
    : _env(env), _jstr(NULL), _str(NULL), _length(0), _released(true) {
    this->get(jstr);
}

JNIH_EXPORT JString::JString(JNIEnv* env, const char* str) 
    : _env(env), _jstr(NULL), _str(NULL), _length(0), _released(true) {
    this->create(str);
}

JNIH_EXPORT JString::JString(JString& other) 
    : _env(other._env), _jstr(NULL), _str(NULL), _length(0), _released(true) {
    this->get(other._jstr);
}

JNIH_EXPORT JString::~JString() {
    this->release();
}

JNIH_EXPORT void JString::create(const char* str) {
    if (_released == true && str && _str != str) {
        this->release();
        _jstr = _env->NewStringUTF(str);
        _length = _env->GetStringUTFLength(_jstr);
        _str = str;
        _released = false;
    }
}

JNIH_EXPORT void JString::get(jstring jstr) {
    if (_released == true && jstr && _jstr != jstr) {
        this->release();
        _str = _env->GetStringUTFChars(jstr, NULL);
        _length = _env->GetStringUTFLength(jstr);
        _jstr = jstr;
        _released = false;
    }
}

JNIH_EXPORT void JString::release() {
    if (_released == false) {
        _env->ReleaseStringUTFChars(_jstr, _str);
        _length = 0;
        _jstr = NULL;
        _str = NULL;
        _released = true;
    }
}

JNIH_EXPORT long JString::getLength() {
    return _length;
}

JNIH_EXPORT const char* JString::getCString() {
    return _str;
}

JNIH_EXPORT jstring JString::getJString() {
    return _jstr;
}



JNIH_EXPORT JWString::JWString(JNIEnv* env) : _env(env), _released(true) {
}

JNIH_EXPORT JWString::JWString(JNIEnv* env, jstring jstr) : _env(env), _released(true) {
    this->get(jstr);
}

JNIH_EXPORT JWString::JWString(JNIEnv* env, const wchar_t* str) : _env(env), _released(true) {
    this->create(str);
}

JNIH_EXPORT JWString::~JWString() {
    this->release();
}

JNIH_EXPORT void JWString::create(const wchar_t* str) {
    if (_released == true && str && _str != str) {
        this->release();
        _jstr = _env->NewString(reinterpret_cast<const jchar*>(str), static_cast<jsize>(wcslen(str)));
        _length = _env->GetStringLength(_jstr);
        _str = str;
        _released = false;
    }
}

JNIH_EXPORT void JWString::get(jstring jstr) {
    if (_released == true && jstr && _jstr != jstr) {
        this->release();
        _str = reinterpret_cast<const wchar_t*>(_env->GetStringChars(jstr, NULL));
        _length = _env->GetStringLength(jstr);
        _jstr = jstr;
        _released = false;
    }
}

JNIH_EXPORT void JWString::release() {
    if (_released == false) {
        _env->ReleaseStringChars(_jstr, reinterpret_cast<const jchar*>(_str));
        _length = 0;
        _jstr = NULL;
        _str = NULL;
        _released = true;
    }
}

JNIH_EXPORT long JWString::getLength() {
    return _length;
}

JNIH_EXPORT const wchar_t* JWString::getCString() {
    return _str;
}

JNIH_EXPORT jstring JWString::getJString() {
    return _jstr;
}
