//
// Created by phage on 10/18/25.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <Common.hh>

NAMESPACE_BEGIN
class Component {
    public:
        virtual void tick(float deltatime) = 0;


};
NAMESPACE_END


#endif //COMPONENT_H
