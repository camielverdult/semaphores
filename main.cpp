#include <iostream>
#include <thread>

#include "clock_thread.hpp"
#include "cart.hpp"
#include "queue.hpp"

int main() {

    std::thread clock_thread(clock_thread_func);
    std::thread queue_thread(cart_thread_func);

    clock_thread.join();
    queue_thread.join();

    return 0;
}
