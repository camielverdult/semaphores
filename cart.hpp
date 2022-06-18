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
    bool left;
    bool back;
} cart;

void init_cart(cart* cart) {
    cart->capacity = 6;
    cart->left = false;
}

cart cart_one;
Semaphore cart_ride_sema;
std::mutex cart_one_mutex;

void init_carts() {
    // A cart contains only one row of 6 people. And leaves around every 5 seconds.
    init_cart(&cart_one);
}

_Noreturn void cart_ride() {

    std::cout << "CART_RIDE: hello!\n";

    while (true) {
        std::cout << "CART_RIDE: waiting cart_ride_sema\n";
        cart_ride_sema.wait();

        std::cout << "CART_RIDE: cart is leaving!\n";

        for (int i = 0; i < 10; i++) {
            std::cout << "CART_RIDE: weee!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "CART_RIDE: signalling cart_ride_sema";
        cart_ride_sema.signal();
    }
}

unsigned int spots_left(cart* cart) {

    // Lock the cart_one vector to this thread to avoid mutual access
    cart_one_mutex.lock();

    unsigned int people_in_cart = std::accumulate(cart->groups.begin(), cart->groups.end(), 0, [](int sum, group b) {
        return sum + b.size;
    });

    cart_one_mutex.unlock();

    return cart->capacity - people_in_cart;
}

_Noreturn void fill_cart_from_first_queue() {
    std::cout << "CART_QUEUE: hello!\n";

    while (true) {
        std::cout << "CART_QUEUE: waiting first semaphore\n";
        first_queue_sema.wait();
        std::cout << "CART_QUEUE: first semaphore signal received! checking queues\n";

        // Wait 5 seconds because of assignment requirement:
        // A cart contains only one row of 6 people. And leaves around every 5 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // Lock the cart_one vector to this thread to avoid mutual access
        cart_one_mutex.lock();

        // Check if the front group in first queue can fit in the cart
        while (spots_left(&cart_one) <= first_queue.front().size) {

            // Add front group to cart
            cart_one.groups.push_back(first_queue.front());

            // Removes front element in first queue
            first_queue.pop();
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

        cart_one_mutex.unlock();

        std::cout << "\n";

        // Let cart leave
        std::cout << "CART_QUEUE: signalling cart_ride_sema";
        cart_ride_sema.signal();
        std::cout << "CART_QUEUE: waiting cart_ride_sema";
        cart_ride_sema.wait();

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
            cart_one.groups.push_back(first_queue.front());
            first_queue.pop();
        }

        std::cout << "CART_SINGLE: signaling single semaphore\n";
        single_queue_sema.signal();
    }
}

void print_cart_row() {

    // Lock the cart_one vector to this thread to avoid mutual access
    cart_one_mutex.lock();

    for (group g : cart_one.groups) {
        for (int i = 0; i < g.size; i++) {
            switch (g.size) {
                case 1:
                    std::cout << "1️⃣";
                    break;
                case 2:
                    std::cout << "2️⃣";
                    break;
                case 3:
                    std::cout << "3️⃣";
                    break;
            }
        }
    }

    cart_one_mutex.unlock();
}


#endif //SEMAPHORES_CART_HPP
