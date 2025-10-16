#include <PhongShader.hh>

NAMESPACE_BEGIN

using namespace std;

//TODO: move this inner class to base class `shader`
PhongShader::GLShader::GLShader(GLenum shadertype, fs::path shaderfilepath) {
    
    GLchar shaderInfoLog[512];
    GLint success;
    

    string sourceGeneralVertexPath = shaderfilepath.string();
    ifstream file(sourceGeneralVertexPath);

    ENGINE_VALIDLOCATION(shaderfilepath);

    if (!file.is_open()) {
        ENGINE_WARN("Error: failed to open shader file {}\n", sourceGeneralVertexPath);
        //throw std::runtime_error("Shader file cannot be opened");
    }


    string content((istreambuf_iterator<char>(file)), 
        istreambuf_iterator<char>()
    );    

    GLuint vertexShader = glCreateShader(shadertype);
    this->shaderID = vertexShader;

    const char* sourcesShader = content.c_str();
    glShaderSource(vertexShader, 1, &sourcesShader, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, shaderInfoLog);
        ENGINE_ERROR("Phong Shader compilation failed:\n{}\n", shaderInfoLog);
    }
}

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

    bindUBO(UBOType::Camera);
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