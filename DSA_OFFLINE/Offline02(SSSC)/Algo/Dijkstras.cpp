#include <iostream>
#include <vector>
#include <queue>
#include <map>
#define INFINITY INT16_MAX
#define NIL -1
using namespace std;
vector<int> Key;
class compare
{

public:
    bool operator()(int a, int b)
    {
        return Key[a] > Key[b];
    }
};
template <typename T>
class Graph
{
public:
    int VertexNo, EdgeNo;
    vector<vector<pair<int, int>>> Adjacency;
    map<T, int> myMap;
    vector<int> Parent;
    vector<bool> Visited;
    vector<int> distance;
    // vector<int> Key;

    Graph(int n, int m)
    {
        VertexNo = n;
        EdgeNo = m;
        Adjacency.resize(VertexNo + 1);
        distance.resize(VertexNo + 1);
        Parent.resize(VertexNo + 1, -1);
        Visited.resize(VertexNo + 1, false);
        Key.resize(VertexNo + 1, INT16_MAX);
        int j = 1;
        for (int i = 0; i < EdgeNo; i++)
        {
            T u, v;
            int wt;
            cin >> u >> v >> wt;
            auto it = myMap.find(u);

            if (it == myMap.end())
            {
                // Key found
                myMap.insert({u, j++});
            }

            it = myMap.find(v);
            if (it == myMap.end())
            {
                myMap.insert({v, j++});
            }
            AddEdge(myMap[u], myMap[v], wt);
        }
    }
    void AddEdge(int u, int v, int wt)
    {
        Adjacency[u].push_back({v, wt});
         Adjacency[v].push_back({u, wt});
    }
    T findKeyByValue(const map<T, int> &myMap, const int &value)
    {
        for (const auto &pair : myMap)
        {
            if (pair.second == value)
            {
                return pair.first;
            }
        }
    }
    void INITIALIZE()
    {
        for (int i = 0; i < VertexNo + 1; i++)
        {
            distance[i] = INFINITY;
            Parent[i] = NIL;
        }
    }
    void RELAX(int u, pair<int, int> v, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> &Q)
    {
        if (distance[v.first] > (distance[u] + v.second))
        {
            distance[v.first] = distance[u] + v.second;
            Parent[v.first] = u;
            Q.push({distance[v.first], v.first});
        }
    }
    void Dijkstra(T src1)

    {
        int src = myMap[src1];
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        INITIALIZE();
        distance[src] = 0;
        Q.push({0, src});
        while (!Q.empty())
        {
            int u = Q.top().second;
            Q.pop();
            for (auto v : Adjacency[u])
            {
                RELAX(u, v, Q);
            }
        }
    }
    void Dijkstra(T src1, T des1)

    {
        int src = myMap[src1];
        int des = myMap[des1];
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        INITIALIZE();
        distance[src] = 0;
        Q.push({0, src});
        while (!Q.empty())
        {
            int u = Q.top().second;
            if (u == des)
            {
                cout << distance[des] << endl;
                exit(0);
            }
            Q.pop();
            for (auto v : Adjacency[u])
            {
                RELAX(u, v, Q);
            }
        }

        // PRINTING DISTANCE
        for (int i = 1; i < distance.size(); i++)
        {
            cout << distance[i] << " ";
        }
        cout << endl;

        // PRINTING PARENT

        for (int i = 1; i < Parent.size(); i++)
        {
            cout << Parent[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph<string> G(n, m);
    string src, des;
    cin >> src >> des;
    // G.PrimsAlogrithm(src);
    G.Dijkstra(src, des);
    cout << "Hello" << endl;

    return 0;
}
/*
5 8
A B 10
A C 3
B C 1
B D 5
C B 4
C E 6
D E 9
E D 9
A
*/