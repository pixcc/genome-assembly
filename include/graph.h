#pragma once

#include <list>
#include <vector>
#include <string_view>
#include <unordered_map>

namespace genome
{

// one possible starting point
//

using Node = std::string_view;

class Edge
{
public:
    Edge(Node from, Node to);

    const auto &from() const { return m_from; }
    const auto &to() const { return m_to; }
    size_t get_id() const { return m_id; }

    bool operator==(const Edge &other) const;

    bool removed = false;

private:
    Node m_from;
    Node m_to;
    size_t m_id;
    static size_t id;
};

class Graph
{
public:
    void add_edge(Edge edge);

    std::list<Edge> find_euler_path();

private:
    std::unordered_map<Node, std::vector<Edge>> m_adjacency_list;
    std::unordered_map<Node, size_t> m_degree;
};

} // namespace genome
