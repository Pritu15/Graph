#include <bits/stdc++.h>
using namespace std;
const int INF = INT16_MAX;
void Initialize(vector<vector<int>> &dis, int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (i == j)
            {
                dis[i][j] = 0;
            }
            else
            {
                dis[i][j] = INF;
            }
        }
    }
}
void FloydWarshall(vector<vector<int>> &dis, int n)
{

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
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
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1, 0));
    Initialize(dis, n);

    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        dis[u][v] = wt;
        dis[v][u] = wt;
    }
    FloydWarshall(dis, n);
    PrintDistanceArray(dis,n);

    return 0;
}