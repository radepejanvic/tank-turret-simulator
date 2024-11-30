#include "turret.h"

const char* Turret::SUCCESS = "Mission Successful!";
const char* Turret::FAIL = "Mission Failed!";
const char* Turret::SIGNATURE = "Rade Pejanovic SV10/2021";

Turret::Turret(float baseV, const char* fontPath): baseV(baseV), currV(baseV), deltaT(0.0), lastT(0.0), ammo(10, 0.6, -0.5, 0.2, 1.0, 0.02), led(0.5, -0.45, 0.1), voltmeter(20, 0.1, -0.6, -0.3, 0.5), panorama(0.0, 0.0, 7.0, 2.0), target(3, 0.05, 7.0, 2.0), timer(30.0), textHandler(fontPath)
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

    currT = glfwGetTime();

    deltaT = currT - lastT;
    lastT = currT;

    timer.update(deltaT);


    std::string timerText = timer.getTimeString();
    glm::vec3 timerColor(0.5, 0.8f, 0.2f);


    if (!target.isEmpty()) {
        if (timer.isFinished()) {
            textHandler.renderText(FAIL, 650.0f, 830.0f, 1.0f, glm::vec3(1.0f, 0.2f, 0.2f));
        }
        else {
            textHandler.renderText(timerText, 750.0f, 830.0f, 1.0f, timerColor);
        }
    }
    else {
        textHandler.renderText(SUCCESS, 620.0f, 830.0f, 1.0f, glm::vec3(0.2f, 1.0f, 0.2f));
    }

    textHandler.renderText(SIGNATURE, 30.0f, 870.0f, 0.3f, glm::vec3(0.2f, 1.0f, 0.2f));

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

bool Turret::isEnd()
{
    return target.isEmpty();
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
