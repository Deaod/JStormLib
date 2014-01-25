#ifndef _JNIHELPER_H_
#define _JNIHELPER_H_

#if defined(_WIN32) // _WIN32 is defined for both 32bit and 64bit
#   if defined(_MSC_VER)
// were compiling for windows using MS VC++
#       if defined(_WIN64)
#           define WIN64
#       else
#           define WIN32
#       endif

#       if defined(__JNIHELPER_SELF__)
#           define JNIH_EXPORT __declspec(dllexport)
#       else
#           define JNIH_EXPORT //__declspec(dllimport)
#       endif
#       define JNIH_CURRENT_FUNCTION __FUNCTION__
#       define JNIH_THREAD_LOCAL __declspec(thread)

#       if !defined(__JNIHELPER_SELF__)
  
#           ifdef _DEBUG                                 // DEBUG VERSIONS
#               ifndef _UNICODE                            
#                   ifdef _DLL                               
#                       pragma comment(lib, "JNIHelperDAD.lib") // Debug Ansi CRT-DLL version
#                   else        
#                       pragma comment(lib, "JNIHelperDAS.lib") // Debug Ansi CRT-LIB version
#                   endif
#               else
#                   ifdef _DLL                               
#                       pragma comment(lib, "JNIHelperDUD.lib") // Debug Unicode CRT-DLL version
#                   else        
#                       pragma comment(lib, "JNIHelperDUS.lib") // Debug Unicode CRT-LIB version
#                   endif
#               endif
#           else                                         // RELEASE VERSIONS
#               ifndef _UNICODE                            
#                   ifdef _DLL
#                       pragma comment(lib, "JNIHelperRAD.lib") // Release Ansi CRT-DLL version
#                   else        
#                       pragma comment(lib, "JNIHelperRAS.lib") // Release Ansi CRT-LIB version
#                   endif
#               else
#                   ifdef _DLL
#                       pragma comment(lib, "JNIHelperRUD.lib") // Release Unicode CRT-DLL version
#                   else        
#                       pragma comment(lib, "JNIHelperRUS.lib") // Release Unicode CRT-LIB version
#                   endif
#               endif
#           endif

#       endif

#   elif defined(__GNUC__)

#   elif defined(__MINGW32__) // __MINGW32__ is defined for both 32bit and 64bit

#   endif
#elif defined(__linux__)

#endif

#include "jni.h"

#define CLASS_BOOLEAN "java/lang/Boolean"
#define CLASS_BYTE    "java/lang/Byte"
#define CLASS_CHAR    "java/lang/Char"
#define CLASS_SHORT   "java/lang/Short"
#define CLASS_INTEGER "java/lang/Integer"
#define CLASS_LONG    "java/lang/Long"
#define CLASS_FLOAT   "java/lang/Float"
#define CLASS_DOUBLE  "java/lang/Double"
#define CLASS_OBJECT  "java/lang/Object"
#define CLASS_STRING  "java/lang/String"

#define JNI_FIELD_CLASS(objClass)     "L" objClass ";"
#define JNI_INNER_CLASS(outer, inner) outer "$" inner
#define JNI_ARRAY(type)               "[" type
#define JNI_ARRAY_2D(type)            JNI_ARRAY(JNI_ARRAY(type))
#define JNI_ARRAY_3D(type)            JNI_ARRAY(JNI_ARRAY_2D(type))
#define JNI_CONSTRUCTOR               "<init>"

