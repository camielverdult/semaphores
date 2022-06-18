//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_CART_HPP
#define SEMAPHORES_CART_HPP

#include <iostream>

#include "queue.hpp"

#define PERSON_GET_IN_DELAY 1

typedef struct cart {
    unsigned int capacity;
    unsigned int single_groups;
    unsigned int dual_groups;
    unsigned int triple_groups;
    bool left;
    bool back;
} cart;

void init_cart(cart* cart) {
    cart->capacity = 6;
    cart->single_groups = 0;
    cart->dual_groups = 0;
    cart->triple_groups = 0;
    cart->left = false;
}

cart cart_one;

void init_carts() {
    // A cart contains only one row of 6 people. And leaves around every 5 seconds.
    init_cart(&cart_one);
}

unsigned int spots_left(cart* cart) {
    return cart->capacity - cart->dual_groups - cart->triple_groups - cart->single_groups;
}

_Noreturn void fill_cart_from_first_queue() {
    std::cout << "CART_QUEUE: hello!\n";

    while (true) {
        std::cout << "CART_QUEUE: waiting first semaphore\n";
        first_queue_sema.wait();
        std::cout << "CART_QUEUE: first semaphore signal received!\n";

        std::cout << "CART_QUEUE: checking queues\n";

        while (spots_left(&cart_one) <= first_queue.front().size) {

            switch (first_queue.front().size) {
                case 2:
                    cart_one.dual_groups++;
                    break;
                case 3:
                    cart_one.triple_groups++;
                    break;
                default:
                    // This should never happen
                    break;
            }

            // Removes front element in first queue
            first_queue.pop();

            // Wait 1 second per person to get in the cart
            std::this_thread::sleep_for(std::chrono::seconds (first_queue.front().size * PERSON_GET_IN_DELAY));
        }

        // Check if we need to signal the fill_cart_from_single_queue thread
        if (spots_left(&cart_one)) {
            unsigned int spots_to_fill = spots_left(&cart_one);

            std::cout << "CART_SINGLE: filling last ";

            if (spots_to_fill > 1) {
                std::cout << "spot";
            } else {
                std::cout << spots_to_fill << " spots ";
            }

            std::cout << " in cart\n";

            std::cout << "CART_QUEUE: signaling single semaphore\n";
            single_queue_sema.signal();
            std::cout << "CART_QUEUE: waiting first semaphore\n";
            single_queue_sema.wait();
        }

        std::cout << "\n";

        std::cout << "CART_QUEUE: signaling first semaphore\n";
        first_queue_sema.signal();
    }
}

_Noreturn void fill_cart_from_single_queue() {

    std::cout << "CART_SINGLE: hello!\n";

    while (true) {
        std::cout << "CART_SINGLE: waiting single semaphore\n";
        single_queue_sema.wait();

        while (spots_left(&cart_one) != 0) {
            cart_one.single_groups++;
            first_queue.pop();

            // Wait for people to get in the cart
            std::this_thread::sleep_for(std::chrono::seconds (PERSON_GET_IN_DELAY));
        }

        std::cout << "CART_SINGLE: signaling single semaphore\n";
        single_queue_sema.signal();
    }
}

#endif //SEMAPHORES_CART_HPP
