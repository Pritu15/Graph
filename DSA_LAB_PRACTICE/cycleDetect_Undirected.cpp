#include <iostream>
#include <vector>
using namespace std;
#define WHITE 1
#define GRAY 2
#define BLACK 3

void DFS(int source, vector<vector<int>> &adj, vector<int> &color, vector<int> &parent)
{
    color[source] = GRAY;
    for (auto v : adj[source])
    {
        if (color[v] == WHITE)
        {
            parent[v] = source;
            DFS(v, adj, color, parent);
        }
        else if (color[v] == GRAY && parent[source] != v)
        {
            cout << "YES" << endl;
            cout << source << " " << v << endl;
            exit(0);
        }
    }
    color[source] = BLACK;
}
int main()
{

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> parent(n + 1);
    vector<int> color(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
    }
    for (int i = 1; i <= n; i++)
    {
        DFS(i, adj, color, parent);
    }
    cout << "NO" << endl;
    return 0;
}