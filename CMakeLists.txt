cmake_minimum_required(VERSION 3.22)
project(Semaphores C CXX)

set(CXX_STANDARD 23)

# assume built-in pthreads on MacOS
IF(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF()

add_executable(${PROJECT_NAME} main.cpp baron.cpp clock_thread.h clock_thread.cpp cart.hpp cart.cpp queue.hpp riders_queue.hpp baron.hpp)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}) # Add the threads library to the executable.