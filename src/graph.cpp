#include "graph.h"
#include <stack>
#include <algorithm>
#include <unordered_set>

namespace genome {

    size_t Edge::id = 0;

    Edge::Edge(Node from, Node to)
            : m_from(from), m_to(to), m_id(id++) {
    }

    bool Edge::operator==(const Edge &other) const {
        return m_from == other.m_from && m_to == other.m_to && m_id == other.m_id;
    }

    void Graph::add_edge(Edge edge) {
        m_adjacency_list[edge.from()].push_back(edge);
        m_degree[edge.from()]++;
        m_degree[edge.to()]++;
    }

    std::list<Edge> Graph::find_euler_path() {

        Node start;
        for (auto const &[node, list]: m_adjacency_list) {
            size_t out_degree = list.size();
            size_t degree = m_degree[node];
            size_t in_degree = degree - out_degree;
            if (degree % 2 == 1 && in_degree + 1 == out_degree) {
                start = node;
                break;
            }
        }

        std::list<Edge> path;

        std::stack<Node> stack;
        stack.push(start);

        Node last;

        while (!stack.empty()) {
            Node v = stack.top();
            size_t &v_degree = m_degree[v];
            if (v_degree == 0) {
                if (!last.empty()) {
                    path.emplace_front(v, last);
                }
                last = v;
                stack.pop();
            } else {
                std::vector<Edge> &v_list = m_adjacency_list[v];
                auto it = std::find_if(v_list.begin(), v_list.end(), [](const Edge &edge) {
                    return !edge.removed;
                });
                it->removed = true;
                v_degree--;
                Node to = (*it).to();
                m_degree[to]--;
                stack.push(to);
            }
        }
        return path;
    }
} // namespace genome
