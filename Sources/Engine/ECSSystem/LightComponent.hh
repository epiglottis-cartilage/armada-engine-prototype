//
// Created by phage on 10/25/25.
//

#ifndef LIGHTCOMPONENT_HH
#define LIGHTCOMPONENT_HH

#include <Common.hh>
#include <Component.h>
#include <Shader.hh>
#include <Model.hh>
#include <Light.hh>
#include <entt/entt.hpp>

NAMESPACE_BEGIN


class LightComponent : public Component {
public:
    using allocator_type = void;
    LightComponent() = delete;
    //this constructor is for directional light
//    LightComponent(Shader* shader, const typeLight type, const glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}, const float intensity = 1.0f);
    //this constructor is for point light
    LightComponent(Shader* shader, const typeLight type, const glm::vec4 color = glm::vec4{1.0f, 1.0f, 1.0f, 1.0f}, const float intensity = 1.0f, const float range = 10.0f);
    ~LightComponent();

    bool visible = true;
    //this flag is for updating the ubo shared memory, not for the transform!
    bool isdirty = true;
    gpuLightStruct properties;
    Shader* ptrShader;
    int lightindex = 0;

    void tick(float dt);
    void setColor(const glm::vec4 rgbaColor);
    void setIntensity(float intensity);
    void setRange(float range);
    void setShader(Shader* newshader);
private:
    const typeLight lighttype;
};

NAMESPACE_END

#endif //LIGHTCOMPONENT_HH
