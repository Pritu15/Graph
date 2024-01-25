#include<bits/stdc++.h>
using namespace std;
class Edge{
    public:
    int src,des,wt;
    Edge(int a,int b,int c)
    {
        src=a;
        des=b;
        wt=c;
    }
};
int bellmanFord(int n,int m,int src,int des,vector<Edge>& adj)
{
    vector<int>distance(n+1,INT_MAX);
    distance[src]=0;
    for(int i=1;i<=n-1;i++)
    {
        for(int j=0;j<m;j++)
        {
            int u=adj[j].src;
            int v=adj[j].des;
            int wt=adj[j].wt;
            if(distance[u]!=INT_MAX&&((distance[u]+wt)<distance[v]))
            {
                distance[v]=distance[u]+wt;
            }
        }
    }
    bool flag=0;
        for(int j=0;j<m;j++)
        {
            int u=adj[j].src;
            int v=adj[j].des;
            int wt=adj[j].wt;
            if(distance[u]!=INT_MAX&&((distance[u]+wt)<distance[v]))
            {
               flag=1;
            }
        }
        if(flag)
        {
            return -404;
        }
    return distance[des];
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<Edge> adj;
    for(int i=0;i<m;i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        adj.push_back(Edge(u,v,wt));

    }
    int u,v;
    cin>>u>>v;
    int low,high;
    cin>>low>>high;
    int src,des;
    cin>>src>>des;
    // int minDistance=1e5;
    // for(int i=low;i<=high;i++)
    // {
    //     int temp=bellmanFord(n,m,src,des,adj);
    // }
    int distance=bellmanFord(n,m,src,des,adj);
    //cout<<"Answer is: "<<distance<<endl;
    //int distemp=bellmanFord(n,m,src,u,adj);
   // cout<<"Answer is: "<<distemp<<endl;
    int distance1=bellmanFord(n,m,v,u,adj);
    if(distance1==INT_MAX)
    {
        distance1=low;
    }
   
    else {
        distance1=-distance1;

    }
    if(distance1<low)
    {
        distance1=low;
    }
      if(distance1>high)
    {
         cout<<"Impossible"<<endl;
        exit(0);
    }
    // cout<<"Answer is: "<<distance1<<endl;
    adj.push_back(Edge(u,v,distance1));
    // for(int i=0;i<adj.size();i++)
    // {
    //     cout<<adj[i].src<<" "<<adj[i].des<<" "<<adj[i].wt<<endl;
    // }
    int ans=bellmanFord(n,m+1,src,des,adj);
    if(ans==distance)
    {
        cout<<"Impossible"<<endl;
        exit(0);
    }
    cout<<distance1<<" "<<ans<<endl;




    return 0;
}