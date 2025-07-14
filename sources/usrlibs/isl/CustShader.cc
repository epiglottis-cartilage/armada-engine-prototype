#include "CustShader.hh"

using namespace std;

CustShader::CustShader(GLenum shadertype, string sourceGeneralVertexPath){
    
    GLchar shaderInfoLog[512];
    GLint success;
    
    ifstream file(sourceGeneralVertexPath);
    string content((istreambuf_iterator<char>(file)), 
        istreambuf_iterator<char>()
    );    

    generalShader = glCreateShader(shadertype);

    const char* sourcesShader = content.c_str();
    glShaderSource(generalShader, 1, &sourcesShader, NULL);
    glCompileShader(generalShader);

    glGetShaderiv(generalShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(generalShader, 512, NULL, shaderInfoLog);
        std::cerr << "Shader compilation failed:\n" << shaderInfoLog << std::endl;
    }
};
optional<GLuint> CustShader::shaderLink(CustShader vertexShader, CustShader fragmentShader){
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.generalShader);
    glAttachShader(shaderProgram, fragmentShader.generalShader);
    glLinkProgram(shaderProgram);

    GLint cust_errorcode;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &cust_errorcode);

    if (!cust_errorcode) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        glDeleteProgram(shaderProgram);
        return {};
    }
    return {shaderProgram};
}








