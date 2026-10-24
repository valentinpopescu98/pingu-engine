cmake_minimum_required(VERSION 3.21)
project(pingu-engine LANGUAGES C CXX)

# Compile the existing Visual Studio .rc file into the Windows executable.
if(WIN32)
    enable_language(RC)
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
if(WIN32)
    # Fresh official-source ports built by vcpkg; old committed Windows binaries are not used.
    find_package(glfw3 CONFIG REQUIRED)
    find_package(assimp CONFIG REQUIRED)
    find_package(Lua REQUIRED)
else()
    # Link directly against the shared libraries checked into the repository.
    # OpenGL/GLVND and GPU drivers remain system-provided.
    set(VENDORED_LINUX_LIB "${CMAKE_CURRENT_SOURCE_DIR}/deps/linux/x86_64/lib")
    foreach(_name libglfw.so.3 libassimp.so.5 liblua5.4.so.0 libdraco.so.4)
        if(NOT EXISTS "${VENDORED_LINUX_LIB}/${_name}")
            message(FATAL_ERROR "Missing vendored Linux library: ${_name}; restore the verified Ubuntu 22.04 package binary")
        endif()
    endforeach()
endif()

# Vendored GLAD, Dear ImGui, pugixml, stb and GLM live under deps/.
file(GLOB ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp")
set(VENDORED_SOURCES
    deps/src/glad.c
    deps/src/imgui.cpp
    deps/src/imgui_draw.cpp
    deps/src/imgui_tables.cpp
    deps/src/imgui_widgets.cpp
    deps/src/imgui_impl_glfw.cpp
    deps/src/imgui_impl_opengl3.cpp
    deps/src/pugixml.cpp
    deps/src/stb.c
)

add_executable(pingu-engine src/main.cpp ${ENGINE_SOURCES} ${VENDORED_SOURCES})
if(WIN32)
    target_sources(pingu-engine PRIVATE vs/PinguEngine.rc)
    target_include_directories(pingu-engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vs")
endif()
target_include_directories(pingu-engine PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/include"
)
target_link_libraries(pingu-engine PRIVATE OpenGL::GL)
if(WIN32)
    target_link_libraries(pingu-engine PRIVATE glfw assimp::assimp ${LUA_LIBRARIES})
    target_include_directories(pingu-engine PRIVATE ${LUA_INCLUDE_DIR})
else()
    target_link_libraries(pingu-engine PRIVATE
        "${VENDORED_LINUX_LIB}/libglfw.so.3"
        "${VENDORED_LINUX_LIB}/libassimp.so.5"
        "${VENDORED_LINUX_LIB}/liblua5.4.so.0")

endif()

# Keep application dependencies beside the executable. Avoid bundling glibc,
# libstdc++, GLVND, Mesa or GPU drivers.
if(UNIX AND NOT APPLE)
    set_target_properties(pingu-engine PROPERTIES
        BUILD_RPATH "$ORIGIN/lib"
        INSTALL_RPATH "$ORIGIN/lib")
    # RUNPATH on the executable is not inherited for indirect dependencies.
    # Each bundled shared object must also locate its siblings.
    find_program(PATCHELF_EXECUTABLE patchelf REQUIRED)
    add_custom_command(TARGET pingu-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:pingu-engine>/lib"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${VENDORED_LINUX_LIB}"
            "$<TARGET_FILE_DIR:pingu-engine>/lib"
        # Patch copies, not the checked-in ELF files.
        COMMAND ${PATCHELF_EXECUTABLE} --set-rpath "$ORIGIN/lib" "$<TARGET_FILE:pingu-engine>"
        COMMAND ${CMAKE_COMMAND} -DLIB_DIR=$<TARGET_FILE_DIR:pingu-engine>/lib -DPATCHELF=${PATCHELF_EXECUTABLE} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patch-linux-libs.cmake
        VERBATIM)
endif()

# Source code uses repo-root-relative paths for shaders, scenes and textures.
set_target_properties(pingu-engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
add_custom_command(TARGET pingu-engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
        "$<TARGET_FILE_DIR:pingu-engine>/src/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/xml"
        "$<TARGET_FILE_DIR:pingu-engine>/src/xml"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:pingu-engine>/resources"
    VERBATIM
)
if(WIN32)
    # The vcpkg toolchain knows the runtime triplet. Copy all runtime DLLs,
    # including Assimp's transitive dependencies, from its bin directory.
    if(NOT DEFINED VCPKG_INSTALLED_DIR OR NOT DEFINED VCPKG_TARGET_TRIPLET)
        message(FATAL_ERROR "Windows builds require the vcpkg toolchain")
    endif()
    set(_vcpkg_bin "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(_vcpkg_bin "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug/bin")
    endif()
    file(GLOB _runtime_dlls "${_vcpkg_bin}/*.dll")
    if(NOT _runtime_dlls)
        message(FATAL_ERROR "No vcpkg runtime DLLs found in ${_vcpkg_bin}")
    endif()
    add_custom_command(TARGET pingu-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${_runtime_dlls} "$<TARGET_FILE_DIR:pingu-engine>"
        COMMAND_EXPAND_LISTS VERBATIM)
endif()
