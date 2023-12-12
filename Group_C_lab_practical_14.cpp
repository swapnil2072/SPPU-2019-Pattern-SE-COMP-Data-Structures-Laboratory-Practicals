#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>

using namespace std;

class Graph {
    unordered_map<string, int> cityIndices;
    vector<vector<int>> adjacencyMatrix;
    int numVertices;

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjacencyMatrix.resize(vertices, vector<int>(vertices, -1));
    }

    void addCity(const string& city) {
        cityIndices[city] = cityIndices.size();
    }

    void addEdge(const string& src, const string& dest, int cost) {
        int srcIndex = cityIndices[src];
        int destIndex = cityIndices[dest];
        adjacencyMatrix[srcIndex][destIndex] = cost;
        adjacencyMatrix[destIndex][srcIndex] = cost;
    }

    bool isConnected() {
        vector<bool> visited(numVertices, false);
        dfs(0, visited);

        for (bool visit : visited) {
            if (!visit) {
                return false;
            }
        }

        return true;
    }

    void dfs(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        for (int i = 0; i < numVertices; ++i) {
            if (adjacencyMatrix[vertex][i] != -1 && !visited[i]) {
                dfs(i, visited);
            }
        }
    }

    void findShortestPath(const string& startCity, const string& endCity) {
        if (!cityIndices.count(startCity) || !cityIndices.count(endCity)) {
            cout << "Invalid city names." << endl;
            return;
        }

        int startCityIndex = cityIndices[startCity];
        int endCityIndex = cityIndices[endCity];

        vector<int> dist(numVertices, INT_MAX);
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);

        dist[startCityIndex] = 0;

        for (int i = 0; i < numVertices - 1; ++i) {
            int u = findMinDistance(dist, visited);
            visited[u] = true;

            for (int v = 0; v < numVertices; ++v) {
                if (!visited[v] && adjacencyMatrix[u][v] != -1 && dist[u] != INT_MAX &&
                    dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjacencyMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        // Display the shortest path and minimum cost
        displayShortestPath(startCityIndex, endCityIndex, dist, parent);
    }

    int findMinDistance(const vector<int>& dist, const vector<bool>& visited) {
        int minDist = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minIndex = i;
            }
        }

        return minIndex;
    }

    void displayShortestPath(int startCityIndex, int endCityIndex, const vector<int>& dist, const vector<int>& parent) {
        if (dist[endCityIndex] == INT_MAX) {
            cout << "No path found from " << getCityName(startCityIndex) << " to " << getCityName(endCityIndex) << endl;
            return;
        }

        cout << "Shortest Path from " << getCityName(startCityIndex) << " to " << getCityName(endCityIndex) << ": ";
        int currentCity = endCityIndex;
        vector<int> path;

        while (currentCity != -1) {
            path.push_back(currentCity);
            currentCity = parent[currentCity];
        }

        for (int i = path.size() - 1; i >= 0; --i) {
            cout << getCityName(path[i]);
            if (i != 0) {
                cout << " -> ";
            }
        }

        cout << endl;
        cout << "Minimum Cost: " << dist[endCityIndex] << endl;
    }

    string getCityName(int index) {
        for (const auto& entry : cityIndices) {
            if (entry.second == index) {
                return entry.first;
            }
        }
        return "";
    }

    void displayAdjacencyMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << adjacencyMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    int numCities;
    cout << "Enter the number of cities: ";
    cin >> numCities;

    Graph graph(numCities);

    for (int i = 0; i < numCities; ++i) {
        string city;
        cout << "Enter city name: ";
        cin >> city;
        graph.addCity(city);
    }

    int choice;
    while (true) {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Add flight path" << endl;
        cout << "2. Check connectivity" << endl;
        cout << "3. Find shortest path and minimum cost" << endl;
        cout << "4. Display adjacency matrix" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string src, dest;
                int cost;
                cout << "Enter source city: ";
                cin >> src;
                cout << "Enter destination city: ";
                cin >> dest;
                cout << "Enter flight cost: ";
                cin >> cost;
                graph.addEdge(src, dest, cost);
                cout << "Flight path added successfully!" << endl;

                graph.displayAdjacencyMatrix();  // Display adjacency matrix after adding the flight path

                break;
            }
            case 2: {
                bool connected = graph.isConnected();
                if (connected) {
                    cout << "The graph is connected." << endl;
                } else {
                    cout << "The graph is not connected." << endl;
                }
                break;
            }
            case 3: {
                string startCity, endCity;
                cout << "Enter the starting city: ";
                cin >> startCity;
                cout << "Enter the destination city: ";
                cin >> endCity;
                graph.findShortestPath(startCity, endCity);
                break;
            }
            case 4: {
                graph.displayAdjacencyMatrix();
                break;
            }
            case 5: {
                cout << "Exiting the program..." << endl;
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

/*
The overall time and space complexity of the program and each function are as follows:

1. `Graph` constructor: The constructor initializes the adjacency matrix and cityIndices. It has a time complexity of O(V^2), where V is the number of vertices (cities), as it resizes the adjacency matrix to V^2 and initializes all entries to -1. The space complexity is O(V^2) for the adjacency matrix and O(V) for the cityIndices.

2. `Graph::addCity`: This function adds a city to the cityIndices map. It has a time complexity of O(1) as it performs a map insertion. The space complexity is O(V) for the cityIndices.

3. `Graph::addEdge`: This function adds an edge between two cities in the graph. It updates the adjacency matrix. It has a time complexity of O(1) as it directly accesses the adjacency matrix positions corresponding to the source and destination cities. The space complexity is O(1) as it does not use any additional space.

4. `Graph::isConnected`: This function checks if the graph is connected using a Depth-First Search (DFS) algorithm. It has a time complexity of O(V^2), where V is the number of vertices, as it performs a DFS on the adjacency matrix. The space complexity is O(V) for the visited vector.

5. `Graph::dfs`: This function performs a Depth-First Search traversal starting from a given vertex. It updates the visited vector. It has a time complexity of O(V^2), where V is the number of vertices, as it visits each vertex and each edge once. The space complexity is O(V) for the visited vector.

6. `Graph::findShortestPath`: This function finds the shortest path and minimum cost between two cities using Dijkstra's algorithm. It has a time complexity of O(V^2), where V is the number of vertices, as it iterates V times and performs operations on the adjacency matrix. The space complexity is O(V) for the dist, visited, and parent vectors.

7. `Graph::findMinDistance`: This function finds the vertex with the minimum distance from the source in Dijkstra's algorithm. It has a time complexity of O(V), where V is the number of vertices, as it iterates through the dist and visited vectors. The space complexity is O(1) as it does not use any additional space.

8. `Graph::displayShortestPath`: This function displays the shortest path and minimum cost between two cities. It has a time complexity of O(V), where V is the number of vertices, as it traces the path from the end city to the start city. The space complexity is O(V) for the path vector.

9. `Graph::getCityName`: This function retrieves the name of a city from its index. It has a time complexity of O(V), where V is the number of vertices, as it iterates through the cityIndices map. The space complexity is O(1) as it does not use any additional space.

10. `Graph::displayAdjacencyMatrix`: This function displays the adjacency matrix. It has a time complexity of O(V^2), where V is the number of vertices, as it prints all entries in the matrix. The space complexity is O(1) as it does not use any additional space.

The overall time complexity of the program depends on the number of cities and the operations performed. The overall space complexity is O(V^2) for the adjacency matrix and O(V) for other data structures used in the program.

Oral Questions:
1. What is the purpose of the `Graph` class?
2. How are cities represented in the graph? How is their

 connectivity stored?
3. How does the `isConnected` function determine if the graph is connected?
4. What algorithm is used to find the shortest path and minimum cost between two cities?
5. How does the `findMinDistance` function work in Dijkstra's algorithm?
6. How is the shortest path and minimum cost displayed in the `displayShortestPath` function?
7. How does the program handle invalid city names?
8. What is the time complexity of adding a flight path in the `addEdge` function?
9. What is the time complexity of checking connectivity in the `isConnected` function?
10. How does the program handle non-existent cities in the `findShortestPath` function?

Answers:
1. The `Graph` class represents a graph of cities and their flight paths. It provides functions to add cities, add flight paths, check connectivity, find the shortest path and minimum cost between cities, and display the adjacency matrix.
2. Cities are represented by their names using a `std::unordered_map<string, int>`. The connectivity between cities is stored in the adjacency matrix, where the indices correspond to cities, and the values represent the flight costs.
3. The `isConnected` function uses a Depth-First Search (DFS) algorithm to traverse the graph starting from the first city. If all cities are visited during the DFS, the graph is considered connected.
4. Dijkstra's algorithm is used to find the shortest path and minimum cost between two cities. It iteratively selects the vertex with the minimum distance from the source and updates the distances to its neighbors.
5. The `findMinDistance` function iterates through the distances of all vertices and returns the index of the vertex with the minimum distance. It excludes visited vertices.
6. The `displayShortestPath` function traces the shortest path from the end city to the start city using the parent array. It prints the cities in the path and the minimum cost.
7. If the user provides invalid city names when finding the shortest path, the program displays an error message.
8. Adding a flight path in the `addEdge` function has a constant time complexity of O(1) as it directly accesses the corresponding positions in the adjacency matrix.
9. Checking connectivity in the `isConnected` function has a time complexity of O(V^2), where V is the number of vertices, as it performs a DFS on the adjacency matrix.
10. If non-existent cities are provided in the `findShortestPath` function, the program displays an error message indicating invalid city names.
*/

