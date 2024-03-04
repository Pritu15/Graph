#include <iostream>
#include <vector>
#include <queue>
#include <map>
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
    // vector<int> Key;

    Graph(int n, int m)
    {
        VertexNo = n;
        EdgeNo = m;
        Adjacency.resize(VertexNo + 1);
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
    void PrimsAlogrithm(T src1)
    {
        int src = myMap[src1];
        int minwt = 0;
        Key[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Queue;
        Queue.push({0, src});
        while (!Queue.empty())
        {
            int u = Queue.top().second;
            int wt = Queue.top().first;
            Queue.pop();
            if (Visited[u])
            {
                continue;
            }
            minwt += wt;
            Visited[u] = true;
            for (auto v : Adjacency[u])
            {
                if ((v.second < Key[v.first]) && !Visited[v.first])
                {
                    Parent[v.first] = u;
                    Key[v.first] = v.second;
                    Queue.push({Key[v.first], v.first});
                }
            }
        }
        cout << minwt << endl;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph<int> G(n, m);
    int src;
    cin >> src;
    G.PrimsAlogrithm(src);
    // cout << "Hello" << endl;

    return 0;
}