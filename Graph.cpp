#include "Graph.h"

#include <fstream>
#include <sstream>
#include <iostream>


Graph::Graph(unsigned int len) : tPool(len)
{
    // nothing to do
}

void Graph::Init(const char *filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::getline(infile, line);
    unsigned int total = static_cast<unsigned int>(std::stoul(line)); // the total of Nodes
    // init Nodes
    for (unsigned int i = 1; i <= total; i++) {
        graph[i] = std::make_pair(Task(i), std::unordered_set<unsigned int>());
    }
    while (std::getline(infile, line)) {
        std::istringstream iss{line};
        unsigned int id;
        iss >> id;
        unsigned int nid;
        while (iss >> nid) {
            graph[nid].second.insert(id);     // init neighbours of nid
            graph[id].first.IncreaseDegree(); // increase degree of id
        }
    }
    ShowInfo();
}

void Graph::Run()
{
    std::cout << "************* RUNNING *************" << std::endl;
    std::vector<std::future<unsigned int>> results; // container to store the results of the threadpool
    bool oneTaskFinished = false;
    // graph.size() == 0 means all jobs are done
    while (graph.size() != 0) {
        // put the tasks of all zero-degree nodes into the threadpool
        for (auto it = graph.begin(); it != graph.end(); ++it) {
            if (it->second.first.IsReady()) {
                std::cout << "Put Task " << it->first << " to the ThreadPool" << std::endl;
                results.emplace_back(tPool.enqueue(it->second.first));
                it->second.first.SetNonValid(); // once the task is handled by the threadpool, its degree becomes -1 to avoid double-adding it
            }
        }
        oneTaskFinished = false;
        while (!oneTaskFinished) {
            for (auto it = results.begin(); it != results.end();) {
                // check if the future's value is ready
                if (it->wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
                    unsigned int finishedID = it->get();
                    auto &neighbours = graph[finishedID].second;
                    // the degree of all neighbours of finishedID should be decrease by 1
                    for (auto nit = neighbours.begin(); nit != neighbours.end(); ++nit) {
                        graph[*nit].first.DecreaseDegree();
                        std::cout << "Degree of " << *nit << " decreased because of " << finishedID << std::endl;
                    }
                    it = results.erase(it); // erase the future of finishedID in the container
                    std::cout << "Erase Task " << finishedID << " from the graph" << std::endl;
                    graph.erase(finishedID); // erase finishedID from the graph
                    oneTaskFinished = true; // once any of tasks has finished, we loop the graph from the beginning
                    //break;
                } else {
                    ++it;
                }
            }
            if (!oneTaskFinished) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20)); // sleep 20 milliseconds to avoid exhaust CPU
            }
        }
    }
    std::cout << "************* DONE *************" << std::endl;
}

void Graph::ShowInfo() const
{
    std::cout << "************* INFO *************" << std::endl;
    for (auto it = graph.cbegin(); it != graph.cend(); ++it) {
        std::cout << "Task: " << it->first << ' ' << "Degree: " << it->second.first.GetDegree() << " Neighbours: ";
        for (auto nit = it->second.second.cbegin(); nit != it->second.second.cend(); ++nit) {
            std::cout << *nit << ' '; 
        }
        std::cout << std::endl;
    }
}
