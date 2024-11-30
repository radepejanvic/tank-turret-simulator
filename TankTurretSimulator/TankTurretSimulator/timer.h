#ifndef TIMER_H
#define TIMER_H

#include <string>

class Timer {
private:
    float startTime;      
    float elapsedTime;     
    float remainingTime;   
    bool isComplete;       

public:
    Timer(float duration = 60.0f);
    void update(float deltaTime);
    std::string getTimeString();
    bool isFinished();
    void reset();
};

#endif // TIMER_H
