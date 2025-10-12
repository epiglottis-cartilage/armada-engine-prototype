#include <Shader.hh>

NAMESPACE_BEGIN

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

        GLuint uniformBlockIndex = glGetUniformBlockIndex(this->shaderID, UBOCAMERA);
        if(uniformBlockIndex == GL_INVALID_INDEX){
            ENGINE_ERROR("Cannot find uniform block {} in shader\n", UBOCAMERA);
            return;
        }


        if(type == UBOType::Camera){
            glUniformBlockBinding(shaderID, uniformBlockIndex, static_cast<GLuint>(UBOType::Camera));

            ENGINE_INFO("Shader Manager now binding UBO Camera block to shader\n");
            GLuint err = glGetError();
            if (err == GL_NO_ERROR)
                ENGINE_INFO("No GL error occur");
            while(err != GL_NO_ERROR){
                ENGINE_ERROR("GL error occur! Error code: {}", err);
                err = glGetError();
            }
        }else{
            ENGINE_ERROR("Cannot find ubo name {}\n", UBOCAMERA);
        }
        //up to now shader block is bind to binding point, 
        //but binding point still not connect to ubo in-mem block yet!
        return;
}

NAMESPACE_END