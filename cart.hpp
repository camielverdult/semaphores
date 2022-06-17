//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_CART_HPP
#define SEMAPHORES_CART_HPP

#include <iostream>

#include "queue.hpp"

typedef struct cart {
    unsigned int capacity;
    unsigned int single_groups;
    unsigned int dual_groups;
    unsigned int triple_groups;
    bool left;
    bool back;
} cart_t;

void init_cart(cart* cart) {
    cart->capacity = 6;
    cart->single_groups = 0;
    cart->dual_groups = 0;
    cart->triple_groups = 0;
    cart->left = false;
}

cart cart_one;

_Noreturn void fill_cart_from_first_queue() {

    // A cart contains only one row of 6 people. And leaves around every 5 seconds.
    init_cart(&cart_one);

    std::cout << "CART_QUEUE: hello!\n";

    while (true) {
        std::cout << "CART_QUEUE: waiting semaphore\n";
        first_queue_sema.wait();
        std::cout << "CART_QUEUE: semaphore signal received!\n";

        std::cout << "CART_QUEUE: checking queues\n";

        // We fill cart here from queue
        std::cout << "Queue number " << first_queue.queue_number << " has " << first_queue.groups.size() << " groups. ";
        for (group g : first_queue.groups) {
//            std::cout << "Group number " << g.group_number << " has " << g.size << " people. ";

        }
        std::cout << "\n";
        first_queue.groups.clear();

        // Wait for people to get in the cart
        std::this_thread::sleep_for(std::chrono::seconds (3));

        std::cout << "CART_QUEUE: signaling semaphore\n";
        first_queue_sema.signal();
    }
}

unsigned int spots_left(cart* cart) {
    return cart->capacity - cart->dual_groups - cart->triple_groups;
}

_Noreturn void fill_cart_from_single_queue() {

    std::cout << "CART_SINGLE: hello!\n";

    while (true) {
        std::cout << "CART_SINGLE: waiting semaphore\n";
        single_queue_sema.wait();


        unsigned int spots_to_fill = spots_left(&cart_one);

        std::cout << "CART_SINGLE: filling last ";

        if (spots_to_fill > 1) {
            std::cout << "spot";
        } else {
            std::cout << spots_to_fill;
        }

        std::cout << " in cart\n";

        cart_one.single_groups = spots_to_fill;

        // Wait for people to get in the cart
        std::this_thread::sleep_for(std::chrono::seconds (3));

        std::cout << "CART_SINGLE: signaling semaphore\n";
        single_queue_sema.signal();
    }
}

#endif //SEMAPHORES_CART_HPP
