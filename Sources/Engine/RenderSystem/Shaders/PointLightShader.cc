//
// Created by phage on 10/24/25.
//

#include "PointLightShader.hh"

NAMESPACE_BEGIN

PointLightShader::PointLightShader(const fs::path& shaderdir) :
Shader( shaderdir )
{
    GLuint vertexShader = GLShader(GL_VERTEX_SHADER, shaderdir / POINTLIGHTVERTEXSHADER).shaderID;
    GLuint fragmentShader = GLShader(GL_FRAGMENT_SHADER, shaderdir / POINTLIGHTFRAGMENTSHADER).shaderID;
    //============================================================
    // Link shaders

    GLuint shaderProgram = glCreateProgram();
    this->shaderID = shaderProgram;
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint cust_errorcode;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &cust_errorcode);

    if (!cust_errorcode) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        ENGINE_ERROR(POINTLIGHT "Shader program linking failed:\n{}\n", infoLog);
        glDeleteProgram(shaderProgram);
    }else{
        ENGINE_INFO(POINTLIGHT "Shader program linked successfully");
    }

//    bindUBO(UBOType::Camera);
}

PointLightShader::~PointLightShader(){
    glDeleteProgram(this->shaderID);
}





NAMESPACE_END