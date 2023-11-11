// #include <stdio.h>

#include <atomic>
#include <memory>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <time.h> //time(&time_t)
#include <unistd.h>

constexpr int TEN_SECONDS = 10000000;

constexpr int ONE_SECOND = 1000000;

constexpr int TEN_MILLI = 100000;

constexpr int ONE_MILLI = 10000;

constexpr int THOUSAND_MICRO = 1000;

constexpr int HUNDRED_MICRO = 100;

constexpr int TEN_MICRO = 10;

constexpr int NUM_OF_THREADS = 100000;

std::mutex m;

// usleep expects a microsecond latency input


// #include "lib/base.h" //ignore on normal vscode
// #include "libc/ghost.h" //ignore on normal vscode

int main() {

    int random = rand();

    int count = 1000000;

    //start timer to see how long it is going 
    std::chrono::time_point start = std::chrono::steady_clock::now();


    //This sleeps for ten second
    usleep(100000);

    for (int i =0; i < NUM_OF_THREADS; ++i) {
        if (i%10 == 4) {
            GhostThread t(GhostThread::KernelScheduler::kGhost, []{
                std::chrono::time_point thread_start = std::chrono::steady_clock::now();

                usleep(TEN_MILLI);

                std::chrono::duration<double> diff =  std::chrono::steady_clock::now() - thread_start;
                
                m.lock();
                std::cout << "thread " << i << " ran in: " << diff.count();
                m.unlock();


            });
        } else {
            GhostThread t(GhostThread::KernelScheduler::kGhost, []{
                usleep(5); //sleep 5 microseconds

                m.lock();
                std::cout << "running fast thread " << std::endl;
                m.unlock();
            }
        }
    }

    std::chrono::duration<double> diff =  std::chrono::steady_clock::now() - start;

    m.lock();
    std::cout << "finished creating all the threads in: " << diff.count() << std::endl;
    m.unlock();



    usleep(TEN_SECONDS*3) //sleep for thirty seconds
    

    m.lock();
    std::cout << "done sleeping" << std::endl;
    m.unlock();
    
    return 0;

}

