//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_QUEUE_HPP
#define SEMAPHORES_QUEUE_HPP

#include <vector>

typedef struct group {
    int group_number;
    unsigned int size;
} group_t;

typedef struct queue {
    int queue_number;
    std::vector<group> groups;
} queue_t;

#endif //SEMAPHORES_QUEUE_HPP
