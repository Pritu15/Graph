
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
using namespace std;
class Edge
{
public:
    int src, des;
    int wt;
    Edge(int a, int b, int c)
    {
        src = a;
        des = b;
        wt = c;
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
    vector<Edge> allEdges;
    vector<bool> Visited;
    vector<int> rank;
    // vector<int> Key;

    Graph(int n, int m)
    {
        VertexNo = n;
        EdgeNo = m;
        Adjacency.resize(VertexNo + 1);
        rank.resize(VertexNo + 1);
        Parent.resize(VertexNo + 1, -1);
        Visited.resize(VertexNo + 1, false);
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
        allEdges.push_back({u, v, wt});
        allEdges.push_back({v, u, wt});
    }
    T findKeyByValue(const int &value)
    {
        for (const auto &pair : myMap)
        {
            if (pair.second == value)
            {
                return pair.first;
            }
        }
    }
    void Make_Set(int v)
    {

        Parent[v] = v;
        rank[v] = 0;
    }
    int findParent(int Node)
    {
        if (Parent[Node] == Node)
        {
            return Node;
        }
        return Parent[Node] = findParent(Parent[Node]);
    }
    void Union(int u1, int v1)
    {
        int u = findParent(u1);
        int v = findParent(v1);
        if (rank[u] < rank[v])
        {
            Parent[u] = v;
        }
        else if (rank[u] > rank[v])
        {
            Parent[v] = u;
        }
        else
        {
            Parent[v] = u;
            rank[u]++;
        }
    }
    static bool compare(Edge a, Edge b)
    {
        if (a.wt == b.wt && a.src == b.src)
        {
            return a.des < b.des;
        }
        if (a.wt == b.wt)
        {
            return a.src < b.src;
        }
        return a.wt < b.wt;
    }
    void PrintEdge(vector<Edge> &allEdges)
    {
        int i = 1;
        for (auto x : allEdges)
        {
            cout << i++ << ". src:" << findKeyByValue(x.src) << " des:" << findKeyByValue(x.des) << " wt:" << x.wt << endl;
        }
    }
    void KrusKal()
    {
        vector<Edge> MST;
        int minwt = 0;
        for (int i = 0; i < VertexNo + 1; i++)
        {
            Make_Set(i);
        }

        sort(allEdges.begin(), allEdges.end(), compare);

        for (auto v : allEdges)
        {
            if (findParent(v.src) != findParent(v.des))
            {
                minwt += v.wt;
                Union(v.src, v.des);
                MST.push_back(v);
            }
        }

        cout << minwt << endl;
        PrintEdge(MST);
        cout<<"Printing Parent array"<<endl;
        for(auto v: Parent)
        {
            cout<<v<<" ";
        }
        cout<<endl;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph<int> G(n, m);
    G.KrusKal();

    return 0;
}