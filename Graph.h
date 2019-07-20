#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <unordered_set>

#include "ThreadPool.h"
#include "Task.h"


/*
 * Description:
 *     The class Graph uses a hashmap(unordered_map) to represents the graph.
 *     hashmap.first is the node ID
 *     hashmap.second is a pair:
 *         pair.first is the task corresponding to the node, it contains the degree and the ID of the node
 *         pair.second is a set, representing the neighbours of the node
 * Others:
 *     It contains a threadpool to handle all tasks.
 *     std::future::get() is used to acquire the result coming from the threadpool.
 */
class Graph
{
public:
    explicit Graph(unsigned int = 4);
    ~Graph() = default;
    Graph(const Graph &) = delete;
    Graph & operator=(const Graph &) = delete;
    Graph(Graph &&) = delete;
    Graph & operator=(Graph &&) = delete;

    void Init(const char *); // read file to init the graph
    void Run();
    void ShowInfo() const;   // show the graph
private:
    std::unordered_map<unsigned int, std::pair<Task, std::unordered_set<unsigned int>>> graph;
    ThreadPool tPool;
};

#endif
