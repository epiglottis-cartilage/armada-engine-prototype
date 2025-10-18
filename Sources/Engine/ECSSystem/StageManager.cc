#include <StageManager.hh>
#include <RenderSystem.hh>

NAMESPACE_BEGIN

void MeshSystem::tick()
{
    auto view = enttregistry->view<MeshComponent, TransformComponent>();
    for (auto [entity, mesh, transform]: view.each())
    {
        if (mesh.visible)
        {
            this->rendercontext.drawtargets.push_back(
                RenderCommand{mesh.modelptr, mesh.modelptr->getShader(), transform.getTransformMat()}
                );
        }
    }
}

NAMESPACE_END