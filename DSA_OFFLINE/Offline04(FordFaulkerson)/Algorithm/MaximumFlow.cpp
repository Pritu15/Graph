#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Edge
{
    int src, des, capacity;

public:
    int flow = 0;
    Edge(int a, int b, int c)
    {
        src = a;
        des = b;
        capacity = c;
    }
};
class Graph
{
    int VertexNo, EdgeNo;
    vector<vector<pair<int, int>>> adj;
    vector<Edge> Adjacency;
    vector<bool> Visited;
    vector<int>path;

public:
    Graph(int n, int m)
    {
        VertexNo = n;
        EdgeNo = m;
        adj.resize(n + 1);
        Visited.resize(VertexNo + 1, false);
        for (int i = 0; i < m; i++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            AddDirectedEdge(x, y, z);
        }
        SortEdges();
    }
    void AddDirectedEdge(int u, int v, int capacity)
    {
        adj[u].push_back({v, capacity});
        Adjacency.push_back(Edge(u, v, capacity));
    }
    void AddUnDirectedEdge(int u, int v, int capacity)
    {
        adj[u].push_back({v, capacity});
        adj[v].push_back({u, capacity});
    }
    static bool compareWeights(pair<int, int> a,pair<int, int> b)
    {
        return a.second > b.second;
    }
    void SortEdges()
    {
        for (int i = 0; i < adj.size(); ++i)
        {
            sort(adj[i].begin(), adj[i].end(), compareWeights);
        }
    }

    void PrintAdjacencyList()
    {
        for (int i = 1; i < adj.size(); i++)
        {
            cout << i << "-> ";
            for (int j = 0; j < adj[i].size(); j++)
            {
                cout << "[" << adj[i][j].first << "," << adj[i][j].second << "] ";
            }
            cout << endl;
        }
    }
    void DFS(int source,int des)
    {
        Visited[source] = true;
        path.push_back(source);
        for (auto v : adj[source])
        {
            if (!Visited[v.first])
            {
                if(v.first==des)
                {
                    return;
                }
                DFS(v.first,des);
            }
        }
    }
    void ResidualGraph()
    {
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Graph G(n, m);
    G.PrintAdjacencyList();
    return 0;
}