#include <iostream>
#include <thread>

#include "queue.hpp"
#include "cart.hpp"
#include "queue.hpp"

int main() {
    init_carts();

    std::thread first_fill_thread(fill_first_queue);
    std::thread single_rider_thread(fill_single_rider_queue);

    std::thread first_fill_from_normal_queue_thread(fill_cart_from_first_queue);
    std::thread first_fill_from_single_queue_thread(fill_cart_from_single_queue);

    std::thread cart_ride_thread(cart_ride);

    first_fill_thread.join();
    single_rider_thread.join();

    first_fill_from_normal_queue_thread.join();
    first_fill_from_single_queue_thread.join();

    cart_ride_thread.join();

    return 0;
}
