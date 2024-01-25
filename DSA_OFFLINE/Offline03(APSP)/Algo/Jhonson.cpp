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
    vector<vector<pair<int, int>>> johsonAdj;
    map<T, int> myMap;
    vector<int> Parent;
    vector<bool> Visited;
    vector<int> distance;
    vector<vector<int>> d;
    // vector<int> Key;

    Graph(int n, int m, T te)
    {
        VertexNo = n;
        EdgeNo = m;
        Adjacency.resize(VertexNo + 1);
        johsonAdj.resize(VertexNo + 2);

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
            cout << "Found the Value" << endl;
            cout << myMap[u] << " " << myMap[v] << " " << wt << endl;
            AddEdge(myMap[u], myMap[v], wt);
        }
        myMap.insert({te, j});
        for (int i = 1; i <= VertexNo; i++)
        {
            johsonAdj[j].push_back({i, 0});
        }
        VertexNo = n + 1;
        EdgeNo = m + n;
        distance.resize(VertexNo + 1);
        d.resize(VertexNo + 1, vector<int>(VertexNo + 1, 0));
        Parent.resize(VertexNo + 1, -1);
        Visited.resize(VertexNo + 1, false);
        Key.resize(VertexNo + 1, INT16_MAX);
        PrintAdjacencyList(johsonAdj);
    }
    void AddEdge(int u, int v, int wt)
    {
        cout << "ENTERED THE ADD EDGE FUNCTION" << endl;
        Adjacency[u].push_back({v, wt});
        cout << "ADDED IN THE ADJACENCY" << endl;
        johsonAdj[u].push_back({v, wt});
        cout << "ADDING EDGE" << endl;
        // Adjacency[v].push_back({u, wt});
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
    void RELAX(int u, pair<int, int> v)
    {
        if (distance[v.first] > (distance[u] + v.second))
        {
            distance[v.first] = distance[u] + v.second;
            Parent[v.first] = u;
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
    void bellmanFord(int src)
    {
        // int src = myMap[src1];
        // int des=myMap[des1];
        INITIALIZE();
        distance[src] = 0;
        for (int i = 1; i < VertexNo + 1; i++)
        {
            for (int i = 1; i < johsonAdj.size(); i++)
            {
                for (int j = 0; j < johsonAdj[i].size(); j++)
                {
                    RELAX(i, johsonAdj[i][j]);
                }
            }
        }
        // cout<<distance[des]<<endl;

        // for (int i = 1; i < Ad.size(); i++)
        // {
        //     for (int j = 0; j < Adjacency[i].size(); j++)
        //     {
        //         RELAX(i, Adjacency[i][j]);
        //         if (distance[Adjacency[i][j].first] > (distance[i] + Adjacency[i][j].second))
        //         {
        //             cout << "Neg_Cycle" << endl;
        //         }
        //     }
        // }
    }
    void changeAdjacency()
    {
        for (int i = 1; i < johsonAdj.size(); i++)
        {
            for (int j = 0; j < johsonAdj[i].size(); j++)
            {
                johsonAdj[i][j].second = distance[i] + johsonAdj[i][j].second - distance[johsonAdj[i][j].first];
            }
        }
    }
    void Dijkstra(int src)

    {
        // int src=myMap[src1];
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
        INITIALIZE();
        distance[src] = 0;
        Q.push({0, src});
        while (!Q.empty())
        {
            int u = Q.top().second;
            Q.pop();
            for (auto v : johsonAdj[u])
            {
                RELAX(u, v, Q);
            }
        }

        // PRINTING DISTANCE
        //  for(int i=1;i<distance.size();i++)
        //  {
        //      cout<<distance[i]<<" ";

        // }
        // cout<<endl;

        // PRINTING PARENT

        // for(int i=1;i<Parent.size();i++)
        // {
        //     cout<<Parent[i]<<" ";
        // }
        // cout<<endl;
    }

    void JohsonAlgorithm()
    {
        bellmanFord(VertexNo);
        changeAdjacency();
        PrintAdjacencyList(johsonAdj);
       // cout << "johsonAlgo" << endl;

        for (int i = 1; i < VertexNo; i++)
        {
            Dijkstra(i);
            for (int j = 1; j < VertexNo; j++)
            {
                d[i][j] = distance[j];
            }
        }
        PrintDistanceArray(d, VertexNo - 1);
    }
    void PrintAdjacencyList(vector<vector<pair<int, int>>> &Adjacency)
    {
        for (int i = 1; i < Adjacency.size(); i++)
        {
            cout << findKeyByValue(myMap, i) << "-> ";
            for (int j = 0; j < Adjacency[i].size(); j++)
            {
                cout << "[" << findKeyByValue(myMap, Adjacency[i][j].first) << "," << Adjacency[i][j].second << "] ";
            }
            cout << endl;
        }
        cout << "************" << endl;
    }
    void PrintDistanceArray(vector<vector<int>> &dis, int n)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cout << dis[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph<string> G(n, m, "s");
    int src, des;
    // cin >> src;
    //  G.PrimsAlogrithm(src);
    //  G.Dijkstra(src, des);
    // G.bellmanFord(src);
    G.JohsonAlgorithm();
    cout << "Hello" << endl;

    return 0;
}
/*
5 6
0 1 4
0 4 1
2 1 7
2 3 -2
3 1 1
4 3 -5
*/

/*
 4 4
 1 2 3
 2 3 1
 2 4 4
 3 4 1
 4
*/

/*
5 8
a b 3
a c 8
a e -4
b e 7
c b 4
d a 2
d c -5
e d 6
johsonAlgo
0 2 2 0 2
14 0 12 10 12
14 0 0 10 12
4 2 2 0 2
2 0 0 2 0
*/