add_library(OrbitCore SHARED
    src/Core.cpp
    src/Renderer.cpp
    src/MetalImpl.cpp
)

find_library(METAL_FRAMEWORK Metal REQUIRED)
find_library(FOUNDATION_FRAMEWORK Foundation REQUIRED)
find_library(QUARTZCORE_FRAMEWORK QuartzCore REQUIRED)
find_library(OBJC_LIBRARY objc REQUIRED)
find_library(APPKIT_FRAMEWORK AppKit REQUIRED)
find_library(METALKIT_FRAMEWORK MetalKit REQUIRED)

target_link_libraries(OrbitCore PUBLIC 
    ${METAL_FRAMEWORK}
    ${FOUNDATION_FRAMEWORK}
    ${QUARTZCORE_FRAMEWORK}
    ${OBJC_LIBRARY}
    ${APPKIT_FRAMEWORK}
    ${METALKIT_FRAMEWORK}
)

if(APPLE)
    target_compile_options(OrbitCore PRIVATE "-fobjc-arc")
endif()

target_include_directories(OrbitCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/import/metal-cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/import/metal-cpp-extensions
)

target_compile_definitions(OrbitCore
    PRIVATE ORBIT_BUILD_DLL
)

set_target_properties(OrbitCore PROPERTIES
    CXX_VISIBILITY_PRESET hidden
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
