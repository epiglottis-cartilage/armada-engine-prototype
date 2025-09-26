#pragma once

#include <Common.hh>

#include <fstream>
#include <iostream>
#include <optional>
#include <GL/glew.h>
#include <filesystem>
#include <Logger.hh>


NAMESPACE_BEGIN

using namespace std;

/*when using delete keyword, it will implicitly call gl remove this shader from memory.
So to maximum the performance, please allocate this class on heap using new*/
class CustShader {
public:
    CustShader(GLenum shadertype, string sourceGeneralVertexPath);

    ~CustShader(){
        glDeleteShader(generalShader);
    }

    static optional<GLuint> shaderLink(CustShader vertexShader, CustShader fragmentShader);

private:
    GLuint generalShader;
};
















NAMESPACE_END
