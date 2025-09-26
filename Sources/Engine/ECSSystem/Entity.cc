#include <Entity.hh>

NAMESPACE_BEGIN


EntityId Entity::nextId = 0;


Entity::~Entity(){
    model = nullptr;
}



NAMESPACE_END