//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_CART_HPP
#define SEMAPHORES_CART_HPP

#include <iostream>

#include "queue.hpp"
#include "clock_thread.hpp"

typedef struct cart {
    int capacity;
    int single_groups;
    int dual_groups;
    int triple_groups;
    bool left;
} cart_t;


std::vector<cart> carts;

_Noreturn void fill_from_first_queue() {

    cart cart_one = {.capacity = 6, .single_groups = 0, .dual_groups = 0, .triple_groups = 0, .left = false};
    carts.push_back(cart_one);

    cart cart_two = {.capacity = 6, .single_groups = 0, .dual_groups = 0, .triple_groups = 0, .left = false};
    carts.push_back(cart_two);

    std::cout << "CART: hello!\n";

    while (true) {
        std::cout << "CART: waiting semaphore\n";
        semaphore_wait(clock_sema);

        std::cout << "CART: checking queues\n";

        // We fill the queue here;
        std::cout << "Queue number " << first_queue.queue_number << " has " << first_queue.groups.size() << " groups. ";
        for (group g : first_queue.groups) {
            std::cout << "Group number " << g.group_number << " has " << g.size << " people. ";
        }
        std::cout << "\n";
        first_queue.groups.clear();

        // Wait for people to get in the cart
        std::this_thread::sleep_for(std::chrono::seconds (3));

        semaphore_signal(clock_sema);
    }
}

#endif //SEMAPHORES_CART_HPP
