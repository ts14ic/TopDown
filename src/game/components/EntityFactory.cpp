#include "EntityFactory.h"
#include <limits>
#include <cassert>

Entity EntityFactory::create_entity() {
    const std::size_t MINIMUM_FREE_INDICES = 1024;
    const std::size_t GENERATION_ZERO = 0;

    Entity::Index index;
    // If there are not yet enough entities to reuse
    if (_free_indices.size() <= MINIMUM_FREE_INDICES) {
        // create a new entity with generation zero (0)
        _generations.push_back(GENERATION_ZERO);
        // return it's generation index
        index = _generations.size() - 1;

    } else {
        // else if a number of entities can be reused
        // take the oldest entity and pop it
        index = _free_indices.front();
        _free_indices.pop_front();
    }

    return Entity{index, _generations[index]};
}

bool EntityFactory::is_alive(Entity entity) const {
    // If given entity and stored entities generations match, the entity is alive.
    return _generations.size() > entity._index
           && _generations[entity._index] == entity._generation;
}

void EntityFactory::destroy(Entity entity) {
    // To invalidate an entity, increase the generation stored by it's index, also store the index as free for reuse
    auto index = entity._index;
    ++_generations[index];
    _free_indices.push_back(index);
}
