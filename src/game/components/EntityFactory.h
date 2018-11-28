#pragma once

#include <cstdint>
#include <unordered_set>
#include <vector>
#include <deque>

class EntityFactory;

class Entity {
public:
    Entity() = default;

    friend bool operator==(const Entity& left, const Entity& right) {
        return left._index == right._index
               && left._generation == right._generation;
    }

private:
    using Index = std::uint32_t;
    using Generation = std::uint32_t;

    explicit Entity(Index index, Generation generation) : _index{index}, _generation{generation} {
    }

    friend class EntityFactory;

    friend struct std::hash<Entity>;

    Index _index = 0;
    Generation _generation = 0;
};

namespace std {
    template <>
    struct hash<Entity> {
        inline size_t operator()(const Entity& entity) const {
            auto hashed_index = hash<Entity::Index>{}(entity._index);
            auto hashed_generation = hash<Entity::Generation>{}(entity._generation);;
            return hashed_index ^ (hashed_generation << 1);
        }
    };
}

class EntityFactory {
public:
    Entity create_entity();

    bool is_alive(Entity entity) const;

    void destroy(Entity entity);

private:
    std::vector<Entity::Generation> _generations;
    std::deque<Entity::Index> _free_indices;
};
