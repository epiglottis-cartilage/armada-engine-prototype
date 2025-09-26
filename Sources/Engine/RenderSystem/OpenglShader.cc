#include <OpenglShader.hh>

using namespace std;

CustShader::CustShader(GLenum shadertype, string sourceGeneralVertexPath){
    
    GLchar shaderInfoLog[512];
    GLint success;
    

    ifstream file(sourceGeneralVertexPath);

    if (!file.is_open()) {
        ENGINE_WARN("Error: failed to open shader file %s\n", sourceGeneralVertexPath);
        //throw std::runtime_error("Shader file cannot be opened");
    }


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
        ENGINE_ERROR("Shader compilation failed:\n%s\n", shaderInfoLog);
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
        ENGINE_ERROR("Shader program linking failed:\n%s\n", infoLog);
        glDeleteProgram(shaderProgram);
        return {};
    }
    return {shaderProgram};
}








