//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_CLOCK_THREAD_HPP
#define SEMAPHORES_CLOCK_THREAD_HPP

#include <thread>
#include <chrono>
#include <random>
#include <semaphore>
#include <random>
#include "queue.hpp"
#include "mach/mach.h" // cross-platform semaphore class

semaphore_t clock_sema;
queue first_queue;

_Noreturn void fill_first_queue() {
    // This generates a uniform distribution of groups being either 2 or 3 people big
    std::random_device dev_group_size;
    std::mt19937 rng_group_size(dev_group_size());
    std::uniform_int_distribution<std::mt19937::result_type> dist2(2,3);

    // This generates group amount
    std::random_device dev_group_amount;
    std::mt19937 rng_group_amount(dev_group_amount());
    std::uniform_int_distribution<std::mt19937::result_type> dist5(1, 5);

    // Make queues
    first_queue.queue_number = 1;

    // Initialize semaphore
    semaphore_create(mach_task_self(), &clock_sema, SYNC_POLICY_FIFO, 0);

    std::cout << "CLK: hello!\n";
    while (true) {

        // We fill the queue here;
        for (int group_amount = 0; group_amount < dist5(rng_group_amount); group_amount++) {
            group random_group = {.group_number = group_amount + 1, .size = dist2(rng_group_size)};
            first_queue.groups.push_back(random_group);
        }

        // Wait for people to fill the queue
        std::this_thread::sleep_for(std::chrono::seconds (1));

        // Signal other thread that queue is full and wait until other thread empties queue
        std::cout << "CLK: signaling semaphore\n";

        semaphore_signal(clock_sema);
        semaphore_wait(clock_sema);
    }
}

#endif //SEMAPHORES_CLOCK_THREAD_HPP