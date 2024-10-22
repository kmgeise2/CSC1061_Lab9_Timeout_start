#ifndef CLOCK_H
#define CLOCK_H

class MillisecondClock {
public:
    virtual ~MillisecondClock() {
    }

    // Returns an integer representing the clock's current time, in milliseconds
    virtual int GetTime() = 0;
};

// TestClock implements a clock that stores a time set by code external to the
// class.
class TestClock : public MillisecondClock {
private:
    int currentTime;

public:
    TestClock() {
        currentTime = 0;
    }

    virtual int GetTime() override {
        return currentTime;
    }

    // Sets this clock's current time, provided the new time is greater than the
    // previously set time.
    virtual bool SetTime(int newTime) {
        // Only allow time to move forward
        if (newTime > currentTime) {
            currentTime = newTime;
            return true;
        }
        return false;
    }
};

#endif
