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

set(ENGINE_HEADERS_DIRS

    ${CMAKE_SOURCE_DIR}/sources/engine
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem
    ${CMAKE_SOURCE_DIR}/sources/engine/camera
    ${CMAKE_SOURCE_DIR}/sources/engine/utils
    ${CMAKE_SOURCE_DIR}/sources/engine/inputsystem
    ${CMAKE_SOURCE_DIR}/sources/engine/audiosystem
    ${CMAKE_SOURCE_DIR}/sources/engine/physicsystem
    ${CMAKE_SOURCE_DIR}/sources/engine/assetsystem
)

set(ENGINE_HEADERS_FILES
    ${CMAKE_SOURCE_DIR}/sources/engine/common.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/engine.hh

    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/CustShader.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/modelloader.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/rendersystem.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/ShaderFinal.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/textureSdlGl.hh

    ${CMAKE_SOURCE_DIR}/sources/engine/camera/Camera.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/utils/dbgJellyfish.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/utils/config.hh
    ${CMAKE_SOURCE_DIR}/sources/engine/utils/configtypes.hh

    ${CMAKE_SOURCE_DIR}/sources/engine/assetsystem/assetsystem.hh
)


set(ENGINE_SOURCES_FILES 
    #engine main
    ${CMAKE_SOURCE_DIR}/sources/engine/engine.cc
                       
    #rendersystem,core, essential
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/CustShader.cc
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/modelloader.cc
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/rendersystem.cc
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/ShaderFinal.cc
    ${CMAKE_SOURCE_DIR}/sources/engine/rendersystem/textureSdlGl.cc


    ${CMAKE_SOURCE_DIR}/sources/engine/assetsystem/assetsystem.cc
                       
    #camera class
    ${CMAKE_SOURCE_DIR}/sources/engine/camera/Camera.cc
                       
    #utilities, like cosole output debugger, config loader, etc
    ${CMAKE_SOURCE_DIR}/sources/engine/utils/dbgJellyfish.cc
    ${CMAKE_SOURCE_DIR}/sources/engine/utils/config.cc
)

set(EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/sources/examples")

include_directories(${INCLUDE_DIRECTORIES} ${ENGINE_HEADERS_DIRS})

####################################### add example target function #######################################



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

    add_library(${lib_name} STATIC ${ENGINE_SOURCES_FILES} ${ENGINE_HEADERS_FILES})
    target_link_libraries(${lib_name} PUBLIC

        OpenGL::GL
        GLEW::GLEW
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        glm::glm    
        assimp::assimp
        yaml-cpp::yaml-cpp
    )

endfunction()


build_engine_stclib(engine)

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
    target_include_directories(${example_name} PRIVATE 
        "${INCLUDE_DIRECTORIES}"
        "${EXAMPLES_DIR}/${example_name}/" 
    )
    target_link_libraries(${example_name} PRIVATE engine )

endfunction()


add_example(sandbox)

copy_resources(sandbox resources/defaulttexture.png)




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
