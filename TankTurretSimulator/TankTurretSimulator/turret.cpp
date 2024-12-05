#include "turret.h"

Turret::Turret(float baseV, const char* fontPath, const char* textPath): baseV(baseV), currV(baseV), deltaT(0.0), lastT(0.0), ammo(10, 0.75, -0.95, 0.2, 1.0, 0.02), led(0.65, -0.87, 0.1), voltmeter(20, 0.1, -0.8, -0.7, 0.3), panorama(0.0, 0.0, 7.0, 2.0), target(3, 0.05, 7.0, 2.0), timer(30.0), textHandler(fontPath), visor(0.2)
{
    loadText(textPath);
}

void Turret::fire(float mouseX, float mouseY)
{
    if (!led.getIsOn() || ammo.isEmpty()) return;

    ammo.fire();
    float* coords = visor.getGunCoords();
    target.tryShoot(*coords, *(coords+1));
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
        visor.draw(currV/5);
    } 
    ammo.draw();
    led.draw();
    voltmeter.draw();

    currT = glfwGetTime();

    deltaT = currT - lastT;
    lastT = currT;

    timer.update(deltaT);

    glm::vec3 timerColor(0.5, 0.8f, 0.2f);

    if (!target.isEmpty()) {
        if (timer.isFinished()) {
            textHandler.renderText(lines[2], 650.0f, 830.0f, 1.0f, glm::vec3(1.0f, 0.2f, 0.2f));
        }
        else {
            textHandler.renderText(convertStringToWString(timer.getTimeString()), 750.0f, 830.0f, 1.0f, timerColor);
        }
    }
    else {
        textHandler.renderText(lines[1], 620.0f, 830.0f, 1.0f, glm::vec3(0.2f, 1.0f, 0.2f));
    }

    textHandler.renderText(lines[0], 30.0f, 870.0f, 0.3f, glm::vec3(0.2f, 1.0f, 0.2f));
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

void Turret::moveAim(float mouseX, float mouseY) {
    visor.moveAim(mouseX, mouseY);
}

void Turret::loadText(const char* path)
{
    std::ifstream file(path);

    if (!file) {
        std::cerr << "TURRET::ERROR: Opening file: " << path << std::endl;
        return;
    }

    std::string utf8Line;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    while (std::getline(file, utf8Line)) {
        try {
            std::wstring wideLine = converter.from_bytes(utf8Line);
            lines.push_back(wideLine);
        }
        catch (const std::exception& e) {
            std::cerr << "TURRET::ERROR: Converting line to wide string: " << e.what() << std::endl;
        }
    }

    file.close();
}
