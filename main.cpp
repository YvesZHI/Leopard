#include "Graph.h"


int main(int argc, char **argv)
{
    Graph g{4};
    g.Init("case1.graph");
    g.Run();

    return EXIT_SUCCESS;
}
