#include <UIDrawSystem.hh>
#include <GlobalContext.hh>
#include <Engine.hh>
#include <SDL2/SDL.h>

NAMESPACE_BEGIN
extern AppContext* objptrAppContext;
extern Engine* objptrGameEngine;

void UIDrawSystem::drawframe()
{
    ImGui::Begin("ECS Editor");
    ImGui::Text("Press F10 to switch to editor");
    ImGui::Text("Press F19 to hide editor");
    ImGui::Separator();

    StateManager* stateManager = objptrGameEngine->getStateManager();

    auto view = stateManager->view<TransformComponent>();
    rttr::type transform_type = rttr::type::get<TransformComponent>();
    // 提前获取字段的反射信息（避免循环中重复查找）
    rttr::property pos_prop = transform_type.get_property("position");
    rttr::property rot_prop = transform_type.get_property("rotation");
    rttr::property scale_prop = transform_type.get_property("scale");

    for(auto entity : view)
    {
        string label;
        if (stateManager->all_of<NameComponent>(entity)){
            auto& nameComp = stateManager->get<NameComponent>(entity);
            label = nameComp.name;
        }else{
            label = "Entity " + std::to_string(static_cast<uint32_t>(entt::to_integral(entity)));
        }


        if (ImGui::TreeNode(label.c_str()))
        {
            ImGui::Text("Transform");
            ImGui::PushID(static_cast<int>(entt::to_integral(entity)));

            // 获取组件实例
            auto& transform = stateManager->get<TransformComponent>(entity);
            // 将实例包装为RTTR可操作的对象
            rttr::instance transform_instance(transform);

            // 1. 处理Position（通过getter/setter）
            if (pos_prop.is_valid())
            {
                // 调用getter获取当前值
                glm::vec3 pos = pos_prop.get_value(transform_instance).get_value<glm::vec3>();
                glm::vec3 new_pos = pos;

                // 显示ImGui控件并修改new_pos
                if (ImGui::DragFloat3("Position", &new_pos.x, 0.1f))
                {
                    // 调用setter设置新值
                    pos_prop.set_value(transform_instance, new_pos);
                }
            }

            // 2. 处理Rotation（同上）
            if (rot_prop.is_valid())
            {
                glm::vec3 rot = rot_prop.get_value(transform_instance).get_value<glm::vec3>();
                glm::vec3 new_rot = rot;
                if (ImGui::DragFloat3("Rotation", &new_rot.x, 0.1f))
                {
                    rot_prop.set_value(transform_instance, new_rot);
                }
            }

            // 3. 处理Scale（同上）
            if (scale_prop.is_valid())
            {
                glm::vec3 scale = scale_prop.get_value(transform_instance).get_value<glm::vec3>();
                glm::vec3 new_scale = scale;
                if (ImGui::DragFloat3("Scale", &new_scale.x, 0.1f))
                {
                    scale_prop.set_value(transform_instance, new_scale);
                }
            }

            ImGui::PopID();
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

UIDrawSystem::UIDrawSystem()
{
    SDL_Window* window = objptrAppContext->aRenderContext->mainwindow;
    SDL_GLContext glcontext = objptrAppContext->aRenderContext->glcontext;
    this->init(window,  glcontext);
}

void UIDrawSystem::init(SDL_Window* window, SDL_GLContext glcontext)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, glcontext);
    ImGui_ImplOpenGL3_Init("#version 330");

    //register editor hide/switch_to subscriber
    auto* eventmanager = objptrGameEngine->getEventManager();
    eventmanager->subscribe(EventType::KeyPressed, [](const Event& e)
    {
        auto& ev = static_cast<const KeyPressedEvent&>(e);
        if (ev.key == SDLK_F10)
            objptrAppContext->aEditorMode = !objptrAppContext->aEditorMode;
            objptrAppContext->switchEditorMode();
        if (ev.key == SDLK_F9)
            objptrAppContext->aShowEditor = !objptrAppContext->aShowEditor;
    });

}

void UIDrawSystem::quit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void UIDrawSystem::prerender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}


void UIDrawSystem::postrender()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


NAMESPACE_END