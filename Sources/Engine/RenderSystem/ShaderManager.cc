#include <ShaderManager.hh>


NAMESPACE_BEGIN

ShaderManager::ShaderManager(){
    this->uboBindings = vector<GLuint>{};
    uboBindings.push_back(0);
    // Create the UBOs
    glGenBuffers(1, &uboBindings[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, uboBindings[0]);
    glBufferData(GL_UNIFORM_BUFFER, 2* sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Bind the UBOs to the correct binding points
}

void ShaderManager::bindUBO(UBOType type, Shader* shader){
    GLuint uniformBlockIndex = glGetUniformBlockIndex(shader->getGSP(), UBOCAMERA);
    if(uniformBlockIndex == GL_INVALID_INDEX){
        ENGINE_ERROR("Cannot find uniform block %s in shader\n", UBOCAMERA);
        return;
    }

    if(type == UBOType::Camera){
        glUniformBlockBinding(shader->getGSP(), uniformBlockIndex, static_cast<GLuint>(UBOType::Camera));
    }else{
        ENGINE_ERROR("Cannot find ubo name %s\n", UBOCAMERA);
        return;
    }
}







NAMESPACE_END