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
    map<T, E> adj;
    vector<bool> Visited;
    vector<int> parent;

public:
//Time Complexity: O(m)
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
    //Time Complexity: O(1)
    void AddEdge(int u, int v, E wt)
    {
        Adjacency[u].push_back({v, wt});
        ResidualGraph[u].push_back({v, wt});
        ResidualGraph[v].push_back({u, 0});
    }
    //Time Complexity: O(V)

    void Reset()
    {
        for (int i = 0; i < vertexNo + 1; i++)
        {
            Visited[i] = false;
        }
        // parent.resize(vertexNo + 1, -1);
    }
    //Time Complexity: O(V + E)
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
    //Time Complexity: O(V)
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
    //Time Complexity: O(V + E)
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
    //Time Complexity: O(V)
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
    //Time Complexity: O(1)
    static int min(int a, int b)
    {
        if (a < b)
            return a;
        else
            return b;
    }
   // Time Complexity: O(E)
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
    //Time Complexity: O(E)
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


   // Time Complexity: O(V * E)
    pair<int, int> maxflowFromVertex(T src1,T sink1)
    {
         int src = adj[src1];
        int sink = adj[sink1];
        int max = INT16_MIN;
        int index = 0;
        for (int i = 1; i < ResidualGraph.size(); i++)
        {
            for(int j=0;j<ResidualGraph[i].size();j++)
            {
            if (ResidualGraph[i][j].second > max)
            {
                if(ResidualGraph[i][j].first!=src && ResidualGraph[i][j].first!=sink)
                {
                max = ResidualGraph[i][j].second;
                index = ResidualGraph[i][j].first;
                }
            }
            }
        }
        return {max, index};
    }
    //Time Complexity: O(m * V * E)
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
    Graph<string, int> G(n, m);
    // G.PrintAdjacencyList();
    string src, sink;
    cin >> src >> sink;
    // G.BFS(src, sink);
    // G.PrintPath(src, sink);
    G.FordFulkerson(src, sink);
    pair<int, int> ans = G.maxflowFromVertex(src,sink);
    cout << ans.second << " " << ans.first << endl;
    return 0;
}