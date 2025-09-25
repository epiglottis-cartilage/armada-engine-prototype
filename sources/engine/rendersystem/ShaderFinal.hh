#ifndef SPCUST_HH
#define SPCUST_HH

#include "CustShader.hh"
#include <GL/glew.h>
#include <filesystem>

/*
represent the compiled shader program inside memory. 
pass a vertex location and a fragment location to assmbly a ShaderFinal
original shader memory will be free if assmbly successful
*/
class ShaderFinal {


public:
    ShaderFinal(std::string sourceGeneralVertexPath, std::string sourceGeneralFragmentPath);
    ShaderFinal(std::filesystem::path sourceGeneralVertexPath, std::filesystem::path sourceGeneralFragmentPath);

    ~ShaderFinal(){
        glDeleteShader(generalShader);
    }   
    GLuint getGSP() const { return generalShader; }

private:
    GLuint generalShader;

};




#endif