add_executable(OrbitApp
    src/main.cpp
)

target_link_libraries(OrbitApp
    PRIVATE OrbitCore
)

if(WIN32)
    add_custom_command(TARGET OrbitApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:OrbitCore>
            $<TARGET_FILE_DIR:OrbitApp>
    )
endif()
