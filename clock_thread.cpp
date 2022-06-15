//
// Created by Camiel Verdult on 13/06/2022.
//

#include "clock_thread.h"
#include <unistd.h>
#include <stdio.h>

_Noreturn void* clock_thread(void* _) {

    while (1) {
        printf("Hello from cock thread!\n");

        sleep(1);
    }

}