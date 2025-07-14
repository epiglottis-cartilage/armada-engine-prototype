
cmake_minimum_required(VERSION 3.15)
project(MyOpenGLExamples)

# 设定 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER_LAUNCHER ccache)
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)


find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2_image REQUIRED)



# 添加源代码根目录
set(EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/sources/examples")

####################################### add example target function #######################################

# 定义一个函数，创建一个名为 `example_name` 的构建目标
function(add_example example_name)
    # 查找对应例子目录的源文件
    file(GLOB_RECURSE EXAMPLE_SOURCES 
        "${EXAMPLES_DIR}/${example_name}/*.cc"
        "${EXAMPLES_DIR}/${example_name}/*.hh"
    )

    # 如果找不到任何源文件，报错
    if(NOT EXAMPLE_SOURCES)
        message(FATAL_ERROR "No source files found for example '${example_name}'")
    endif()

    # 创建可执行目标
    add_executable(${example_name} ${EXAMPLE_SOURCES})

    # 设置该目标的输出路径到 build/<example_name>/ 目录中
    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${example_name}"
    )

    # 如果你有通用库或依赖，统一链接（例如 SDL2 / OpenGL / GLM 等）
    # target_link_libraries(${example_name} SDL2::SDL2 OpenGL::GLM ...) 
endfunction()

function(add_example_debug example_name)
    # 查找对应例子目录的源文件
    file(GLOB_RECURSE EXAMPLE_SOURCES 
        "${EXAMPLES_DIR}/${example_name}/*.cc"
        "${EXAMPLES_DIR}/${example_name}/*.hh"
    )

    # 如果找不到任何源文件，报错
    if(NOT EXAMPLE_SOURCES)
        message(FATAL_ERROR "No source files found for example '${example_name}'")
    endif()

    # 创建可执行目标
    add_executable(${example_name} ${EXAMPLE_SOURCES})



    # 设置该目标的输出路径到 build/<example_name>/ 目录中
    set_target_properties(${example_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${example_name}"
    )

    target_compile_definitions(${example_name} PRIVATE DEBUG)
endfunction()

####################################### static libraries #######################################

# 添加一个用户定义库（静态库）
function(add_usrlib lib_name)
    # 找到该库的源文件
    file(GLOB_RECURSE LIB_SOURCES 
        "${CMAKE_SOURCE_DIR}/sources/usrlibs/${lib_name}/*.cc"
#        "${CMAKE_SOURCE_DIR}/sources/usrlibs/${lib_name}/*.cc"
    )

    if(NOT LIB_SOURCES)
        message(FATAL_ERROR "No source files found for user library '${lib_name}'")
    endif()

    # 创建静态库目标
    add_library(${lib_name} STATIC ${LIB_SOURCES})

    # 可选：设置包含目录（让其他 target_link_libraries 时能自动找头文件）
    target_include_directories(${lib_name} PUBLIC "${CMAKE_SOURCE_DIR}/sources/usrlibs/${lib_name}")
endfunction()

add_usrlib(txbridge)
add_usrlib(moncams)
add_usrlib(isl)


# 示例用法：添加多个例子
add_example_debug(farlight)

target_link_libraries(farlight PRIVATE
    txbridge
    moncams
    isl

    OpenGL::GL
    GLEW::GLEW
    SDL2::SDL2
    SDL2_image::SDL2_image
    glm::glm    

)


