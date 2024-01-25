#include <bits/stdc++.h>
using namespace std;
const int N = 101;
const int INF = INT16_MAX;
int min(vector<int> &city)
{
    int min = INT_MAX;
    for (int i = 1; i <= city.size() - 1; i++)
    {
        if (city[i] < min)
        {
            min = city[i];
        }
    }
    return min;
}
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
void FloydWarshall(vector<vector<int>> &dis, int n, int thresholdCost, vector<int> &city)
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
    for (int i = 0; i <= n; i++)
    {
        int k = 0;
        for (int j = 1; j <= n; j++)
        {
            if (dis[i][j] == 0)
            {
                continue;
            }
            if (dis[i][j] <= thresholdCost)
            {
                city[i] = ++k;
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
    int thresholdCost;
    cin >> thresholdCost;
    vector<int> city(n + 1);

    FloydWarshall(dis, n, thresholdCost, city);
   // PrintDistanceArray(dis,n);
    int reachable = min(city);
    for (int i = 1; i <= n; i++)
    {
        if (city[i] == reachable)
        {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}