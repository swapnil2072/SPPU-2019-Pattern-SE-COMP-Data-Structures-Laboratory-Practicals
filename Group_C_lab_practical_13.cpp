#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>

using namespace std;

class Graph
{

private:
    map<string, int> nodeIndexes;
    vector<vector<int>> adjacencyMatrix;
    vector<vector<int>> adjcencyList;
    string getNodeName(int index);
    void dfsRecursive(int startingVertex, vector<bool> &visited);

public:
    void addNode(string node);
    void addEdge(string node1, string node2);
    void dfs(string startingVertex);
    void bfs(string startingVertex);
};

void Graph ::dfsRecursive(int startingVertex, vector<bool> &visited)
{
    cout << getNodeName(startingVertex) << " ";
    visited[startingVertex] = true;
    for (int i = 0; i < nodeIndexes.size(); i++)
    {
        if (i == startingVertex)
        {
            continue;
        }
        if (adjacencyMatrix[startingVertex][i] == 1 && !visited[i])
        {
            dfsRecursive(i, visited);
        }
    }
}

string Graph ::getNodeName(int index)
{
    for (auto it = nodeIndexes.begin(); it != nodeIndexes.end(); it++)
    {
        if (it->second == index)
        {
            return it->first;
        }
    }
    return "";
}

void Graph ::addNode(string node)
{
    if (nodeIndexes.find(node) == nodeIndexes.end())
    {
        int index = nodeIndexes.size();
        nodeIndexes[node] = index;
        adjacencyMatrix.resize(index + 1, vector<int>(index + 1, 0));
        adjcencyList.resize(index + 1);
    }
}

void Graph ::addEdge(string node1, string node2)
{
    if (nodeIndexes.find(node1) != nodeIndexes.end() && nodeIndexes.find(node2) != nodeIndexes.end())
    {
        int index1 = nodeIndexes[node1];
        int index2 = nodeIndexes[node2];
        adjacencyMatrix[index1][index2] = 1;
        adjacencyMatrix[index2][index1] = 1;
        adjcencyList[index1].push_back(index2);
        adjcencyList[index2].push_back(index1);
    }
}

void Graph ::dfs(string node)
{
    if (nodeIndexes.find(node) == nodeIndexes.end())
    {
        cout << "Node not found." << endl;
        return;
    }
    int startingVertex = nodeIndexes[node];
    vector<bool> visited(nodeIndexes.size(), false);
    cout << "DFS traversal: ";
    dfsRecursive(startingVertex, visited);
    cout << endl;
}

void Graph ::bfs(string node)
{
    if (nodeIndexes.find(node) == nodeIndexes.end())
    {
        cout << "Node not Found " << endl;
        return;
    }
    int startingVertex = nodeIndexes[node];
    vector<bool> visited(nodeIndexes.size(), false);
    queue<int> q;
    visited[startingVertex] = true;
    q.push(startingVertex);
    cout << " BFS Traversal : ";
    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();
        cout << getNodeName(currentNode) << " ";
        for (int neighbor : adjcencyList[currentNode])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main()
{
    Graph graph;
    int choice;
    string node1;
    string node2;

    while (true)
    {
        cout << "----------------Graph operation----------------------" << endl;
        cout << "1.Add Node." << endl;
        cout << "2.Add Edge." << endl;
        cout << "3.preform DFS." << endl;
        cout << "4.preform BFS." << endl;
        cout << "5.Exit." << endl;
        cout << "Enter your choice:";
        cin >> choice;

        switch (choice)
        {

        case 1:
            cout << "Enter the node name: ";
            cin >> node1;
            graph.addNode(node1);
            cout << "Node added: " << node1 << endl;
            break;

        case 2:
            cout << "Enter the first node: ";
            cin >> node1;
            cout << "Enter the second node: ";
            cin >> node2;
            graph.addEdge(node1, node2);
            cout << "Node added between" << node1 << " and " << node2;
            break;

        case 3:
            cout << "Enter the starting vertex for DFS: ";
            cin >> node1;
            graph.dfs(node1);
            break;

        case 4:
            cout << "Enter the starting vertex for BFS: ";
            cin >> node1;
            graph.bfs(node1);
            break;

        case 5:
            cout << " End of the program" << endl;
            break;

        default:
            cout << "invalid choice!" << endl;
        }
        cout << endl;
    }

    return 0;
}

