#ifndef CustShader_hh
#define CustShader_hh
#include <string>
#include <fstream>
#include <iostream>
#include <optional>
#include <GL/glew.h>

using namespace std;

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

















#endif