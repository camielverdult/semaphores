cmake_minimum_required(VERSION 3.22)
project(semaphores C CXX)

set (CMAKE_CXX_STANDARD 11)

# assume built-in pthreads on MacOS
IF(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF()

add_executable(${PROJECT_NAME} main.cpp queue.hpp cart.hpp sema.h)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}) # Add the threads library to the executable.