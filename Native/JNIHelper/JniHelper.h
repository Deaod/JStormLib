#ifndef _JNIHELPER_H_
#define _JNIHELPER_H_

#if defined(_WIN32) // _WIN32 is defined for both 32bit and 64bit
# if defined(_MSC_VER)
// were compiling for windows using MS VC++
#   if defined(_WIN64)
#     define WIN64
#   else
#     define WIN32
#   endif

#   if defined(__JNIHELPER_SELF__)
#     define JNIH_EXPORT __declspec(dllexport)
#   else
#       define JNIH_EXPORT //__declspec(dllimport)
#   endif
#   define JNIH_CURRENT_FUNCTION __FUNCTION__
#   define JNIH_THREAD_LOCAL __declspec(thread)

#   if !defined(__JNIHELPER_SELF__)
  
#     ifdef _DEBUG                                 // DEBUG VERSIONS
#       ifndef _UNICODE                            
#         ifdef _DLL                               
#           pragma comment(lib, "JNIHelperDAD.lib") // Debug Ansi CRT-DLL version
#         else        
#           pragma comment(lib, "JNIHelperDAS.lib") // Debug Ansi CRT-LIB version
#         endif
#       else
#         ifdef _DLL                               
#           pragma comment(lib, "JNIHelperDUD.lib") // Debug Unicode CRT-DLL version
#         else        
#           pragma comment(lib, "JNIHelperDUS.lib") // Debug Unicode CRT-LIB version
#         endif
#       endif
#     else                                         // RELEASE VERSIONS
#       ifndef _UNICODE                            
#         ifdef _DLL
#           pragma comment(lib, "JNIHelperRAD.lib") // Release Ansi CRT-DLL version
#         else        
#           pragma comment(lib, "JNIHelperRAS.lib") // Release Ansi CRT-LIB version
#         endif
#       else
#         ifdef _DLL
#           pragma comment(lib, "JNIHelperRUD.lib") // Release Unicode CRT-DLL version
#         else        
#           pragma comment(lib, "JNIHelperRUS.lib") // Release Unicode CRT-LIB version
#         endif
#       endif
#     endif

#   endif

# elif defined(__GNUC__)

# elif defined(__MINGW32__) // __MINGW32__ is defined for both 32bit and 64bit

# endif
#elif defined(__linux__)

#endif

#include "jni.h"

#define C_Boolean "java/lang/Boolean"
#define C_Byte    "java/lang/Byte"
#define C_Char    "java/lang/Char"
#define C_Short   "java/lang/Short"
#define C_Integer "java/lang/Integer"
#define C_Long    "java/lang/Long"
#define C_Float   "java/lang/Float"
#define C_Double  "java/lang/Double"
#define C_Object  "java/lang/Object"
#define C_String  "java/lang/String"

#define JNI_ClassToField(objClass)   "L" objClass ";"
#define JNI_InnerClass(outer, inner) outer "$" inner
#define JNI_Array(field)             "[" field
#define JNI_Array2D(field)           JNI_Array(JNI_Array(field))
#define JNI_Array3D(field)           JNI_Array(JNI_Array2D(field))
#define JNI_Constructor              "<init>"

#define F_Boolean JNI_ClassToField(C_Boolean)
#define F_Byte    JNI_ClassToField(C_Byte)
#define F_Char    JNI_ClassToField(C_Char)
#define F_Short   JNI_ClassToField(C_Short)
#define F_Integer JNI_ClassToField(C_Integer)
#define F_Long    JNI_ClassToField(C_Long)
#define F_Float   JNI_ClassToField(C_Float)
#define F_Double  JNI_ClassToField(C_Double)
#define F_Object  JNI_ClassToField(C_Object)
#define F_String  JNI_ClassToField(C_String)

#define JNI_byte    "B"
#define JNI_char    "C"
#define JNI_short   "S"
#define JNI_int     "I"
#define JNI_long    "J"
#define JNI_float   "F"
#define JNI_double  "D"
#define JNI_boolean "Z"
#define JNI_void    "V"

#define JNI_BYTE_ARRAY    JNI_Array(JNI_byte)
#define JNI_CHAR_ARRAY    JNI_Array(JNI_char)
#define JNI_SHORT_ARRAY   JNI_Array(JNI_short)
#define JNI_INT_ARRAY     JNI_Array(JNI_int)
#define JNI_LONG_ARRAY    JNI_Array(JNI_long)
#define JNI_FLOAT_ARRAY   JNI_Array(JNI_float)
#define JNI_DOUBLE_ARRAY  JNI_Array(JNI_double)
#define JNI_BOOLEAN_ARRAY JNI_Array(JNI_boolean)

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
    JNI_METHOD_0(JNI_void)

#define JNI_CONSTRUCTOR_1(param1) \
    JNI_METHOD_1(JNI_void, param1)

#define JNI_CONSTRUCTOR_2(param1, param2) \
    JNI_METHOD_2(JNI_void, param1, param2)

#define JNI_CONSTRUCTOR_3(param1, param2, param3) \
    JNI_METHOD_3(JNI_void, param1, param2, param3)

#define JNI_CONSTRUCTOR_4(param1, param2, param3, param4) \
    JNI_METHOD_4(JNI_void, param1, param2, param3, param4)

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
