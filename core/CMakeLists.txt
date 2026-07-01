add_library(OrbitCore SHARED
    src/Core.cpp
)

target_include_directories(OrbitCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(OrbitCore
    PRIVATE ORBIT_BUILD_DLL
)

set_target_properties(OrbitCore PROPERTIES
    CXX_VISIBILITY_PRESET hidden
)
