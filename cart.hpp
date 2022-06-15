//
// Created by Camiel Verdult on 13/06/2022.
//

#ifndef SEMAPHORES_CART_HPP
#define SEMAPHORES_CART_HPP

typedef struct cart {
    int capacity;
    int single_groups;
    int dual_groups;
    int triple_groups;
    bool left;
} cart_t;

void cart_init(cart_t* cart) {
    cart->capacity = 6;
    cart->single_groups = 0;
    cart->dual_groups = 0;
    cart->triple_groups = 0;
    cart->left = false;
}

#endif //SEMAPHORES_CART_HPP
