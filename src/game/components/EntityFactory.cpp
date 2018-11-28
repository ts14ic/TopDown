#include "EntityFactory.h"
#include <limits>
#include <cassert>

Entity EntityFactory::create_entity() {
    assert(_id_counter < std::numeric_limits<Entity::Id>::max() && "Entity pool exhausted");

    auto entity = Entity{_id_counter};
    ++_id_counter;
    return entity;
}
