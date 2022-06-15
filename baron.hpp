//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_BARON_HPP
#define SEMAPHORES_BARON_HPP

#include <thread>
#include "queue.hpp"
#include "clock_thread.h"

/*
 * A cart contains only one row of 6 people. And leaves around every 5 seconds.
 * About every two seconds one person enters the single rider queue.
 * About every second one group enters the normal queue, decide randomly if it is a
    group of 2 or 3 (50-50 chance). (hint: just make a semaphore queue of ‘groups’, and
    only when you ‘signal’ the next group, run a randomizer to ask the group in front
    how ‘big’ the group is. You don’t have to invent a sophisticated data structure)
 * At the front of the normal queue, ask at most the first three groups, how ‘big’ they
    are and see if they can fit in a row of 6. This will be the case with 2+2+2 or 3+3. In the
    case of 2+3 or 3+2 (or 2+2 and the next group 3) one (or more) people from the
    single rider queue will be invited to sit in the row.
 * If the normal queue is empty, the row can be filled with all single rider’s. If the single
    rider queue is empty, try to fill up as much as possible and a row/cart will leave with
    open seat’s. If both queues are empty the cart/row will wait till it can be filled at
    least with one group or one single rider.
 * When a cart leaves, neatly print the distribution of the people within that row and
    also the size of the queue’s at that moment.
*/

class baron {
public:

    baron() {
        _clock_thread = std::thread(clock_thread);
    }

private:
    std::thread _clock_thread;
    std::thread _single_rider_thread;
    std::thread _row_grabber_thread;

    queue _first_queue;
};

#endif //SEMAPHORES_BARON_HPP
