cmake_minimum_required(VERSION 3.15)
project(MyOpenGLExamples)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

if(UNIX)
    set(CMAKE_C_COMPILER_LAUNCHER ccache)
    set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()

# config EASTL
add_subdirectory(${CMAKE_SOURCE_DIR}/Sources/Thirdparty/EAstl)

# search headers, this function is intended for eabase&stl only.
function(collect_headers result_var base_dir)
    file(GLOB_RECURSE collected_headers
        "${base_dir}/*.h"
        "${base_dir}/*.hh"
        "${base_dir}/*.hpp"
    )
    set(${result_var} ${collected_headers} PARENT_SCOPE)
endfunction()

#config entt
add_subdirectory(${CMAKE_SOURCE_DIR}/Sources/Thirdparty/entt)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(ENGINE_HEADERS_DIRS

    ${CMAKE_SOURCE_DIR}/Sources/Engine
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Shaders
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Camera
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Utils
    ${CMAKE_SOURCE_DIR}/Sources/Engine/InputSystem
    ${CMAKE_SOURCE_DIR}/Sources/Engine/AudioSystem
    ${CMAKE_SOURCE_DIR}/Sources/Engine/PhysicSystem
    ${CMAKE_SOURCE_DIR}/Sources/Engine/AssetSystem
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem

)

set(ENGINE_HEADERS_FILES
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Common.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Engine.hh

    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Model.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/RenderSystem.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Texture.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/ShaderManager.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/ShaderFactory.hh

    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Shaders/Shader.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Shaders/PhongShader.hh


    ${CMAKE_SOURCE_DIR}/Sources/Engine/Camera/Camera.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Utils/Config.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Utils/ConfigTypes.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Utils/Logger.hh

    ${CMAKE_SOURCE_DIR}/Sources/Engine/AssetSystem/AssetSystem.hh

    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/Entity.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/StageManager.hh
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/Component.h
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/MeshComponent.h
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/TransformComponent.h

)


set(ENGINE_SOURCES_FILES 
    #engine main
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Engine.cc
                       
    #rendersystem,core, essentiaE
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Model.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/RenderSystem.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Texture.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/ShaderManager.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/ShaderFactory.cc

    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Shaders/Shader.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/RenderSystem/Shaders/PhongShader.cc


    ${CMAKE_SOURCE_DIR}/Sources/Engine/AssetSystem/AssetSystem.cc
                       
    #camera class
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Camera/Camera.cc
                       
    #utilities, like cosole output, config loader, etc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Utils/Config.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/Utils/Logger.cc

    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/Entity.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/StageManager.cc
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/Component.cpp
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/MeshComponent.cpp
    ${CMAKE_SOURCE_DIR}/Sources/Engine/ECSSystem/TransformComponent.cpp
)

set(EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/Sources/Examples")

include_directories(${INCLUDE_DIRECTORIES} ${ENGINE_HEADERS_DIRS})

####################################### add example target function #######################################



# 通用函数：为某个 target 添加资源复制规则
function(copy_resources target)
    foreach(resource IN LISTS ARGN)
        set(src "${CMAKE_SOURCE_DIR}/${resource}")
        set(dst "$<TARGET_FILE_DIR:${target}>/")

        if (IS_DIRECTORY "${src}")
            # Copy directory recursively
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${src}"
                    "${dst}/${resource}"
                COMMENT "Copying directory ${resource} -> ${dst}/${resource}"
            )
        else()
            # Copy single file
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${src}"
                    "${dst}"
                COMMENT "Copying file ${resource} -> ${dst}"
            )
        endif()
    endforeach()
endfunction()
####################################### static libraries #######################################

#collect_headers(EABASE_HEADERS ${EABASE_ROOT_DIR}/include/Common/)
#collect_headers(EASTL_HEADERS ${EASTL_ROOT_DIR}/include/)

#compile engine as a static lib, althought I have no idea if this helps something....
function(build_engine_stclib lib_name)

    add_library(${lib_name} STATIC ${ENGINE_SOURCES_FILES} ${ENGINE_HEADERS_FILES}
#    ${EABASE_HEADERS} ${EASTL_HEADERS}
    )
    target_link_libraries(${lib_name} PUBLIC

        OpenGL::GL
        GLEW::GLEW
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_image::SDL2_image
        glm::glm    
        assimp::assimp
        yaml-cpp::yaml-cpp
        spdlog::spdlog

        # Modified stl
        EASTL
        EnTT::EnTT
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


add_example(Sandbox)

copy_resources(Sandbox resources/defaulttexture.png)
copy_resources(Sandbox engine.cfg)
copy_resources(Sandbox resources)




########WINDOWS DEBUG ZONE###########
set(debug_sourcesfile "${CMAKE_SOURCE_DIR}/Sources/Examples/debugtest/test.cc")
add_executable(debugtest  ${debug_sourcesfile})
target_link_libraries(debugtest PUBLIC 
    assimp::assimp
)
