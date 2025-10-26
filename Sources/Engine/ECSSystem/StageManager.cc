#include <StageManager.hh>
#include <RenderSystem.hh>
#include <glm/glm.hpp>

NAMESPACE_BEGIN

void TransformSystem::tick(float deltatime) {
    auto view = enttregistry->view<TransformComponent>();
    for (auto [entity, transform]: view.each()) {

        if (transform.isdirty) {
            transform.isdirty = !transform.isdirty;

            transform.tick(deltatime);
            if (enttregistry->any_of<LightComponent>(entity)) {
                auto& light = enttregistry->get<LightComponent>(entity);

                light.properties.position = glm::vec4{transform.getPosition(), 1.0f};
                light.properties.direction = glm::vec4{transform.getRotation(), 0.0f};
                light.isdirty = true;
            }
        }
    }
}


void MeshSystem::tick(float deltatime)
{
    auto view = enttregistry->view<MeshComponent, TransformComponent>();
    for (auto [entity, mesh, transform]: view.each())
    {
        if (mesh.visible)
        {
            this->rendercontext->drawtargets.push_back(
                RenderCommand{mesh.modelptr, mesh.modelptr->getShader(), transform.getTransformMat()}
                    );
        }
    }
}

MeshSystem::MeshSystem(RenderContext& rendercontext, StateManager& stateManager):
    enttregistry(&stateManager),
    rendercontext(&rendercontext)
{}

void LightSystem::init() {

}


void LightSystem::tick(float deltatime) {
    //update light nums count on ubo
    if (numsdirty) {
        glBindBuffer(GL_UNIFORM_BUFFER, objptrAppContext->aRenderContext->uboBindings[static_cast<int>(UBOType::LightBuffer)]);
        //buffer current light num
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(int), &lightnums);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    auto view = enttregistry->view<LightComponent>();
    for (auto [entity, light]: view.each()) {
        if (light.isdirty)
            light.isdirty = !light.isdirty;
            light.tick(deltatime);
    }
}





NAMESPACE_END