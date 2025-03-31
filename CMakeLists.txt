#
#   project
#

cmake_minimum_required(VERSION 3.20)
project(lux C)

set(common_bin_dir ${CMAKE_SOURCE_DIR}/bin/$<0:>)

#
#   library
#

file(GLOB_RECURSE lib_files CONFIGURE_DEPENDS src/*.c)
add_library(lux STATIC ${lib_files})

target_link_libraries(lux PRIVATE
    opengl32
    gdi32
    user32
)

set_target_properties(lux PROPERTIES
    C_STANDARD 17

    RUNTIME_OUTPUT_DIRECTORY ${common_bin_dir}
    ARCHIVE_OUTPUT_DIRECTORY ${common_bin_dir}
    LIBRARY_OUTPUT_DIRECTORY ${common_bin_dir}
)

target_include_directories(lux PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

#
#   tests
#

if(BUILD_TEST_EXECUTABLE)

    file(GLOB_RECURSE test_files CONFIGURE_DEPENDS tests/*.c)
    add_executable(tests ${test_files})

    target_link_libraries(tests PRIVATE
        lux
    )

    target_include_directories(tests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
    )

    set_target_properties(tests PROPERTIES
        C_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY ${common_bin_dir}
    )

endif()