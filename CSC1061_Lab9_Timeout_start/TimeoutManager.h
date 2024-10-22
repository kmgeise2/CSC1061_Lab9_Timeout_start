#ifndef TIMEOUTMANAGER_H
#define TIMEOUTMANAGER_H

#include <functional>
#include <queue>
#include "TimeoutItem.h"
#include "Clocks.h"

class TimeoutManager {
protected:
    // Priority queue for timeout items. The timeout item with the lowest
    // callback time is the first to be dequeued.
    std::priority_queue<TimeoutItem> pq;

    // Pointer to a clock used to get the current time in the AddTimeout() and
    // Update() functions.
    MillisecondClock* clock;

public:
    TimeoutManager(MillisecondClock* clock) {
        this->clock = clock;
    }

    virtual ~TimeoutManager() {
    }

    // Returns a reference to this timeout manager's internal priority queue.
    // Used only for grading purposes.
    std::priority_queue<TimeoutItem>& GetPriorityQueue() {
        return pq;
    }

    // Adds a timeout item, given a callback function and delay time as
    // parameters. The added timeout expires at:
    // (clock's current time when this function is called) + (delay time)
    virtual void AddTimeout(std::function<void()> callback,
        int delayBeforeCallback) {
        // TODO: Type your code here
    }

    // Dequeues each expired timeout item from the priority queue and calls each
    // expired item's callback function.
    virtual void Update() {
        // TODO: Type your code here
    }
};

#endif
