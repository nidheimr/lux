#
#   project
#

cmake_minimum_required(VERSION 3.20)
project(lux C)

set(common_bin_dir ${CMAKE_SOURCE_DIR}/bin/$<0:>)

if(WIN32)
    set(PLATFORM_WINDOWS TRUE)
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_LINUX TRUE)
else()
    message(FATAL_ERROR, "unsupported platform, supported platforms include: windows, linux (wayland)")
endif()

#
#   library
#

file(GLOB_RECURSE lib_files CONFIGURE_DEPENDS src/*.c)

if(PLATFORM_WINDOWS)
    list(FILTER lib_files EXCLUDE REGEX "_linux\\.c$")
    add_library(lux SHARED ${lib_files})

    target_link_libraries(lux PRIVATE
        opengl32
        gdi32
        user32
    )
elseif(PLATFORM_LINUX)
    list(FILTER lib_files EXCLUDE REGEX "_win32\\.c$")
    add_library(lux SHARED ${lib_files})

    target_link_libraries(lux PRIVATE
        wayland-client
        wayland-egl
        EGL
        GL
        m
    )    
endif()

set_target_properties(lux PROPERTIES
    C_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY ${common_bin_dir}
    ARCHIVE_OUTPUT_DIRECTORY ${common_bin_dir}
    LIBRARY_OUTPUT_DIRECTORY ${common_bin_dir}
)

target_include_directories(lux PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_definitions(lux PRIVATE
    LX_BUILD
)

#
#   test executable
#

if(BUILD_TEST_EXECUTABLE)
    file(GLOB_RECURSE test_files CONFIGURE_DEPENDS tests/*.c)
    add_executable(test ${test_files})

    target_link_libraries(test PRIVATE
        lux
    )

    set_target_properties(test PROPERTIES
        C_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY ${common_bin_dir}
    )

    target_include_directories(test PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
    )
endif()
