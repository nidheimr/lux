#pragma once

#ifdef __cplusplus
    #define LX_BEGIN_HEADER extern "C" {
    #define LX_END_HEADER }
#else
    #define LX_BEGIN_HEADER
    #define LX_END_HEADER
#endif

#ifdef _WIN32
    #ifdef LX_BUILD
        #define LX_API __declspec(dllexport)
    #else
        #define LX_API __declspec(dllimport)
    #endif
#else
    #define LX_API
#endif
