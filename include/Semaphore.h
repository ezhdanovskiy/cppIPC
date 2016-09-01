#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0) : count(count) {}

    void notify() {
        std::unique_lock<std::mutex> lock(m);
        count++;
        cv.notify_one();
    }

    void wait() {
        std::unique_lock<std::mutex> lock(m);
        while (count == 0) {
            cv.wait(lock);
        }
        count--;
    }

private:
    std::mutex m;
    std::condition_variable cv;
    int count;
};
