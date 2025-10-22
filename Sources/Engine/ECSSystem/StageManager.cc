#include <StageManager.hh>
#include <RenderSystem.hh>

NAMESPACE_BEGIN

void MeshSystem::tick(float deltatime)
{
    auto view = enttregistry->view<MeshComponent, TransformComponent>();
    for (auto [entity, mesh, transform]: view.each())
    {
        transform.tick(deltatime);
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
{
}


NAMESPACE_END