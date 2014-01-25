#ifndef _JSTRING_H_
#define _JSTRING_H_

#include "JniHelper.h"

class JString {
    JNIEnv* _env;
    jstring _jstr;
    const char* _str;
    long _length;
    bool _released;
public:
    JNIH_EXPORT JString(JNIEnv* env);
    JNIH_EXPORT JString(JNIEnv* env, jstring jstr);
    JNIH_EXPORT JString(JNIEnv* env, const char* str);
    JNIH_EXPORT JString(JString& other);
    JNIH_EXPORT JString& operator=(JString& other);
    JNIH_EXPORT ~JString();
    JNIH_EXPORT void create(const char* str);
    JNIH_EXPORT void get(jstring jstr);
    JNIH_EXPORT void release();
    JNIH_EXPORT long getLength();
    JNIH_EXPORT const char* getCString();
    JNIH_EXPORT jstring getJString();
};

class JWString {
    JNIEnv* _env;
    jstring _jstr;
    const wchar_t* _str;
    long _length;
    bool _released;
public:
    JNIH_EXPORT JWString(JNIEnv* env);
    JNIH_EXPORT JWString(JNIEnv* env, jstring jstr);
    JNIH_EXPORT JWString(JNIEnv* env, const wchar_t* str);
    JNIH_EXPORT JWString(JWString& other);
    JNIH_EXPORT JWString& operator=(JWString& other);
    JNIH_EXPORT ~JWString();
    JNIH_EXPORT void create(const wchar_t*);
    JNIH_EXPORT void get(jstring str);
    JNIH_EXPORT void release();
    JNIH_EXPORT long getLength();
    JNIH_EXPORT const wchar_t* getCString();
    JNIH_EXPORT jstring getJString();
};

#ifdef UNICODE
typedef JWString JTString;
#else
typedef JString JTString;
#endif

#endif // !_JSTRING_H_
