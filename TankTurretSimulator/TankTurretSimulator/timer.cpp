#include "Timer.h"
#include <sstream> 

Timer::Timer(float duration) : startTime(duration), elapsedTime(0.0f), isComplete(false) {
    remainingTime = startTime; 
}

void Timer::update(float deltaTime) {
    if (!isComplete) {
        remainingTime -= deltaTime; 
        if (remainingTime <= 0.0f) {
            remainingTime = 0.0f;
            isComplete = true;
        }
    }
}

std::string Timer::getTimeString() {
    int minutes = static_cast<int>(remainingTime) / 60;
    int seconds = static_cast<int>(remainingTime) % 60;

    std::stringstream ss;
    ss << (minutes < 10 ? "0" : "") << minutes << ":"
        << (seconds < 10 ? "0" : "") << seconds;
    return ss.str();
}

bool Timer::isFinished() {
    return isComplete;
}

void Timer::reset() {
    remainingTime = startTime;
    isComplete = false;
}
