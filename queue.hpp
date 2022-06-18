//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_QUEUE_HPP
#define SEMAPHORES_QUEUE_HPP

#include <thread>
#include <chrono>
#include <random>
#include <semaphore>
#include <random>
#include <iostream>
#include <queue>
#include "sema.h" // cross-platform semaphore class

typedef struct group {
    int group_number;
    unsigned int size;
} group_t;

// Semaphore and queue for first queue
Semaphore first_queue_sema;
std::queue<group> first_queue;

// Semaphore and queue for second queue
Semaphore single_queue_sema;
std::queue<group> single_queue;

_Noreturn void fill_first_queue() {
    // This generates a uniform distribution of groups being either 2 or 3 people big
    std::random_device dev_group_size;
    std::mt19937 rng_group_size(dev_group_size());
    std::uniform_int_distribution<std::mt19937::result_type> dist2(2,3);

    // This generates group amount
    std::random_device dev_group_amount;
    std::mt19937 rng_group_amount(dev_group_amount());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(1, 10);

    std::cout << "FILL_1: hello!\n";
    while (true) {

        // We fill the queue here;
        for (int group_amount = 0; group_amount < dist10(rng_group_amount); group_amount++) {
            group random_group = {.group_number = group_amount + 1, .size = dist2(rng_group_size)};
            first_queue.push(random_group);
        }

        // Wait for people to fill the queue
        std::this_thread::sleep_for(std::chrono::seconds (1));

        // Signal other thread that queue is full
        std::cout << "FILL_1: signaling semaphore\n";
        first_queue_sema.signal();

        // Wait until other thread empties queue
        std::cout << "FILL_1: waiting semaphore\n";
        first_queue_sema.wait();
        std::cout << "FILL_1: semaphore signal received!\n";
    }
}

_Noreturn void fill_single_rider_queue() {

    // This generates group amount
    std::random_device dev_group_amount;
    std::mt19937 rng_group_amount(dev_group_amount());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4);

    std::cout << "FILL_SINGLE: hello!\n";
    while (true) {

        // We fill the queue here;
        for (int group_amount = 0; group_amount < dist4(rng_group_amount); group_amount++) {
            group single_rider = {.group_number = group_amount + 1, .size = 1};
            single_queue.push(single_rider);
        }

        // Wait for people to fill the queue
        std::this_thread::sleep_for(std::chrono::seconds (1));

        // Signal other thread that queue is full
        std::cout << "FILL_SINGLE: signaling semaphore\n";
        single_queue_sema.signal();

        // Wait until other thread empties queue
        std::cout << "FILL_SINGLE: waiting semaphore\n";
        single_queue_sema.wait();
        std::cout << "FILL_SINGLE: semaphore signal received!\n";
    }
}

#endif //SEMAPHORES_QUEUE_HPP