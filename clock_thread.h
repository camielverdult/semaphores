//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_CLOCK_THREAD_H
#define SEMAPHORES_CLOCK_THREAD_H

#include "rollercoaster_context.hpp"

_Noreturn void* clock_thread(void* _);

void clock_start(context* ctx);
void clock_stop(context* ctx);

#endif //SEMAPHORES_CLOCK_THREAD_H