#define JNI_FIELD_OBJECT  JNI_FIELD_CLASS(CLASS_OBJECT)
#define JNI_FIELD_BYTE    JNI_FIELD_CLASS(CLASS_BYTE)
#define JNI_FIELD_CHAR    JNI_FIELD_CLASS(CLASS_CHAR)
#define JNI_FIELD_SHORT   JNI_FIELD_CLASS(CLASS_SHORT)
#define JNI_FIELD_INTEGER JNI_FIELD_CLASS(CLASS_INTEGER)
#define JNI_FIELD_LONG    JNI_FIELD_CLASS(CLASS_LONG)
#define JNI_FIELD_FLOAT   JNI_FIELD_CLASS(CLASS_FLOAT)
#define JNI_FIELD_DOUBLE  JNI_FIELD_CLASS(CLASS_DOUBLE)
#define JNI_FIELD_BOOLEAN JNI_FIELD_CLASS(CLASS_BOOLEAN)
#define JNI_FIELD_STRING  JNI_FIELD_CLASS(CLASS_STRING)

#define JNI_BYTE    "B"
#define JNI_CHAR    "C"
#define JNI_SHORT   "S"
#define JNI_INT     "I"
#define JNI_LONG    "J"
#define JNI_FLOAT   "F"
#define JNI_DOUBLE  "D"
#define JNI_BOOLEAN "Z"
#define JNI_VOID    "V"

#define JNI_BYTE_ARRAY    JNI_ARRAY(JNI_BYTE)
#define JNI_CHAR_ARRAY    JNI_ARRAY(JNI_CHAR)
#define JNI_SHORT_ARRAY   JNI_ARRAY(JNI_SHORT)
#define JNI_INT_ARRAY     JNI_ARRAY(JNI_INT)
#define JNI_LONG_ARRAY    JNI_ARRAY(JNI_LONG)
#define JNI_FLOAT_ARRAY   JNI_ARRAY(JNI_FLOAT)
#define JNI_DOUBLE_ARRAY  JNI_ARRAY(JNI_DOUBLE)
#define JNI_BOOLEAN_ARRAY JNI_ARRAY(JNI_BOOLEAN)

#define JNI_METHOD_0(returnType) \
    "()" returnType

#define JNI_METHOD_1(returnType, param1) \
    "(" param1 ")" returnType

#define JNI_METHOD_2(returnType, param1, param2) \
    "(" param1 param2 ")" returnType

#define JNI_METHOD_3(returnType, param1, param2, param3) \
    "(" param1 param2 param3 ")" returnType

#define JNI_METHOD_4(returnType, param1, param2, param3, param4) \
    "(" param1 param2 param3 param4 ")" returnType

#define JNI_CONSTRUCTOR_0() \
    JNI_METHOD_0(JNI_VOID)

#define JNI_CONSTRUCTOR_1(param1) \
    JNI_METHOD_1(JNI_VOID, param1)

#define JNI_CONSTRUCTOR_2(param1, param2) \
    JNI_METHOD_2(JNI_VOID, param1, param2)

#define JNI_CONSTRUCTOR_3(param1, param2, param3) \
    JNI_METHOD_3(JNI_VOID, param1, param2, param3)

#define JNI_CONSTRUCTOR_4(param1, param2, param3, param4) \
    JNI_METHOD_4(JNI_VOID, param1, param2, param3, param4)

#define JNIC_CLASS   'L'
#define JNIC_ARRAY   '['
#define JNIC_BYTE    'B'
#define JNIC_CHAR    'C'
#define JNIC_SHORT   'S'
#define JNIC_INT     'I'
#define JNIC_LONG    'J'
#define JNIC_FLOAT   'F'
#define JNIC_DOUBLE  'D'
#define JNIC_BOOLEAN 'Z'

class JNIException {

};

// empty parameter list because it enables folding in VS2012
#define JNIH_EXCEPTION_TRAP_BEGIN() \
{ \
    try

#define JNIH_EXCEPTION_TRAP_BEGIN_EX(env, env_wrapper_name) \
{ \
    JniEnv env_wrapper_name(env); \
    try 

#define JNIH_EXCEPTION_TRAP_END \
    catch (...) { \
    } \
    return 0; \
}

#define JNIH_EXCEPTION_TRAP_END2 \
    catch (...) { \
    } \
}

#endif // !_JNIHELPER_H_
