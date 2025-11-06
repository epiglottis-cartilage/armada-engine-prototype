#include <ShaderManager.hh>
#include <Camera.hh>

#include "DebugNormalShader.hh"
#include "Light.hh"
#include "PointLightShader.hh"
#include "RenderSystem.hh"

NAMESPACE_BEGIN
/*
TODO: create a structured camera init method,
move these steps to dedicate camera init,
instead of keeping in inside Shader Manager constructor
*/
extern AppContext* objptrAppContext;

ShaderManager::ShaderManager(){
    auto& uboBindings = objptrAppContext->aRenderContext->uboBindings;
    uboBindings.push_back(0);
    // Create the UBOs
    glGenBuffers(1, &uboBindings[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, uboBindings[0]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraMatrices), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, static_cast<GLuint>(UBOType::Camera), uboBindings[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    uboBindings.push_back(1);
    glGenBuffers(1, &uboBindings[1]);
    glBindBuffer(GL_UNIFORM_BUFFER, uboBindings[1]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightBuffer), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, static_cast<GLuint>(UBOType::LightBuffer), uboBindings[1]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Bind the UBOs to the correct binding points
    ENGINE_INFO("Shader Manager create\nImplicitly create UBO block in memory");
    GLuint err = glGetError();
    if (err == GL_NO_ERROR)
        ENGINE_INFO("No GL error occur");
    while(err != GL_NO_ERROR){
        ENGINE_ERROR("GL error occur! Error code: {}", err);
        err = glGetError();
    }

    
    //should I use such init????????
    ShaderFactory::instance().registerType("Phong", [](const fs::path& shaderdir) { return std::make_unique<PhongShader>(shaderdir); });
    ShaderFactory::instance().registerType("Light", [](const fs::path& shaderdir) { return std::make_unique<PointLightShader>(shaderdir); });
    ShaderFactory::instance().registerType("DebugPhong", [](const fs::path& shaderdir) { return std::make_unique<DebugNormalShader>(shaderdir); });

    //examples::
//    ShaderFactory::instance().registerType("PBR", [] { return std::make_unique<PBRShader>(); });
//    ShaderFactory::instance().registerType("Skybox", [] { return std::make_unique<SkyboxShader>(); });

}


NAMESPACE_END