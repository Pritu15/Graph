#include <iostream>
#include <vector>
#include <queue>
#include<map>
using namespace std;
template<typename T>class Graph
{
    int vertexNo, EdgeNo;
    vector<vector<pair<int, int>>> Adjacency;
    vector<vector<pair<int, int>>> ResidualGraph;
    map<T,int> adj;
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
        for (int i = 0; i < EdgeNo; i++)
        {
            int u, v, wt;
            cin >> u >> v >> wt;
            AddEdge(u, v, wt);
        }
        // PrintAdjacencyList(Adjacency);
    }
    void AddEdge(int u, int v, int wt)
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
            cout << i << "-> ";
            for (int j = 0; j < Adjacency[i].size(); j++)
            {
                cout << "[" << Adjacency[i][j].first << "," << Adjacency[i][j].second << "] ";
            }
            cout << endl;
        }
        cout<<"************"<<endl;
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
    pair<int,int> maxflowFromVertex(int sink)
    {
        int max=INT16_MIN;
        int index=0;
        for(int i=0;i<ResidualGraph[sink].size();i++)
        {
            if(ResidualGraph[sink][i].second>max)
            {
                max=ResidualGraph[sink][i].second;
                index=ResidualGraph[sink][i].first;

            }

        }
        return {max,index};


    }
    int FordFulkerson(int src, int sink)
    {
        // vector<vector<pair<int, int>>> ResidualGraph;
        // ResidualGraph = Adjacency;
        int maxFlow = 0;
        // int max = -1444;
        // int index = 0;
        vector<pair<int, int>> ans;
        while (BFS(src, sink))
        {
           // PrintAdjacencyList(ResidualGraph);
            //PrintPath(src,sink);
            int path_flow = INT16_MAX;
            for (int v = sink; v != src; v = parent[v])
            {
                int u = parent[v];
                int tempflow = findValue(u, v);
                //cout<<"tempFlow "<<tempflow<<endl;

                if (path_flow > tempflow)
                {
                   // ans.push_back({tempflow,u});
                    // if (path_flow > max)
                    // {
                    //     index = u;
                    //     max = path_flow;
                    // }
                    path_flow = tempflow;
                }
                // path_flow = min(path_flow, findValue(ResidualGraph, u, v));
            }
            // cout<<"pathFlow "<<path_flow<<endl;
            for (int v = sink; v != src; v = parent[v])
            {
                int u = parent[v];
                ChangeValue(path_flow, u, v);
            }
              PrintAdjacencyList(ResidualGraph);

            maxFlow += path_flow;
        }
        // int maximum=-14444;
        // for(int i=0;i<ans.size();i++)
        // {
        //     cout<<ans[i].first<<" "<<ans[i].second<<endl;
        //     if(ans[i].first>maximum)
        //     {
        //         index=ans[i].second;
        //         maximum=ans[i].first;
        //     }

        // }
        // cout << index << " ";
        // cout<<maximum<<" ";
        //PrintAdjacencyList(Adjacency);
        return maxFlow;
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Graph<int> G(n, m);
    // G.PrintAdjacencyList();
    int src, sink;
    cin >> src >> sink;
    // G.BFS(src, sink);
    // G.PrintPath(src, sink);
    G.FordFulkerson(src, sink);
    pair<int,int> ans=G.maxflowFromVertex(sink);
    cout<<ans.second<<" "<<ans.first<<endl;
    return 0;
}