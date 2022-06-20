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
    unsigned int size;
} group_t;

// We gebruiken hier geen semaphores want de rijen kunnen worden gevuld en geleegd tegelijk
// Er wordt gezorgd voor niet mutual access door mutexes

// Queue for first queue
std::queue<group> first_queue;
std::mutex first_queue_mutex;

// Queue for second queue
std::queue<group> single_queue;
std::mutex single_queue_mutex;

_Noreturn void fill_first_queue() {
    // This generates a uniform distribution of groups being either 2 or 3 people big
    std::random_device dev_group_size;
    std::mt19937 rng_group_size(dev_group_size());
    std::uniform_int_distribution<std::mt19937::result_type> rand_group_size(2,3);

    std::cout << "FILL_1: hello!\n";
    while (true) {

        single_queue_mutex.lock();

        // About every second one group enters the normal queue
        group random_group = {.size = rand_group_size(rng_group_size)};
        first_queue.push(random_group);

        single_queue_mutex.unlock();

        // Wait for people to fill the queue
        std::this_thread::sleep_for(std::chrono::seconds (1));
    }
}

_Noreturn void fill_single_rider_queue() {

    std::cout << "FILL_SINGLE: hello!\n";
    while (true) {

        // About every two seconds one person enters the single rider queue
        std::this_thread::sleep_for(std::chrono::seconds (2));

        // Lock the single_queue vector to this thread to avoid mutual access
        single_queue_mutex.lock();

        // We fill the queue here
        group single_rider = {.size = 1};
        single_queue.push(single_rider);

        single_queue_mutex.unlock();
    }
}

#endif //SEMAPHORES_QUEUE_HPP