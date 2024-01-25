#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
class Person
{
public:
    int height, age;
    bool divorced;
    Person(int a, int b, bool c)
    {
        height = a;
        age = b;
        divorced = c;
    }
};
template <typename T, typename E>
class Graph
{
    int vertexNo, EdgeNo;
    vector<vector<pair<int, E>>> Adjacency;
    vector<vector<pair<int, E>>> ResidualGraph;
    map<T, E> adj;
    // map<Person, int> MBP;
    vector<bool> Visited;
    vector<int> parent;

public:
    Graph(vector<int> Allinfo,int taskCount,int workerCount,int totalCount)
    {
        vertexNo = totalCount+2;
        // EdgeNo = m;
        Adjacency.resize(vertexNo + 1);
        ResidualGraph.resize(vertexNo + 1);
        Visited.resize(vertexNo + 1);
        parent.resize(vertexNo + 1);
        // int menCount = Meninfo.size();
        // for (auto v : WomenInfo)
        // {
        //     Meninfo.push_back(v);
        // }
        // int totalCount = Meninfo.size();
        for (int i = 0; i < workerCount; i++)
        {
            Adjacency[1].push_back({i + 2, 1});
            ResidualGraph[1].push_back({i + 2, 1});
            ResidualGraph[i + 2].push_back({1, 0});
            for (int j = workerCount; j < totalCount; j++)
            {
                // Adjacency[j+2].push_back({totalCount+2,1});
                //if (IsMarriagePossible(Allinfo[i], Allinfo[j]))
                //{
                    // cout<<i<<" "<<j<<endl;
                    if(Allinfo[i]>=Allinfo[j])
                    {
                    Adjacency[i + 2].push_back({j + 2, 1});
                    ResidualGraph[i + 2].push_back({j + 2, 1});
                    ResidualGraph[j + 2].push_back({i + 2, 0});
                    }
                //}
            }
        }
        // cout<<IsMarriagePossible(Meninfo[1],Meninfo[3])<<endl;
        for (int j = workerCount; j < totalCount; j++)
        {
            Adjacency[j + 2].push_back({totalCount + 2, 1});
            ResidualGraph[j + 2].push_back({totalCount + 2,1});
            ResidualGraph[totalCount + 2].push_back({j + 2, 0});
        }

        // PrintAdjacencyList(Adjacency);
    }
    bool IsMarriagePossible(Person a, Person b)
    {
        int agediff = abs(a.age - b.age);
        int heightdiff = abs(a.height - b.height);
        if (agediff <= 5 && heightdiff <= 10 && (a.divorced == b.divorced))
        {
            // cout<<"Possible"<<endl;
            return true;
        }
        return false;
    }
    void AddEdge(int u, int v, E wt)
    {
        Adjacency[u].push_back({v, wt});
        ResidualGraph[u].push_back({v, wt});
        ResidualGraph[v].push_back({u, 0});
    }
    void Reset()
    {
        for (int i = 0; i < vertexNo +1; i++)
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
        // Visited[5]=false;
        parent[src] = -1;
        //  for(auto v:Visited)
        //     {
        //         cout<<v<<" ";
        //     }
        //    cout<< endl;
        while (!q.empty())
        {
            int u = q.front();
            // cout << u << "->" << endl;
            q.pop();
           
            for (auto neighbour : ResidualGraph[u])
            {
                // cout << neighbour.first << " " << Visited[neighbour.first] << " " << neighbour.second << endl;
                if ((!Visited[neighbour.first]) && (neighbour.second >= 1))
                {
                    if (neighbour.first == des)
                    {
                        parent[neighbour.first] = u;
                        return true;
                    }
                    // cout<<neighbour.first<<endl;
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
    int FordFulkerson(T src, T sink)
    {
        // vector<vector<pair<int, int>>> ResidualGraph;
        // ResidualGraph = Adjacency;
        // int src1 = adj[src];
        // int sink1 = adj[sink];
        int maxFlow = 0;
        // int max = -1444;
        // int index = 0;
        vector<pair<int, int>> ans;
        while (BFS(src, sink))
        {
            // PrintAdjacencyList(ResidualGraph);
              //PrintPath(src, sink);
            int path_flow = INT16_MAX;
            for (int v = sink; v != src; v = parent[v])
            {
                int u = parent[v];
                int tempflow = findValue(u, v);
                 //cout<<"tempFlow "<<tempflow<<endl;

                if (path_flow>tempflow)
                {

                    path_flow = tempflow;
                }
            }
            //cout<<"pathflow "<<path_flow<<endl;

            for (int v = sink; v != src; v = parent[v])
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
    int taskCount, workerCount;
    cin >> workerCount>>taskCount;
    int totalCount=taskCount+workerCount;
    vector<int>AllInfo;
    int strength;
    //bool divorced;
    for (int i = 0; i < totalCount; i++)
    {
        cin >> strength;
        // MenInfo.push_back({height, age, divorced});
        AllInfo.push_back(strength);
    }
    // for (int i = 0; i < m; i++)
    // {
    //     cin >> height >> age >> divorced;
    //     WomenInfo.push_back({height, age, divorced});
    // }
    Graph<int, int> G(AllInfo,taskCount,workerCount,totalCount);
    // G.PrintAdjacencyList();
    // string src, sink;
    // cin >> src >> sink;
    // // G.BFS(src, sink);
    // // G.PrintPath(src, sink);
    cout << G.FordFulkerson(1, totalCount+2);
    // pair<int, int> ans = G.maxflowFromVertex(sink);
    // cout << ans.second << " " << ans.first << endl;
    return 0;
}