//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_BARON_HPP
#define SEMAPHORES_BARON_HPP

#include <thread>
#include "queue.hpp"
#include "clock_thread.h"

class baron {
public:

    baron() {
        _clock_thread = std::thread(clock_thread);
    }

private:
    std::thread _clock_thread;
    std::thread _single_rider_thread;
    std::thread _row_grabber_thread;

    queue _first_queue;
};

#endif //SEMAPHORES_BARON_HPP
