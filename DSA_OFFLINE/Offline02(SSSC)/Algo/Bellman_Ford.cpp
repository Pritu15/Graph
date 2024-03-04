#include <bits/stdc++.h>
using namespace std;
class Edge
{
public:
    int src, des, wt;
    Edge(int a, int b, int c)
    {
        src = a;
        des = b;
        wt = c;
    }
};
int bellmanFord(int n, int m, int src, int des, vector<Edge> &adj)
{
    vector<int> distance(n + 1, 1e9);
    distance[src] = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = adj[j].src;
            int v = adj[j].des;
            int wt = adj[j].wt;
            if (distance[u] != 1e5 && ((distance[u] + wt) < distance[v]))
            {
                distance[v] = distance[u] + wt;
            }
        }
    }
    bool flag = 0;
    for (int j = 0; j < m; j++)
    {
        int u = adj[j].src;
        int v = adj[j].des;
        int wt = adj[j].wt;
        if (distance[u] != 1e5 && ((distance[u] + wt) < distance[v]))
        {
            flag = 1;
        }
    }
    if (flag)
    {
        return -404;
    }
    return distance[des];
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> adj;
    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj.push_back(Edge(u, v, wt));
        adj.push_back(Edge(v, u, wt));
    }
    int src, des;
    cin >> src >> des;
    int distance = bellmanFord(n, m, src, des, adj);
    cout << "Answer is: " << distance << endl;

    return 0;
}