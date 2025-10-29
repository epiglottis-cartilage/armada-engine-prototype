//
// Created by phage on 10/21/25.
//

#ifndef NAMECOMPONENT_HH
#define NAMECOMPONENT_HH

#include <Common.hh>
#include <Component.h>
#include <rttr/registration>

NAMESPACE_BEGIN

class NameComponent :
Component {
public:
    NameComponent(string name) : name(name) {}
    NameComponent() = default;
    string getName() const { return name; }
    void setName(string newname) { this->name = newname; }
    void tick(float deltatime) override;

    string name;
};


NAMESPACE_END
#endif //NAMECOMPONENT_HH
