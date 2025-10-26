#include <PhongShader.hh>

NAMESPACE_BEGIN

PhongShader::PhongShader(const fs::path& shaderdir) :
Shader(shaderdir)
{
    GLuint vertexShader = GLShader(GL_VERTEX_SHADER, shaderdir / PHONGVERTEXSHADER).shaderID;
    GLuint fragmentShader = GLShader(GL_FRAGMENT_SHADER, shaderdir / PHONGFRAGMENTSHADER).shaderID;
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
        ENGINE_ERROR("Phong Shader program linking failed:\n{}\n", infoLog);
        glDeleteProgram(shaderProgram);
    }else{
        ENGINE_INFO("Phong Shader program linked successfully");
    }

//    bindUBO(UBOType::Camera);
//    bindUBO(UBOType::LightBuffer);
}

PhongShader::~PhongShader() {
    glDeleteProgram(this->shaderID);
}

void PhongShader::setUniform(const std::string& name, const glm::mat4& value) const {
    Shader::setUniform(name, value);
}


void PhongShader::setUniform(const std::string& name, const glm::vec3& value) const {
//    GLint location = glGetUniformLocation(this->shaderID, name.c_str());
//    glUniform3f(location, value.x, value.y, value.z);
    Shader::setUniform(name, value);
}

void PhongShader::setUniform(const std::string& name, float value) const {
//    GLint location = glGetUniformLocation(this->shaderID, name.c_str());
//    glUniform1f(location, value);
    Shader::setUniform(name, value);
}

NAMESPACE_END