#include <iostream>
#include <vector>
using namespace std;
#define WHITE 1
#define GRAY 2
#define BLACK 3

void DFS(int source, vector<int> &color, vector<vector<int>> &adj)
{
    color[source] = GRAY;
    for (auto v : adj[source])
    {
        if (color[v] == WHITE)
        {

            DFS(v, color, adj);
        }
        else if (color[v] == GRAY)
        {
            cout << "Cycle Detected" << endl;
            exit(0);
        }
    }
    color[source] = BLACK;
}
int main()
{
    vector<vector<int>> adj;
    vector<int> parent;
    vector<int> color;

    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    color.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
    {
        color[i] = WHITE;
    }
    for (int i = 1; i <= n; i++)
    {
        DFS(i, color, adj);
    }
    cout << "NO Cycle Detected" << endl;
    return 0;
}