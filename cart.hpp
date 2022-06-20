//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_CART_HPP
#define SEMAPHORES_CART_HPP

#include <iostream>
#include <mutex>
#include <functional>

#include "queue.hpp"

typedef struct cart {
    unsigned int capacity;
    std::vector<group> groups;
} cart;

void init_cart(cart* cart) {
    cart->capacity = 6;
}

// Control variables needed for cart
cart cart_one;
Semaphore cart_ride_sema;

// Control variable needed for single queue
Semaphore single_queue_sema;

void init_carts() {
    // A cart contains only one row of 6 people. And leaves around every 5 seconds.
    init_cart(&cart_one);
}

void print_cart_row() {

    std::cout << "Cart row content:\n";

    for (group g: cart_one.groups) {
        for (int i = 0; i < g.size; i++) {
            switch (g.size) {
                case 1:
                    std::cout << "1";
                    break;
                case 2:
                    std::cout << "2";
                    break;
                case 3:
                    std::cout << "3";
                    break;
            }
        }
    }
    std::cout << "\n";
}

[[noreturn]] void cart_ride() {

    std::cout << "CART_RIDE: hello!\n";

    while (true) {

        cart_ride_sema.wait();

        std::cout << "CART_RIDE: cart is leaving!\n";

        for (int i = 0; i < 5; i++) {
            std::cout << "CART_RIDE: weee!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // All groups get out of cart
        cart_one.groups.clear();

        std::cout << "CART_RIDE: signalling cart_ride_sema\n";
        cart_ride_sema.signal();
    }
}

unsigned int spots_filled(cart* cart) {

    return std::accumulate(cart->groups.begin(),
                           cart->groups.end(),
                           0,
                           [](int sum, group b) {
                               return sum + b.size;
                           });
}

unsigned int spots_left(cart* cart) {

    // Lock the cart_one vector to this thread to avoid mutual access
    unsigned int people_in_cart = spots_filled(cart);

    return cart->capacity - people_in_cart;
}

[[noreturn]] void fill_cart_from_first_queue() {
    std::cout << "CART_QUEUE: hello!\n";

    while (true) { // Thread loop

        while (!group_queue.empty()) {

            // Check if the front group in first queue can fit in the cart
            while (spots_left(&cart_one) >= group_queue.front().size) {

                std::cout << "CART_QUEUE: filling cart with group of " << group_queue.front().size << " people\n";

                // Add front group to cart
                cart_one.groups.push_back(group_queue.front());

                // Removes front element in first queue
                group_queue.pop();

                if (group_queue.empty()) {
                    break;
                }
            }

            // Check if we need to signal the fill_cart_from_single_queue thread
            if (spots_left(&cart_one)) {
                // Signal single rider fill thread
                std::cout << "CART_QUEUE: signaling single semaphore\n";
                single_queue_sema.signal();
                std::cout << "CART_QUEUE: waiting first semaphore\n";
                single_queue_sema.wait();
            }

            std::cout << "\n";

            print_cart_row();

            // Let cart leave
            std::cout << "CART_QUEUE: signalling cart_ride_sema\n";
            cart_ride_sema.signal();
            std::cout << "CART_QUEUE: waiting cart_ride_sema\n";
            cart_ride_sema.wait();
        }
    }
}

[[noreturn]] void fill_cart_from_single_queue() {

    std::cout << "CART_SINGLE: hello!\n";

    while (true) {
        std::cout << "CART_SINGLE: waiting single semaphore\n";
        single_queue_sema.wait();

        unsigned int spots_to_fill = spots_left(&cart_one);

        // Pretty print
        std::cout << "CART_SINGLE: filling last ";

        if (spots_to_fill == 1) {
            std::cout << "spot";
        } else {
            std::cout << spots_to_fill << " spots";
        }

        std::cout << " in cart\n";
        // Pretty print end

        while (spots_left(&cart_one) != 0) {
            if (!single_queue.empty()) {
                cart_one.groups.push_back(single_queue.front());
                group_queue.pop();
            }
            else {
                std::cout << "CART_SINGLE: Queue empty, cart is not full!\n";
                std::this_thread::sleep_for(std::chrono::seconds (1));
            }
        }

        std::cout << "CART_SINGLE: signaling single semaphore\n";
        single_queue_sema.signal();
    }
}



#endif //SEMAPHORES_CART_HPP
