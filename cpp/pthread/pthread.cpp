/// @author Benjamin Alcocer

#include <iostream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

// Global variables
mutex tLock;
int counter = 0;

void example()
{
    tLock.lock();
    ++counter;
    tLock.unlock();
}

int main()
{
    // https://en.cppreference.com/w/cpp/thread/thread/hardware_concurrency
    const unsigned int MAX_THREADS = thread::hardware_concurrency();  // max threads
    vector<thread> threadPool;  // vector of threads

    printf("Max threads supported by this system: %d\n", MAX_THREADS);

    for (size_t i = 0; i < MAX_THREADS; ++i)
    {
        //spawn a thread
        //~ threadPool.push_back(thread(multiplyToNum1, number2[i], num2Max - i));
        threadPool.push_back(thread(example));

        // The following is not needed in this case, since we only create
        // MAX_THREADS amount of threads.
        //
        //if we spawned the max amount of threads that this system can handle
        //we wait for all of them to finish before we spawn more threads
        if (threadPool.size() == MAX_THREADS)
        {
            for (size_t j = 0; j < threadPool.size(); ++j)
                threadPool[j].join();

            threadPool.clear();
        }
    }

    // wait for any leftover threads that were spawned in the above loop before
    // continuing
    for (size_t j = 0; j < threadPool.size(); ++j)
            threadPool[j].join();
    threadPool.clear();


    printf("Final value of counter: %d\nWhich equals max threads\n", counter);
    return EXIT_SUCCESS;
}
