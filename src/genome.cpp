#include "genome.h"
#include "graph.h"

namespace genome
{

std::string assembly(size_t k, const std::vector<std::string> & reads)
{
    if (k == 0 || reads.empty()) {
        return "";
    }

    Graph graph;
    for (auto const &read: reads) {
        for (size_t i = 0; i + 1 + k <= read.length(); i++) {
            Node from = Node(read).substr(i, k);
            Node to = Node(read).substr(i + 1, k);
            graph.add_edge(Edge(from, to));
        }
    }

    std::list<Edge> path = graph.find_euler_path();
    Edge start = path.front();
    std::string genome(start.from());
    genome += start.to().substr(k - 1);
    path.pop_front();
    for (auto const &edge: path) {
        Node to = edge.to();
        genome += to[to.size() - 1];
    }
    return genome;
}
}
