#include <bits/stdc++.h>
using namespace std;
#define Infinity INT_MAX
#define NIL -1
const int N = 1e5 + 10;
vector<int> key;
vector<int> parent;
class Graph
{
public:
    vector<int> vertex;
    vector<vector<pair<int, int>>> adj;
    void resize(int n)
    {
        vertex.resize(n);
        adj.resize(n+1);
        
    }
};
class compare
{
public:
    bool operator()(int a, int b)
    {
        return key[a] > key[b];
    }
};
void MSTPrims(Graph G, int src)
{
    cout<<"INTO THE WILD"<<endl;
    key[src]=0;
    priority_queue<int, vector<int>, compare> Q;
    vector<bool> inQueue(G.vertex.size());
    for (int i = 0; i < G.vertex.size(); i++)
    {
        Q.push(i);
        inQueue[i] = true;
    }

    while (!Q.empty())
    {
        int u = Q.top();
        Q.pop();
        inQueue[u] = false;
        for (auto v : G.adj[u])
        {
            if (v.second < key[v.first] && inQueue[v.first] == true)
            {
                parent[v.first] = u;
                key[v.first] = v.second;
            }
        }
    }
}
int main()
{
    Graph G;
    int n, m;
    cin >> n >> m;
    G.resize(n);
    key.resize(n);
    parent.resize(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
       // cout<<"u: "<<u<<" v: "<<v<<" wt: "<<wt<<endl;
        G.adj[u].push_back(make_pair(v, wt));
         G.adj[v].push_back(make_pair(u, wt));
        //cout<<"HELLO"<<endl;
    }
   // cout<<"HIIIIIIIIIIIIIIIIIIIIIII"<<endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < G.adj[i].size(); j++)
        {
            cout << G.adj[i][j].first << ' ' << G.adj[i][j].second << endl;
        }
    }
     cout<<"HYYYYYYEEE"<<endl;
     for (int i = 0; i <n; i++)
    {
        // if (i == src)
        // {
        //     key[i] = 0;
        //     parent[i] = NIL;
        //     cout<<"key and parent declaring"<<endl;
        //     continue;
        // }
       // cout<<"key and parent declaring"<<endl;
        key[i] = Infinity;
        parent[i] = NIL;
        //cout<<"key and parent declaring"<<endl;
    }
    MSTPrims(G,0);
    cout<<"HYYYYYYEEE"<<endl;
    return 0;
}
/*
5 10
0 1 1
2 4 1
1 2 2
0 4 2
3 4 3
0 3 5
1 4 6
2 3 8
0 2 9
1 3 9
*/
