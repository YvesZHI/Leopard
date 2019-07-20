#ifndef TASK_H
#define TASK_H

#include <random>


/*
 * The class Task is the job.
 * It uses a random integer between MIN_MILLISEC to MAX_MILLISEC to sleep itself to simulate the duration of a job.
 * It overloads the operator().
 * 
 * Member:
 *     id:     node ID
 *     degree: degree of the node
 * degree == 0 means the job can be handled
 * degree == -1 means the job has been handled
 */
class Task
{
public:
    Task();
    explicit Task(unsigned int);
    ~Task() = default;
    Task(const Task &) = default;
    Task & operator=(const Task &) = default;
    Task(Task &&) = default;
    Task & operator=(Task &&) = default;

    inline void IncreaseDegree()
    {
        degree++;
    }

    inline void DecreaseDegree()
    {
        degree--;
    }

    inline bool IsReady() const
    {
        return degree == 0; // 0 means this task is ready to be handled
    }

    inline void SetNonValid() {
        degree = -1; // -1 means this task has been handled
    }

    inline int GetDegree() const
    {
        return degree;
    }

    // simulate the job
    unsigned int operator()();
    unsigned int operator()(unsigned int);
private:
    static std::default_random_engine e;
    static std::uniform_int_distribution<unsigned int> duration;
    enum {MIN_MILLISEC = 200, MAX_MILLISEC = 1000};

    unsigned int id;  // Node ID
    int degree;       // degree of Node
};

#endif
