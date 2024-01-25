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
void Initialize(vector<vector<int>> &dis,vector<vector<int>>&nextDestination, int n)
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
                nextDestination[i][j]=j;
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
            if(dis[i][j]==INF)
            {
                cout<<"INF"<<" ";
                continue;
            }
            cout << dis[i][j] << " ";
        }
        cout<<endl;
    }
    cout<<"**********"<<endl;
}
void FloydWarshall(vector<vector<int>> &dis, int n,vector<vector<int>>& nextDestination)
{

    for (int k = 1; k <=n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if(dis[i][k]!=INF&&dis[k][j]!=INF)
                {
                dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
                if(dis[i][j]>dis[i][k]+dis[k][j])
                {
                    nextDestination[i][j]=k;
                }
                }
            }
        }
        PrintDistanceArray(dis,n);
        
    }
}
int ans(int w1,int w2,int s,int d,vector<vector<int>>&dis)
{
    int cost=min(dis[s][w1]+dis[w1][w2]+dis[w2][d],dis[s][w2]+dis[w1][d]+dis[w2][w1]);
    return cost;

}
void printPaths(vector<vector<int>>& nextDestination,int src,int des)
{
    int u=nextDestination[src][des];
    if(u==-1)
    {
        return;
    }
    while(u!=des)
    {
        cout<<u<<"->";
        u=nextDestination[u][des];
    }

}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> nextDestination(n + 1, vector<int>(n + 1, -1));

    Initialize(dis,nextDestination, n);

    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        dis[u][v] = wt;
       // nextDestination[u][v]=v;
        dis[v][u] = wt;
    }

    FloydWarshall(dis, n,nextDestination);
    vector<pair<int,int>>wallStreet;
    PrintDistanceArray(nextDestination,n);
    int x,y;
    while(cin>>x>>y)
    {
        if(x==-1&&y==-1)
        {
            break;
        }
        // if(dis[x][y]==INF)
        // {
        //     cout<<"No path from "<<x<<" to "<<y<<" through the Wall Street"<<endl;
        //     continue;
        // }
        // cout<<dis[y][x]<<endl;
        wallStreet.push_back({x,y});

    }
    
    for(int i=0;i<wallStreet.size();i++)
    {
        if(dis[wallStreet[i].first][wallStreet[i].second]==INF)
        {
            cout<<"No path from "<<wallStreet[i].first<<" to "<<wallStreet[i].second<<" through the Wall Street"<<endl;
            continue;
        }
        cout<<ans(wallStreet[0].first,wallStreet[0].second,wallStreet[i].first,wallStreet[i].second,dis)<<endl;
        printPaths(nextDestination,wallStreet[i].first,wallStreet[0].first);
    }
   // PrintDistanceArray(dis,n);
   

    return 0;
}