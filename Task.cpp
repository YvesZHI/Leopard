#include "Task.h"

#include <iostream>
#include <thread>
#include <chrono>


std::default_random_engine Task::e;
std::uniform_int_distribution<unsigned int> Task::duration{Task::MIN_MILLISEC, Task::MAX_MILLISEC};


Task::Task() : id{0}, degree{0}
{
    // nothing to do
}

Task::Task(unsigned int _id) : id{_id}, degree{0}
{
    // nothing to do
}

// simulate the job
unsigned int Task::operator()()
{
    std::cout << "Task " << id << " is starting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(duration(e)));
    std::cout << "--- Task " << id << " finished" << std::endl;
    return id;
}

// simulate the job
unsigned int Task::operator()(unsigned int d)
{
    std::cout << "Task " << id << " is starting..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(d));
    std::cout << "--- Task " << id << " finished" << std::endl;
    return id;
}
