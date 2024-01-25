#include <bits/stdc++.h>
using namespace std;
const int N = 101;
const int INF = 1e9;
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
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
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

    for (int k = 0; k <= n; k++)
    {
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    //Adian DID
    // for(int i=0;i<n;i++)
    // {
    //     for(int j=0;j<n;j++)
    //     {

       
    //     if(dis[i][j]+dis[j][i]<0)
    //     {
    //         cout<<"Yes"<<endl;
    //         exit(0);
    //     }
    //      }
    // }
    //What I Did
    for(int i=0;i<n;i++)
    {
        if(dis[i][i]<0)
        {
            cout<<"YES"<<endl;
            exit(0);
        }
    }
    // for (int i = 0; i <= n; i++)
    // {
    //     int k = 0;
    //     for (int j = 1; j <= n; j++)
    //     {
    //         if (dis[i][j] == 0)
    //         {
    //             continue;
    //         }
    //         if (dis[i][j] <= thresholdCost)
    //         {
    //             city[i] = ++k;
    //         }
    //     }
    // }
}
void PrintDistanceArray(vector<vector<int>> &dis, int n)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
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
       // dis[v][u] = wt;
    }
    int thresholdCost;
    //cin >> thresholdCost;
    vector<int> city(n + 1);

    FloydWarshall(dis, n);
    PrintDistanceArray(dis,n);
    cout<<"NO"<<endl;
    //  FloydWarshall(dis, n);
    // PrintDistanceArray(dis,n);
    // int reachable = min(city);
    // for (int i = 1; i <= n; i++)
    // {
    //     if (city[i] == reachable)
    //     {
    //         cout << i << " ";
    //     }
    // }
    // cout << endl;

    return 0;
}