//
// Currently when lightnum changes, update to ubo buffer is immediately.
// Should have a better way to defered the update.......

#include "LightComponent.hh"
#include <GlobalContext.hh>
#include <Engine.hh>
#include <rttr/registration>

NAMESPACE_BEGIN

extern Engine* objptrGameEngine;
extern AppContext* objptrAppContext;

LightComponent::~LightComponent() {
    auto* lightsystem = objptrGameEngine->getLightSystem();
    auto& lightnumber = lightsystem->lightnums;
    lightnumber--;
    lightsystem->numsdirty = true;

    ENGINE_INFO("Deleting a light (index {}), current light number: {}(include this one)", this->lightindex, lightnumber);
}

LightComponent::LightComponent(Shader* shader, const typeLight type, const glm::vec4 color , const float intensity, const float range ):
    Component(), //base
    properties(gpuLightStruct{ type, glm::vec3{0.0f}, color, intensity, range
    }),
    ptrShader(shader),
    lighttype(type) {
    auto* lightsystem = objptrGameEngine->getLightSystem();
    auto& lightnumber = lightsystem->lightnums;
    this->lightindex = lightnumber;
    lightnumber++;
    lightsystem->numsdirty = true;
    ENGINE_INFO("Creating a new light, current light number: {}(include this one)", lightnumber);
}


void LightComponent::setIntensity(float intensity) {
    this->isdirty = true;
    this->properties.intensity = intensity;
    //update shader (try)
//    auto* shaderptr = this->ptrShader;
//    glUseProgram(shaderptr->getID());
//    shaderptr->setUniform(FLINTENSITY, intensity);
//    ENGINE_INFO("light intensity set");
//    glUseProgram(0);
}
float LightComponent::getIntensity() {
    return this->properties.intensity;
}

void LightComponent::tick(float dt) {
    //update the instance's data to the ubo shared memory
    int uboindex = static_cast<int>(UBOType::LightBuffer);

    glBindBuffer(
        GL_UNIFORM_BUFFER, 
        objptrAppContext->aRenderContext->uboBindings[uboindex]
    );
    glBufferSubData(
        GL_UNIFORM_BUFFER, 
        16+this->lightindex * sizeof(gpuLightStruct), 
        sizeof(gpuLightStruct), 
        &this->properties
    );

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    RenderSystem::errorposition(__FILE__, __LINE__);
}


void LightComponent::setColor(const glm::vec4 rgbaColor) {
    this->isdirty = true;

    this->properties.color = rgbaColor;
    //update shader (try)
    auto* shaderptr = this->ptrShader;
    //哥们这下面几行没p用的，你在写什么
//    glUseProgram(shaderptr->getID());
//    shaderptr->setUniform(COLORLIGHT, rgbaColor);
//    ENGINE_INFO("light color set");
//    glUseProgram(0);
}
glm::vec4 LightComponent::getColor() {
    return this->properties.color;
}


void LightComponent::setRange(float range) {
    this->isdirty = true;
    this->properties.range = range;
}
float LightComponent::getRange() {
    return this->properties.range;
}

void LightComponent::setShader(Shader* newshader) {
    this->isdirty = true;
    this->ptrShader = newshader;
}
Shader* LightComponent::getShader() {
    return this->ptrShader;
}

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<LightComponent>("LightComponent")
        // 注册构造函数
        .constructor<Shader*, typeLight, glm::vec4, float, float>()

        // 注册字段
        .property("color", &LightComponent::getColor, &LightComponent::setColor)
        .property("intensity",  &LightComponent::getIntensity, &LightComponent::setIntensity)
        .property("range",      &LightComponent::getRange,    &LightComponent::setRange)
        ;
}
NAMESPACE_END