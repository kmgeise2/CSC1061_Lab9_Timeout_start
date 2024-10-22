#ifndef TIMEOUTITEM_H
#define TIMEOUTITEM_H

#include <functional>

class TimeoutItem {
private:
    int callbackTime;
    std::function<void()> callbackFunction;

public:
    TimeoutItem(std::function<void()> callbackFunction, int callbackTime) {
        this->callbackTime = callbackTime;
        this->callbackFunction = callbackFunction;
    }

    TimeoutItem(const TimeoutItem& toCopy) : callbackTime(toCopy.callbackTime) {
        callbackFunction = toCopy.callbackFunction;
    }

    virtual ~TimeoutItem() {
    }

    virtual void CallCallback() {
        callbackFunction();
    }

    int GetCallbackTime() const {
        return callbackTime;
    }

    bool operator<(const TimeoutItem& rhs) const {
        // C++'s priority_queue keeps item with maximum value at the front. So to
        // prioritize lower times, the > operator is used below.
        return callbackTime > rhs.callbackTime;
    }

    bool operator<=(const TimeoutItem& rhs) const {
        return callbackTime >= rhs.callbackTime;
    }

    bool operator>(const TimeoutItem& rhs) const {
        return callbackTime < rhs.callbackTime;
    }

    bool operator>=(const TimeoutItem& rhs) const {
        return callbackTime <= rhs.callbackTime;
    }
};

#endif