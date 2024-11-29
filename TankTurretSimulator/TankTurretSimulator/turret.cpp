#include "turret.h"

Turret::Turret(float baseV): baseV(baseV), currV(baseV), ammo(10, 0.6, -0.5, 0.2, 1.0, 0.02), led(0.5, -0.45, 0.1), voltmeter(20, 0.1, -0.6, -0.3, 0.5), panorama(0.0, 0.0, 7.0, 2.0), target(3, 0.05, 7.0, 2.0)
{
}

void Turret::fire(float mouseX, float mouseY)
{
    if (!led.getIsOn() || ammo.isEmpty()) return;

    ammo.fire();
    target.tryShoot(mouseX, mouseY);
    led.toggle();

    std::thread timer([this]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(7500));
        this->led.toggle();
    });

    timer.detach();
}

void Turret::draw(bool isEnterier)
{
    if (!isEnterier) {
        panorama.draw(); 
        target.draw();
    } 
    ammo.draw();
    led.draw();
    voltmeter.draw();
}

void Turret::increaseV()
{   
    voltmeter.increase(); 
    currV = 10 * baseV * voltmeter.getRatio();
}

void Turret::decreaseV()
{
    voltmeter.decrease();
    currV = 10 * baseV * voltmeter.getRatio();

}

void Turret::moveRight()
{
    panorama.moveRight(currV);
    target.moveRight(currV);
}

void Turret::moveLeft()
{
    panorama.moveLeft(currV);
    target.moveLeft(currV);
}