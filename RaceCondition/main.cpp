#include "Logger.h"

#include <future>
#include <sstream>
#include <vector>
#include <atomic>
#include <stdlib.h>

struct SharedData {
    std::atomic_int i;
    volatile int i1 = 0;
    volatile int i2 = 0;
    volatile int i3 = 0;
};
std::atomic<bool> ready (false);

void increase(SharedData &sd, int count) {
    while (!ready) { std::this_thread::yield(); }
    LOG1(count)
    for (int j = 0; j < count; ++j) {
        sd.i++;
        sd.i1++;
        sd.i2++;
        sd.i3++;
    }
}

int main() {
    srand(time(0));
    SharedData sd;
    sd.i = 0;

    {
        LOG("before std::thread tr(increase, &sd)");
        int nThreads = 9;
        int countTotal = 0;
        std::vector<std::thread> threads;
        for (int i = 0; i < nThreads; ++i) {
            int count = rand() % 10000;
            LOG1(count)
            countTotal += count;
            threads.emplace_back(increase, std::ref(sd), count);
        }
        ready = true;
//        usleep(1000);
        LOG("before tr.join()")
        for (auto &thread : threads) {
            thread.join();
        }
        LOG1(countTotal);
        LOG1(sd.i);
        LOG1(sd.i1);
        LOG1(sd.i2);
        LOG1(sd.i3);
    }

    LOG("return 0");
    return 0;
}