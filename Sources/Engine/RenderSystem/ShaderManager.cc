#include <ShaderManager.hh>


NAMESPACE_BEGIN

/*
TODO: create a camera init method, 
move these steps to dedicate camera init, 
instead of keeping in inside Shader Manager constructor
*/
ShaderManager::ShaderManager(){
    this->uboBindings = vector<GLuint>{};
    uboBindings.push_back(0);
    // Create the UBOs
    glGenBuffers(1, &uboBindings[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, uboBindings[0]);
    glBufferData(GL_UNIFORM_BUFFER, 2* sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    //in-mem camera matrix block bind to binding point 0
    glBindBufferBase(GL_UNIFORM_BUFFER, static_cast<GLuint>(UBOType::Camera), uboBindings[0]);

    // Bind the UBOs to the correct binding points
    ENGINE_INFO("Shader Manager create\nImplicitly create UBO block in memory");
    GLuint err = glGetError();
    if (err == GL_NO_ERROR)
        ENGINE_INFO("No GL error occur");
    while(err != GL_NO_ERROR){
        ENGINE_ERROR("GL error occur! Error code: {}", err);
        err = glGetError();
    }
}

void ShaderManager::bindUBO( Shader* shader, UBOType type){
    GLuint uniformBlockIndex = glGetUniformBlockIndex(shader->getGSP(), UBOCAMERA);
    if(uniformBlockIndex == GL_INVALID_INDEX){
        ENGINE_ERROR("Cannot find uniform block %s in shader\n", UBOCAMERA);
        return;
    }


    if(type == UBOType::Camera){
        glUniformBlockBinding(shader->getGSP(), uniformBlockIndex, static_cast<GLuint>(UBOType::Camera));

        ENGINE_INFO("Shader Manager now binding UBO Camera block to shader\n");
        GLuint err = glGetError();
        if (err == GL_NO_ERROR)
            ENGINE_INFO("No GL error occur");
        while(err != GL_NO_ERROR){
            ENGINE_ERROR("GL error occur! Error code: {}", err);
            err = glGetError();
        }
    }else{
        ENGINE_ERROR("Cannot find ubo name %s\n", UBOCAMERA);
    }
    //up to now shader block is bind to binding point, 
    //but binding point still not connect to ubo in-mem block yet!
    return;
}







NAMESPACE_END