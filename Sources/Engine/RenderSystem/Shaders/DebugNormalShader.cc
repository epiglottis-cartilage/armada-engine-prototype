//
// Created by phage on 11/3/25.
//

#include "DebugNormalShader.hh"
#include "PhongShader.hh"

NAMESPACE_BEGIN
DebugNormalShader::DebugNormalShader(const fs::path& shaderdir) :
Shader(shaderdir) {
    GLuint vertexShader = GLShader(GL_VERTEX_SHADER, shaderdir / PHONGVERTEXSHADER ).shaderID;
    GLuint geometricShader = GLShader(GL_GEOMETRY_SHADER, shaderdir / Debug_Shader_Name ).shaderID;
    GLuint fragmentShader = GLShader(GL_FRAGMENT_SHADER, shaderdir / Shining_Color_Fragshader_Name).shaderID;
    //============================================================
    // Link shaders

    GLuint shaderProgram = glCreateProgram();
    this->shaderID = shaderProgram;
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, geometricShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint cust_errorcode;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &cust_errorcode);

    if (!cust_errorcode) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        ENGINE_ERROR("Phong Shader program linking failed:\n{}\n", infoLog);
        glDeleteProgram(shaderProgram);
    }else{
        ENGINE_INFO("Phong Shader program linked successfully");
    }

}

string DebugNormalShader::typeName() const {
    return DEBUGNORMALSHADERTYPE;
}


NAMESPACE_END