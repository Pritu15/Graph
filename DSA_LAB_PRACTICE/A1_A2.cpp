#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
template <typename T, typename E>
class Graph
{
    int vertexNo, EdgeNo;
    vector<vector<int>> Adjacency;
    vector<vector<pair<int, E>>> ResidualGraph;
    vector<int> distance;
    map<T, E> adj;
    vector<bool> Visited;
    vector<int> parent;

public:
    Graph(int n, int m)
    {
        vertexNo = n;
        EdgeNo = m;
        Adjacency.resize(vertexNo + 1);
        ResidualGraph.resize(vertexNo + 1);
        Visited.resize(vertexNo + 1);
        distance.resize(vertexNo + 1);
        parent.resize(vertexNo + 1);
        int j = 1;
        for (int i = 1; i <= EdgeNo; i++)
        {
            int u,v;
            cin>>u>>v;
            AddEdge(u,v);
        }
         // PrintAdjacencyList(Adjacency);
    }
    void AddEdge(int u, int v)
    {
        Adjacency[u].push_back(v);
        Adjacency[v].push_back(u);
        // ResidualGraph[u].push_back({v, wt});
        // ResidualGraph[v].push_back({u, 0});
    }
    void Reset()
    {
        for (int i = 0; i < vertexNo + 1; i++)
        {
            Visited[i] = false;
        }
        // parent.resize(vertexNo + 1, -1);
    }
    void BFS(int src)
    {
        // cout<<"BFS Called"<<endl;
        Reset();
        queue<int> q;
        q.push(src);
        Visited[src] = true;
        distance[src] = 1;
        parent[src] = -1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto neighbour : Adjacency[u])
            {
                if ((!Visited[neighbour]))
                {
                    distance[neighbour] = distance[u] + 1;
                    q.push(neighbour);
                    parent[neighbour] = u;
                    Visited[neighbour] = true;
                }
            }
        }
        // return false;
    }
    void PrintPath(int src, int sink)
    {
        vector<int> paths;

        int v = parent[sink];
        paths.push_back(sink);
        while (v != src)
        {
            paths.push_back(v);
            v = parent[v];
        }
        paths.push_back(src);
        for (int i = paths.size() - 1; i >= 0; i--)
        {
            cout << paths[i];
            if (i != 0)
            {
                cout << "->";
            }
        }
        cout << endl;
    }
    void PrintAdjacencyList(vector<vector<int>> &Adjacency)
    {
        for (int i = 1; i < Adjacency.size(); i++)
        {
            cout << i<< "-> ";
            for (int j = 0; j < Adjacency[i].size(); j++)
            {
                cout <<Adjacency[i][j]<< ",";
            }
            cout << endl;
        }
        cout << "************" << endl;
    }
    T findKeyByValue(const map<T, E> &myMap, const E &value)
    {
        for (const auto &pair : myMap)
        {
            if (pair.second == value)
            {
                return pair.first;
            }
        }
    }
    void ans(vector<pair<int,int>>& EdgePair)
    {
        vector<int> diff;
        pair<int,int>Edge;
        int min=INT16_MAX;
        for(auto v:EdgePair)
        {
            if(min>distance[v.first]+1){
                min=distance[v.first]+1;
                //cout<<min<<endl;
                Edge=v;
            }
        }
        cout<<Edge.first<<" "<<Edge.second<<endl;
        cout<<min<<endl;

    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Graph<int, int> G(n, m);
    G.BFS(1);
    int Q;
    cin>>Q;
    vector<pair<int,int>>EdgePair;
    int u,v;
    for(int i=0;i<Q;i++)
    {
        cin>>u>>v;
        EdgePair.push_back({u,v});
    }
    
    G.ans(EdgePair);

    // G.PrintAdjacencyList();

    // G.BFS(src, sink);
    // G.PrintPath(src, sink);

    return 0;
}