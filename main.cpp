#include <iostream>
#include <thread>

#include "clock_thread.hpp"
#include "cart.hpp"
#include "queue.hpp"

int main() {

    std::thread clock_thread(fill_first_queue);
    std::thread queue_thread(fill_from_first_queue);

    clock_thread.join();
    queue_thread.join();

    return 0;
}
