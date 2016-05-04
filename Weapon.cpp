#include "GameObject.h"

Pistol::Pistol()
{
    _cd.start();
}

int   Pistol::dmg()    const { return 15; }
float Pistol::speed()  const { return 18.f; }
int   Pistol::length() const { return 10; }
float Pistol::spread() const { return 2; }

void Pistol::shoot(Object const& sender) {
    if(_cd.passed(300)) {
        Bullet b(sender, *this);
        bullets().push_back(b);
        _cd.start();
    }
}
