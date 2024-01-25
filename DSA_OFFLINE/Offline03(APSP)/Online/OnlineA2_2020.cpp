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
void Initialize(vector<vector<double>> &dis, int n)
{
    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < n ; j++)
        {
            if (i == j)
            {
                dis[i][j] = 1;
            }
            else
            {
                dis[i][j] = INF;
            }
        }
    }
}
void FloydWarshall(vector<vector<double>> &dis, int n)
{

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <n; j++)
            {
                // if(min(dis[i][j],dis[i][k]*dis[k][j])>INF)
                // {
                //     dis[i][j] = INF;
                //     continue;

                // }
            //    if(i==j)
            //     {
            //          // dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            //         continue;
            //     }
            //     else
                // {
                    dis[i][j]=min(dis[i][j],dis[i][k]*dis[k][j]);
                // }
            }
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
void PrintDistanceArray(vector<vector<double>> &dis, int n)
{
    for (int i = 0; i <= n-1; i++)
    {
        for (int j = 0; j <= n-1; j++)
        {
            if(dis[i][j]==INF)
            {
                cout<<"INF"<<" ";
                continue;
            }
            cout << dis[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<double>> dis(n + 1, vector<double>(n + 1, 0.0));
    Initialize(dis, n);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        double wt;
        cin>>u>>wt>>v;
        dis[u][v] = wt;
        //cout<<dis[u][v]<<endl;
        //dis[v][u] = 1/wt;
    }
    int thresholdCost;
   // cin >> thresholdCost;
    //vector<int> city(n + 1);

    FloydWarshall(dis, n);
    PrintDistanceArray(dis,n);
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