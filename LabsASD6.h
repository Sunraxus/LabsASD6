﻿#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <memory>
#include <algorithm>
#include <limits>

template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;

        Edge(const Vertex& from, const Vertex& to, const Distance& distance)
            : from(from), to(to), distance(distance) {}

        bool operator==(const Edge& other) const {
            return from == other.from && to == other.to && distance == other.distance;
        }
    };

    bool has_vertex(const Vertex& v) const; 
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
    std::vector<Vertex> vertices() const;
    void add_edge(const Vertex& from, const Vertex& to, const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); 
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e) const; 
    std::vector<Edge> edges(const Vertex& vertex);
    size_t order() const;
    size_t degree(const Vertex& v) const;
    std::vector<Vertex> walk_in_width(const Vertex& start_vertex) const;
    void print() const;
    std::pair<std::vector<Edge>, Distance> dijkstras_algorithm(const Vertex& from, const Vertex& to) const;
    Vertex farthest_from_neighbors() const;

private:
    std::unordered_map<Vertex, std::vector<Edge>> adjacencies_list;
};

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const {
    return adjacencies_list.count(v) > 0;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_vertex(const Vertex& v) {
    adjacencies_list[v];
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v) {
    if (!has_vertex(v)) return false;
    adjacencies_list.erase(v);
    for (auto& [vertex, edges] : adjacencies_list) {
        auto iter = std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return e.to == v; });
        edges.erase(iter, edges.end());
    }
    return true;
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::vertices() const {
    std::vector<Vertex> all_vertices;
    for (const auto& pair : adjacencies_list) {
        all_vertices.push_back(pair.first);
    }
    return all_vertices;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
    if (!has_vertex(from)) {
        add_vertex(from);
    }
    if (!has_vertex(to)) {
        add_vertex(to);
    }
    auto& edges = adjacencies_list[from];
    edges.emplace_back(from, to, d);
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to) {
    if (!has_vertex(from)) return false;
    auto& edges = adjacencies_list[from];
    auto iter = std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return e.to == to; });
    if (iter == edges.end()) return false;
    edges.erase(iter, edges.end());
    return true;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e) {
    if (!has_vertex(e.from)) return false;
    auto& edges = adjacencies_list[e.from];
    auto iter = std::remove_if(edges.begin(), edges.end(), [&](const Edge& edge) { return edge == e; });
    if (iter == edges.end()) return false;
    edges.erase(iter, edges.end());
    return true;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const {
    if (!has_vertex(from)) return false;
    const auto& edges = adjacencies_list.at(from);
    return std::any_of(edges.begin(), edges.end(), [&](const Edge& e) { return e.to == to; });
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge& e) const {
    if (!has_vertex(e.from)) return false;
    const auto& edges = adjacencies_list.at(e.from);
    return std::any_of(edges.begin(), edges.end(), [&](const Edge& edge) { return edge == e; });
}

template <typename Vertex, typename Distance>
std::vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& vertex) {
    if (!has_vertex(vertex)) return {};
    return adjacencies_list[vertex];
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const {
    return adjacencies_list.size();
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const {
    const auto& edges = adjacencies_list.at(v);
    return edges.size();
}

template<typename Vertex, typename Distance>
std::vector<Vertex> Graph<Vertex, Distance>::walk_in_width(const Vertex& start_vertex) const {
    std::vector<Vertex> result;
    if (!has_vertex(start_vertex)) return result;

    std::unordered_set<Vertex> visited;
    std::queue<Vertex> q;
    q.push(start_vertex);
    visited.insert(start_vertex);

    while (!q.empty()) {
        Vertex current = q.front();
        q.pop();
        result.push_back(current);

        for (const auto& edge : adjacencies_list.at(current)) {
            if (visited.find(edge.to) == visited.end()) {
                visited.insert(edge.to);
                q.push(edge.to);
            }
        }
    }

    return result;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print() const {
    for (const auto& pair : adjacencies_list) {
        const Vertex& vertex = pair.first;
        const auto& edges = pair.second;
        std::cout << vertex << " -> ";
        bool first = true;
        for (const auto& edge : edges) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << edge.to << "(" << edge.distance << ")";
            first = false;
        }
        std::cout << std::endl;
    }
}

template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::farthest_from_neighbors() const {
    if (adjacencies_list.empty()) {
        std::cerr << "The graph is empty" << std::endl;
        return Vertex();
    }

    Vertex farthest_vertex = Vertex();
    double max_avg_distance = -1.0;

    for (const auto& pair : adjacencies_list) {
        const Vertex& vertex = pair.first;
        const auto& edges = pair.second;

        double total_distance = 0.0;
        int neighbor_count = 0;

        for (const auto& edge : edges) {
            total_distance += edge.distance;
            ++neighbor_count;
        }

        double avg_distance = neighbor_count > 0 ? total_distance / neighbor_count : 0.0;

        if (avg_distance > max_avg_distance || (avg_distance == max_avg_distance && vertex < farthest_vertex)) {
            max_avg_distance = avg_distance;
            farthest_vertex = vertex;
        }
    }

    return farthest_vertex;
}

template<typename Vertex, typename Distance>
std::pair<std::vector<typename Graph<Vertex, Distance>::Edge>, Distance>
Graph<Vertex, Distance>::dijkstras_algorithm(const Vertex& from, const Vertex& to) const {
    std::unordered_map<Vertex, Distance> distances;
    std::unordered_map<Vertex, Vertex> predecessors;
    std::priority_queue<std::pair<Distance, Vertex>, std::vector<std::pair<Distance, Vertex>>, std::greater<>> pq;
    
    for (const auto& vertex : vertices()) {
        distances[vertex] = std::numeric_limits<Distance>::infinity();
        predecessors[vertex] = Vertex();
    }
    distances[from] = Distance();
    pq.push(std::make_pair(distances[from], from));

    while (!pq.empty()) {
        Distance current_distance = pq.top().first;
        Vertex current_vertex = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_vertex]) {
            continue;
        }

        for (const auto& edge : adjacencies_list.at(current_vertex)) {
            if (edge.distance < 0) {
                std::cerr << "Error: Graph contains negative-weight edges" << std::endl;
                return std::make_pair(std::vector<Edge>(), std::numeric_limits<Distance>::infinity());
            }
            Distance new_distance = current_distance + edge.distance;
            if (new_distance < distances[edge.to]) {
                distances[edge.to] = new_distance;
                predecessors[edge.to] = current_vertex;
                pq.push(std::make_pair(new_distance, edge.to));
            }
        }
    }

    std::vector<Edge> path;
    Distance shortest_distance = distances[to];
    if (shortest_distance == std::numeric_limits<Distance>::infinity()) {
        return std::make_pair(path, std::numeric_limits<Distance>::infinity());
    }

    for (Vertex at = to; at != from; at = predecessors[at]) {
        Vertex pred = predecessors[at];
        auto it = std::find_if(adjacencies_list.at(pred).begin(), adjacencies_list.at(pred).end(),
            [&at](const Edge& edge) { return edge.to == at; });
        if (it != adjacencies_list.at(pred).end()) {
            path.push_back(*it);
        }
    }

    std::reverse(path.begin(), path.end());
    return std::make_pair(path, shortest_distance);
}


