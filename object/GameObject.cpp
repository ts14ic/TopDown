#include "GameObject.h"

bool objectsCollide(GameObject& a, GameObject& b) {
    return ::collides(a.circle(), b.circle());
}