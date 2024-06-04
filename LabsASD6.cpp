#include "LabsASD6.h"

using namespace std;

void test() {
    Graph<int, double> test_g;
    test_g.add_vertex(1);
    test_g.add_vertex(2);
    test_g.add_vertex(3);
    test_g.add_vertex(4);
    test_g.add_vertex(5);
    test_g.add_vertex(6);
    test_g.add_vertex(7);
    test_g.add_edge(1, 2, 5.0);
    test_g.add_edge(1, 3, 5.0);
    test_g.add_edge(1, 6, 3.0);
    test_g.add_edge(1, 7, 6.0);
    test_g.add_edge(2, 3, 4.0);
    test_g.add_edge(3, 4, 3.0);
    test_g.add_edge(4, 2, 4.0);
    test_g.add_edge(4, 5, 3.0);
    test_g.add_edge(5, 1, 7.0);
    test_g.add_edge(5, 6, 5.0);
    test_g.add_edge(6, 4, 8.0);
    test_g.add_edge(7, 3, 6.0);
    test_g.add_edge(7, 5, 7.0);
    test_g.add_edge(7, 6, 4.0);
    cout << "Пример графа заполненного значениями: " << endl;
    test_g.print();
    cout << endl << endl << endl;
    cout << "Проверка работы алгоритма Дейкстры: " << endl;
    int from_vertex = 1;
    int to_vertex = 5;
    auto [path, shortest_distance] = test_g.dijkstras_algorithm(from_vertex, to_vertex);
    if (shortest_distance != numeric_limits<double>::infinity()) {
        cout << "Кратчайший путь из вершины " << from_vertex << " до вершины " << to_vertex << " имеет вес " << shortest_distance << " ,сам путь:";
        for (const auto& edge : path) {
            cout << " (" << edge.from << "->" << edge.to << ")";
        }
        cout << endl;
    }
    else {
        cout << "Не существует пути из" << from_vertex << " до " << to_vertex << endl;
    }
    cout << endl << endl << endl;
    cout << "Проверка методов проверки наличия вершин и рёбер: " << endl;
    cout << "Граф имеет вершину 1: " << test_g.has_vertex(1) << endl;
    cout << "Граф имеет вершину 9: " << test_g.has_vertex(9) << endl;
    cout << "Граф имеет ребро из 7 в 6: " << test_g.has_edge(7, 6) << endl;
    cout << "Граф имеет ребро из 2 в 1: " << test_g.has_edge(2, 1) << endl;
    cout << endl << endl << endl;

    cout << "Проверка метода удаления вершин: " << endl;
    test_g.remove_vertex(5);
    cout << "Удалена вершина 5. Граф теперь: " << endl;
    test_g.print();
    cout << "Граф имеет вершину 5: " << test_g.has_vertex(5) << endl;
    cout << "Граф имеет ребро из 5 в 6: " << test_g.has_edge(5, 6) << endl;
    cout << endl << endl << endl;
    cout << "Проверка метода vertices: " << endl;
    vector<int> vertices = test_g.vertices();
    cout << "Вершины графа: ";
    for (int v : vertices) {
        cout << v << " ";
    }
    cout << endl << endl << endl;
    cout << "Проверка метода удаления рёбер: " << endl;
    test_g.remove_edge(1, 2);
    cout << "Удалено ребро из 1 в 2. Граф теперь: " << endl;
    test_g.print();
    cout << "Граф имеет ребро из 1 в 2: " << test_g.has_edge(1, 2) << endl;
    cout << endl << endl << endl;
    cout << "Проверка метода получения рёбер из вершин: " << endl;
    vector<Graph<int>::Edge> edges = test_g.edges(1);
    cout << "Рёбра из вершины 1:" << endl;
    for (const auto& edge : edges) {
        cout << "Из вершины: " << edge.from << " до вершины: " << edge.to << " Веса: " << edge.distance << endl;
    }
    cout << endl << endl << endl;
    cout << "Проверка метода order: " << endl;
    cout << "Количество вершин в графе: " << test_g.order() << endl;
    cout << endl << endl << endl;

    cout << "Проверка метода degree: " << endl;
    cout << "Степень вершины 1: " << test_g.degree(1) << endl;
    cout << endl << endl << endl;
    cout << "Проверка обхода в ширину: " << endl;
    vector<int> bfs_result = test_g.walk_in_width(1);
    cout << "Обход графа в ширину начиная с вершины 1: ";
    for (int v : bfs_result) {
        cout << v << " ";
    }
    cout << endl << endl << endl;
    cout << "Проверка метода has_edge(const Edge& e): " << endl;
    Graph<int, double>::Edge edge(1, 3, 5.0);
    cout << "Граф имеет ребро (1 -> 3) с весом 5.0: " << test_g.has_edge(edge) << endl;
    cout << endl << endl << endl;

    cout << "Проверка метода remove_edge(const Edge& e): " << endl;
    test_g.remove_edge(edge);
    cout << "Удалено ребро (1, 3) с весом 5. Граф теперь: " << endl;
    test_g.print();
    cout << "Граф имеет ребро (1, 3) с весом 5: " << test_g.has_edge(edge) << endl;
    cout << endl << endl << endl;

    cout << "Проверка Задачи: " << endl;
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
    std::cout << "Самая удаленная вершина: " << farthest_traumapoint << std::endl;

}
    
int main() {
    setlocale(LC_ALL, "Russian");
    test();

    return 0;
}