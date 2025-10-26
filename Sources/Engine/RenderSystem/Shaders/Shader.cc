#include <Shader.hh>
#include <fstream>

NAMESPACE_BEGIN


Shader::GLShader::GLShader(GLenum shadertype, fs::path shaderfilepath) {

    using namespace std;
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

Shader::Shader(const fs::path& shaderdir) {
    this->shaderID = 0;
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) const {
    GLint location = glGetUniformLocation(this->shaderID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const {
    GLint location = glGetUniformLocation(this->shaderID, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);

}

void Shader::setUniform(const std::string& name, float value) const {
    GLint location = glGetUniformLocation(this->shaderID, name.c_str());
    glUniform1f(location, value);
}

void Shader::bindUBO(UBOType type){
        //I guess situation will get better after I master deferred lighting

        GLuint uniformBlockIndex;
        GLuint err;

        switch (type) {
        case UBOType::Camera:
            uniformBlockIndex    = glGetUniformBlockIndex(this->shaderID, UBOCAMERA);
            if(uniformBlockIndex == GL_INVALID_INDEX){
                ENGINE_ERROR("Cannot find uniform block {} in shader\n", UBOCAMERA);
                return;
            }
            glUniformBlockBinding(shaderID, uniformBlockIndex, static_cast<GLuint>(UBOType::Camera));

            ENGINE_INFO("Shader Manager now binding UBO Camera block to shader\n");
            err = glGetError();
            if (err == GL_NO_ERROR)
                ENGINE_INFO("No GL error occur");
            while(err != GL_NO_ERROR){
                ENGINE_ERROR("GL error occur! Error code: {}", err);
                err = glGetError();
            }
            break;
        case UBOType::LightBuffer:
            uniformBlockIndex = glGetUniformBlockIndex(this->shaderID, UBOLIGHTBUFFER);
            if(uniformBlockIndex == GL_INVALID_INDEX){
                ENGINE_ERROR("Cannot find uniform block {} in shader\n", UBOCAMERA);
                return;
            }
            glUniformBlockBinding(shaderID, uniformBlockIndex, static_cast<GLuint>(UBOType::LightBuffer));
            ENGINE_INFO("Shader Manager now binding UBO LightBuffer block to shader\n");
            err = glGetError();
            if (err == GL_NO_ERROR)
                ENGINE_INFO("No GL error occur");
            while(err != GL_NO_ERROR){
                ENGINE_ERROR("GL error occur! Error code: {}", err);
                err = glGetError();
            }
            break;
        default:
            ENGINE_ERROR("Cannot find ubo name , for ubo type: {}\n", static_cast<int>(type));
            break;
        }
        //up to now shader block is bind to binding point,
        //but binding point still not connect to ubo in-mem block yet!
}

NAMESPACE_END