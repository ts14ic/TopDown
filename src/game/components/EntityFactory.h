#pragma once

#include <cstdint>
#include <unordered_set>

class EntityFactory;

class Entity {
public:
    Entity() = default;

    friend bool operator==(const Entity& left, const Entity& right) {
        return left._id == right._id;
    }

private:
    using Id = std::int32_t;

    explicit Entity(Id id) : _id{id} {
    }

    friend class EntityFactory;

    friend struct std::hash<Entity>;

    Id _id = 0;
};

namespace std {
    template <>
    struct hash<Entity> {
        inline size_t operator()(const Entity& entity) const {
            hash<Entity::Id> hasher{};
            return hasher(entity._id);
        }
    };
}

class EntityFactory {
public:
    Entity create_entity();

private:
    Entity::Id _id_counter;
};
