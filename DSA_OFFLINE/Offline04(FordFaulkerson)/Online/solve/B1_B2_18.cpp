#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
template <typename T, typename E>
class Graph
{
    int vertexNo, EdgeNo;
    vector<vector<pair<int, E>>> Adjacency;
    vector<vector<pair<int, E>>> ResidualGraph;
    map<T, int> adj;
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
        parent.resize(vertexNo + 1);
        int j = 1;
        for (int i = 1; i <= EdgeNo; i++)
        {
            E wt;
            T u, v;

            cin >> u >> v >> wt;
            int keyToCheck = 2;
            auto it = adj.find(u);

            if (it == adj.end())
            {
                // Key found
                adj.insert({u, j++});
            }

            it = adj.find(v);
            if (it == adj.end())
            {
                adj.insert({v, j++});
            }
            // adj.insert({u, i});
            // adj.insert({v, i + 1});
            AddEdge(adj[u], adj[v], wt);
        }
        // PrintAdjacencyList(Adjacency);
    }
    void AddEdge(int u, int v, E wt)
    {
        Adjacency[u].push_back({v, wt});
        ResidualGraph[u].push_back({v, wt});
        ResidualGraph[v].push_back({u, 0});
    }
    void Reset()
    {
        for (int i = 0; i < vertexNo + 1; i++)
        {
            Visited[i] = false;
        }
        // parent.resize(vertexNo + 1, -1);
    }
    bool BFS(int src, int des)
    {
        // cout<<"BFS Called"<<endl;
        Reset();
        queue<int> q;
        q.push(src);
        Visited[src] = true;
        parent[src] = -1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto neighbour : ResidualGraph[u])
            {
                if ((!Visited[neighbour.first]) && (neighbour.second > 0))
                {
                    if (neighbour.first == des)
                    {
                        parent[neighbour.first] = u;
                        return true;
                    }
                    q.push(neighbour.first);
                    parent[neighbour.first] = u;
                    Visited[neighbour.first] = true;
                }
            }
        }
        return false;
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
    void PrintAdjacencyList(vector<vector<pair<int, int>>> &Adjacency)
    {
        for (int i = 1; i < Adjacency.size(); i++)
        {
            cout << findKeyByValue(adj, i) << "-> ";
            for (int j = 0; j < Adjacency[i].size(); j++)
            {
                cout << "[" << findKeyByValue(adj, Adjacency[i][j].first) << "," << Adjacency[i][j].second << "] ";
            }
            cout << endl;
        }
        cout << "************" << endl;
    }
    T findKeyByValue(const map<T, E> &myMap, const int &value)
    {
        for (const auto &pair : myMap)
        {
            if (pair.second == value)
            {
                return pair.first;
            }
        }
    }
    static int min(int a, int b)
    {
        if (a < b)
            return a;
        else
            return b;
    }
    int findValue(int u, int v)
    {
        for (auto x : ResidualGraph[u])
        {
            if (x.first == v)
            {
                return x.second;
            }
        }
        return INT16_MAX;
    }
    void ChangeValue(int path_flow, int u, int v)
    {
        for (int i = 0; i < ResidualGraph[u].size(); i++)
        {
            if (ResidualGraph[u][i].first == v)
            {
                ResidualGraph[u][i].second -= path_flow;
            }
            // if(Adjacency[u][i].first==v)
            // {
            //     Adjacency[u][i].second-=path_flow;
            // }
        }
        for (int i = 0; i < ResidualGraph[v].size(); i++)
        {
            if (ResidualGraph[v][i].first == u)
            {
                // cout<<"HI"<<endl;
                ResidualGraph[v][i].second += path_flow;
                // return;
            }
        }
        // residualGraph[v].push_back({u,path_flow});
    }
    pair<int, int> maxflowFromVertex(T sink)
    {
        int max = INT16_MIN;
        int index = 0;
        for (int i = 0; i < ResidualGraph[adj[sink]].size(); i++)
        {
            if (ResidualGraph[adj[sink]][i].second > max)
            {
                max = ResidualGraph[adj[sink]][i].second;
                index = ResidualGraph[adj[sink]][i].first;
            }
        }
        return {max, index};
    }
    void DFS(int src)
    {
        // cout<<"DFS Called"<<endl;
        Visited[src] = true;
        for (auto neighbour : ResidualGraph[src])
        {
            if ((!Visited[neighbour.first]) && (neighbour.second > 0))
            {
                DFS(neighbour.first);
            }
        }
    }
    void MinCut(T s, T t)
    {
        int src=adj[s];
        int sink=adj[t];
        Reset();
        DFS(src);
        int maxflow=0;

        for (int i = 1; i <= vertexNo; i++)
        {
            for (auto &edge : Adjacency[i])
            {
                int v = edge.first;
                int capacity = edge.second;
                if ((Visited[i]) && (!Visited[v]) && (capacity > 0))
                {
                    maxflow+=capacity;
                    cout << findKeyByValue(adj,i) << " " << findKeyByValue(adj,v) << endl;
                }
            }
        }
        // vector<int> partion1;
        // vector<int> partion2;
        // for (int i = 1; i < Visited.size(); i++)
        // {
        //     if (Visited[i])
        //     {
        //         partion1.push_back(i);
        //     }
        //     else
        //     {
        //         partion2.push_back(i);
        //     }
        // }
        // // cout<<endl;
        // PrintPartion(partion1, partion2);
        cout<<maxflow<<endl;
    }
    void PrintPartion(vector<int> &partion1, vector<int> &partion2)
    {
        cout << "[";
        cout << "{";
        for (int i = 0; i < partion1.size(); i++)
        {
            cout << findKeyByValue(adj,partion1[i]);
            if (i != partion1.size() - 1)
            {
                cout << ",";
            }
        }
        cout << "},{";
        for (int i = 0; i < partion2.size(); i++)
        {
            cout <<findKeyByValue(adj,partion2[i]);
            if (i != partion2.size() - 1)
            {
                cout << ",";
            }
        }
        cout << "}]";
        cout << endl;
    }
    int FordFulkerson(T src, T sink)
    {
        // vector<vector<pair<int, int>>> ResidualGraph;
        // ResidualGraph = Adjacency;   
        int src1 = adj[src];
        int sink1 = adj[sink];
        int maxFlow = 0;
        // int max = -1444;
        // int index = 0;
        vector<pair<int, int>> ans;
        while (BFS(src1, sink1))
        {
            // PrintAdjacencyList(ResidualGraph);
            // PrintPath(src,sink);
            int path_flow = INT16_MAX;
            for (int v = sink1; v != src1; v = parent[v])
            {
                int u = parent[v];
                int tempflow = findValue(u, v);
                // cout<<"tempFlow "<<tempflow<<endl;

                if (path_flow > tempflow)
                {

                    path_flow = tempflow;
                }
            }

            for (int v = sink1; v != src1; v = parent[v])
            {
                int u = parent[v];
                ChangeValue(path_flow, u, v);
            }
           // PrintAdjacencyList(ResidualGraph);

            maxFlow += path_flow;
        }

        return maxFlow;
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Graph<string,int> G(n, m);
    // G.PrintAdjacencyList();
    string src, sink;
    cin >> src >> sink;
    // G.BFS(src, sink);
    // G.PrintPath(src, sink);
    G.FordFulkerson(src, sink);
    G.MinCut(src, sink);
    pair<int, int> ans = G.maxflowFromVertex(sink);
    return 0;
}
/*
6 10
s a 16
s c 13
a c 10
a b 12
b c 9
b t 20
c a 4
d b 7
d t 4
c d 14
s t
*/