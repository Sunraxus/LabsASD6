#include "LabsASD6.h"

int main() {
    Graph<std::string, double> g;

    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");
    g.add_vertex("D");

    g.add_edge("A", "B", 1.0);
    g.add_edge("A", "C", 2.0);
    g.add_edge("B", "C", 1.5);
    g.add_edge("C", "D", 3.0);
    g.add_edge("D", "A", 2.5);

    g.print();

    std::string farthest_traumapoint = g.farthest_from_neighbors();
    std::cout << "The farthest traumapoint is: " << farthest_traumapoint << std::endl;

    return 0;
    /*Graph<int, double> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(1, 2, 2.0);
    graph.add_edge(2, 3, 3.0);
    graph.add_edge(1, 3, 6.0);
    int from_vertex = 1;
    int to_vertex = 3;
    auto [path, shortest_distance] = graph.dijkstras_algorithm(from_vertex, to_vertex);

    if (shortest_distance != std::numeric_limits<double>::infinity()) {
        std::cout << "Shortest path from " << from_vertex << " to " << to_vertex << " with distance " << shortest_distance << " is:";
        for (const auto& edge : path) {
            std::cout << " (" << edge.from << "->" << edge.to << ")";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "There is no path from " << from_vertex << " to " << to_vertex << std::endl;
    }

    return 0;
    Graph<int> g;

    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);

    g.add_edge(1, 2, 1.5);
    g.add_edge(1, 3, 2.0);
    g.add_edge(2, 4, 3.0);
    g.add_edge(3, 4, 1.0);

    std::cout << "Graph after adding vertices and edges:" << std::endl;
    g.print();

    std::cout << "Graph has vertex 1: " << g.has_vertex(1) << std::endl;
    std::cout << "Graph has vertex 5: " << g.has_vertex(5) << std::endl;

    std::cout << "Graph has edge from 1 to 2: " << g.has_edge(1, 2) << std::endl;
    std::cout << "Graph has edge from 2 to 3: " << g.has_edge(2, 3) << std::endl;

    g.remove_edge(1, 3);
    std::cout << "Graph after removing edge from 1 to 3:" << std::endl;
    g.print();

    g.remove_vertex(2);
    std::cout << "Graph after removing vertex 2:" << std::endl;
    g.print();

    std::vector<int> vertices = g.vertices();
    std::cout << "Vertices in the graph: ";
    for (int v : vertices) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "Degree of vertex 1: " << g.degree(1) << std::endl;
    std::cout << "Degree of vertex 3: " << g.degree(3) << std::endl;

    std::cout << "Order of the graph: " << g.order() << std::endl;

    std::vector<int> bfs = g.walk_in_width(1);
    std::cout << "BFS starting from vertex 1: ";
    for (int v : bfs) {
        std::cout << v << " ";
    }
    std::cout << std::endl;*/

    return 0;
}