//
// Created by phage on 10/21/25.
//

#include "NameComponent.hh"

NAMESPACE_BEGIN

void NameComponent::tick(float deltatime)
{
}

//rttr registry
RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<NameComponent>("NameComponent")
        // 注册构造函数
        .constructor<>()
        .constructor<string>()

        // 注册字段
        .property("name", &NameComponent::getName, &NameComponent::setName)
        ;
}

NAMESPACE_END
