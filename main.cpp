#include <iostream>
#include <thread>

#include "queue.hpp"
#include "cart.hpp"
#include "queue.hpp"

int main() {
    init_carts();

    std::thread first_fill_thread(fill_first_queue);
    std::thread first_queue_thread(fill_cart_from_first_queue);
    std::thread single_rider_thread(fill_single_rider_queue);

    first_fill_thread.join();
    first_queue_thread.join();
    single_rider_thread.join();

    return 0;
}
