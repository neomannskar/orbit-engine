#pragma once

#if defined(_WIN32)
    #if defined(ORBIT_BUILD_DLL)
        #define ORBIT_API __declspec(dllexport)
    #else
        #define ORBIT_API __declspec(dllimport)
    #endif
#else
    #define ORBIT_API __attribute__((visibility("default")))

    #include <Foundation/Foundation.hpp>
    #include <Metal/Metal.hpp>
    #include <QuartzCore/QuartzCore.hpp>
    #include <AppKit/AppKit.hpp>
    #include <MetalKit/MetalKit.hpp>
#endif
