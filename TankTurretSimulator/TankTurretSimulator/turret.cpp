#include "turret.h"

Turret::Turret(): ammo(10, 0.6, -0.5, 0.2, 1.0, 0.02), led(0.5, -0.45, 0.1), voltmeter(20, 1, -0.6, -0.3, 0.5)
{
}

void Turret::fire()
{
    if (!led.getIsOn() || ammo.isEmpty()) return;

    ammo.fire();
    led.toggle();

    std::thread timer([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(7500));
        this->led.toggle();
    });

    timer.detach();
}

void Turret::draw()
{
    ammo.draw();
    led.draw();
    voltmeter.draw();
}
