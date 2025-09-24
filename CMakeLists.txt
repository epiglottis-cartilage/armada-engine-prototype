cmake_minimum_required(VERSION 3.15)
project(MyOpenGLExamples)

# 设定 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    set(CMAKE_C_COMPILER_LAUNCHER ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()


find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)



set(ENGINE_SOURCES_FILES 
    #engine main
    ${CMAKE_SOURCES_DIR}/sources/engine/common.hh
    ${CMAKE_SOURCES_DIR}/sources/engine/engine.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/engine.hh
                        /
    ${CMAKE_SOURCES_DIR}/#rendersystem, core, essential
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/CustShader.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/CustShader.hh
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/modelloader.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/modelloader.hh
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/rendersystem.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/rendersystem.hh
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/ShaderFinal.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/ShaderFinal.hh
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/textureSdlGl.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/rendersystem/textureSdlGl.hh
                        /
    ${CMAKE_SOURCES_DIR}/#camera class
    ${CMAKE_SOURCES_DIR}/sources/engine/camera/Camera.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/camera/Camera.hh
                        /
    ${CMAKE_SOURCES_DIR}/#utilities, like cosole output debugger, config loader, etc
    ${CMAKE_SOURCES_DIR}/sources/engine/utils/dbgJellyfish.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/utils/dbgJellyfish.hh
    ${CMAKE_SOURCES_DIR}/sources/engine/utils/config.cc
    ${CMAKE_SOURCES_DIR}/sources/engine/utils/config.hh
    ${CMAKE_SOURCES_DIR}/sources/engine/utils/configtypes.hh
)

set(EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/sources/examples")

####################################### add example target function #######################################

# 定义一个函数，创建一个名为 `example_name` 的构建目标
function(add_example example_name)
    file(GLOB_RECURSE EXAMPLE_SOURCES 
            "${EXAMPLES_DIR}/${example_name}/*.cc"
            "${EXAMPLES_DIR}/${example_name}/*.hh"
        )

    # 如果找不到任何源文件，报错
    if(NOT EXAMPLE_SOURCES)
        message(FATAL_ERROR "No source files found for example '${example_name}'")
    endif()

    add_executable(${example_name} ${ENGINE_SOURCES_FILES} ${EXAMPLE_SOURCES})

    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${example_name}"
    )

endfunction()

function(add_example_debug example_name)
    file(GLOB_RECURSE EXAMPLE_SOURCES 
            "${EXAMPLES_DIR}/${example_name}/*.cc"
            "${EXAMPLES_DIR}/${example_name}/*.hh"
        )

    # 如果找不到任何源文件，报错
    if(NOT EXAMPLE_SOURCES)
        message(FATAL_ERROR "No source files found for example '${example_name}'")
    endif()

    add_executable(${example_name} ${ENGINE_SOURCES_FILES} ${EXAMPLE_SOURCES})

    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${example_name}"
    )

    target_compile_definitions(${example_name} PRIVATE DEBUG)
endfunction()


# 通用函数：为某个 target 添加资源复制规则
function(copy_resources target)
    foreach(resource IN LISTS ARGN)
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_SOURCE_DIR}/${resource}"
                $<TARGET_FILE_DIR:${target}>/
        )
    endforeach()
endfunction()
####################################### static libraries #######################################

#compile engine as a static lib, althought I have no idea if this helps something....
function(build_engine_stclib lib_name)

    add_library(${lib_name} STATIC ${ENGINE_SOURCES_FILES})

endfunction()

function(build_engine_stclib_debug lib_name)

    add_library(${lib_name} STATIC ${ENGINE_SOURCES_FILES})

    target_compile_definitions(${lib_name} PRIVATE DEBUG)
endfunction()



add_example(sandbox)
copy_resources(farlight resources/defaulttexture.png)


target_link_libraries(farlight PRIVATE
    txbridge
    moncams
    isl
    modelconverter

    OpenGL::GL
    GLEW::GLEW
    SDL2::SDL2
#not sure if this line breaks compilation on linux.....
    SDL2::SDL2main
#line end
    SDL2_image::SDL2_image
    glm::glm    
    assimp::assimp

)


########WINDOWS DEBUG ZONE###########
#set(debug_sourcesfile "${CMAKE_SOURCE_DIR}/sources/examples/debug_sources/*.cc")

add_example(debug_sources)
target_link_libraries(debug_sources PRIVATE 
    OpenGL::GL
    GLEW::GLEW
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    glm::glm    
    assimp::assimp
)
