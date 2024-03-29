# semaphores - OS2
Camiel Verdult & Marnix Laar

## Introduction

We received an assigment to simulate the queing system for a Baron 1898 roller coaster in the Efteling for our Operating Systems 2 class in the Applied Computer Science study. The roller-coaster's queues have been split into two queues. A queue with groups of 2 or 3 people, and a queue with single riders. The carts of the rollercoaster fit 6 people in a row.
Our job is to write a piece of software that keeps track of the queues and fills the carts with groups first, and finishes off with single riders.

## Assignment

The assignment was to simulate the Baron 1898 roller coaster using threads that fill and empty the riders queue and a thread that would act as the cart. These threads would communicate through semaphores to let threads know what should happen next. To keep track of queues and carts, we have 5 variables on the program heap with infinite lifetime. One of these is the cart, two are semaphores for thread flow control and two are for the group and single queues.

The semaphores can be waited (`sem_wait`) and signaled (`sem_signal`) to inform a thread/process to continue/pause operation. This waiting and signalling of other threads/processes prevents possible deadlocking of the program by ensuring sequential thread flow. A general overview of the program is depicted in the diagram below.

![](diagram/semaphores.png)

Different threads have different access to the heap. The combination of the access to the heap and the semaphore communication between threads allows for smooth operation of the program.

## Testing

For verifying that this program works for longer periods of time or when threads run at different speeds. The program was tested with very low delays for filling the queues and cart. This low delay meant that the program could be simulated to run a lot of cycles in a short time, while performing a lot of read and write operations on the `std::queue` queues per second. The `std::queue` type is not thread-safe, so this would mean that we could come across some weird behaviour. This did not happen, since the fill and empty thread do not access the same elements in the queue. The fill thread puts new groups in the back of the queue, while the empty thread retrieved groups from the front of the queue. The program does not lock up, even with very low delays for filling and emptying the cart.

## Results

By collecting data of riders, we can determine how many of which groups have gone in the roller coaster. In the graph below it becomes clear that more groups of two and three get to go in the coaster than single riders. This is no surprise as these groups are prioritised, and the single riders are only used to fill the carts in case no groups fit anymore.

![](img/Semaphore_graph_BIGDATA.svg)
![](img/group-distribution_percentage.svg)

It makes sense that there are more groups of three and two than single riders. This is because groups will always be fitted first, and single riders will fit only when there is space left in the cart. This means that a cart can be filled with 2 groups of three or 3 groups of two, without the need for a single rider to be added.

## Conclusion

We have built a program that simulates the queuing system of Baron 1898 and analysed its behaviour to verify that the program flow would not deadlock and displayed normally-distributed results that were to be expected by the random number generation module we used. This was a very interesting and fun assignment to do, it has definitely learned me the use of semaphores for thread-based operations.