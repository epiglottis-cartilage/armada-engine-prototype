#include <StageManager.hh>

NAMESPACE_BEGIN

StateManager::StateManager()
{
    this->entities = std::unordered_map<EntityId, shared_ptr<Entity>>();

}

StateManager::~StateManager()
{
    this->entities.clear();
}


void StateManager::addEntity(shared_ptr<Entity> entity){
    this->entities.emplace(entity->getId(), entity);
}

void StateManager::removeEntity(EntityId id){
    this->entities.erase(id);
}


NAMESPACE_END