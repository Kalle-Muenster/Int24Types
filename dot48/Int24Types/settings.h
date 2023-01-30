#ifndef  INT24_BUILD_CONFIGURATION
#define  SET_VERSION_STRING INT24TYPES_VERSION
#include <versionmacro.h>
#define  INT24TYPES_VERSION_NUMBER VERSION_NUMBER
#define  INT24TYPES_VERSION_STRING VERSION_STRING
#define  SET_NAMESPACE stepflow
#if defined( __x86_64__) || defined(_WIN64)
#define  INT24TYPES_CPU_ARCHITECTURE L"x64"
#define  WORD_PRCISION double
#elif defined(_M_IX86) || defined(__x86__)
#define  INT24TYPES_CPU_ARCHITECTURE L"x86"
#define  WORD_PRCISION float
#endif
#define  USE_HALFFLOAT (1)
#ifdef  _DEBUG
#define  INT24_BUILD_CONFIGURATION L"Debug"
#else
#define  INT24_BUILD_CONFIGURATION L"Release"
#endif
#define  HALF_ENABLE_CPP11_USER_LITERALS (0)
#endif
