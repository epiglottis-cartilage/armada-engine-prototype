#pragma once

#include <Common.hh>

#include "OpenglShader.hh"
#include <GL/glew.h>
#include <filesystem>

NAMESPACE_BEGIN


enum class ShaderType{
    General = 0,
    PBR = 1,
};


/*
represent the compiled shader program inside memory. 
pass a vertex location and a fragment location to assmbly a Shader
original shader memory will be free if assmbly successful
*/
class Shader {


public:
    Shader(std::string sourceGeneralVertexPath, std::string sourceGeneralFragmentPath);
    Shader(std::filesystem::path sourceGeneralVertexPath, std::filesystem::path sourceGeneralFragmentPath);

    ~Shader(){
        glDeleteShader(generalShader);
    }   
    GLuint getGSP() const { return generalShader; }

private:
    GLuint generalShader;
    ShaderType shaderType = ShaderType::General;
};



NAMESPACE_END
