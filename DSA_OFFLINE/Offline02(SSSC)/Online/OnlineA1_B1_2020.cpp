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
int bellmanFord(int n,int m,int src,int des,vector<Edge>& adj,vector<int>&child)
{
    vector<int>distance(n+1,INT_MAX);
    child.resize(n,-1);
    distance[src]=0;
    child[src]=-1;
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
                child[v]=u;
            }
        }
    }
    // while(child[des]!=src)
    // {
    //     cout<<child[des]<<"->";
    //     des=child[des];

    // }
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
vector<int> bellmanFord1(int n,int m,int src,vector<Edge>& adj)
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
    // bool flag=0;
    //     for(int j=0;j<m;j++)
    //     {
    //         int u=adj[j].src;
    //         int v=adj[j].des;
    //         int wt=adj[j].wt;
    //         if(distance[u]!=INT_MAX&&((distance[u]+wt)<distance[v]))
    //         {
    //            flag=1;
    //         }
    //     }
    //     if(flag)
    //     {
    //         return -404;
    //     }
    return distance;
}

void print(int src,int des,vector<int>& child)
{
    vector<int> path;
    for(int i=des;i!=-1;i=child[i])
    {
        path.push_back(i);
    }
    for(int i=path.size()-1;i>=0;i--)
    {
        cout<<path[i];
        if(i!=0)
        {
            cout<<"->";
        }
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<Edge> adj;
    //vector<vector<pair<int, int>>> adj1(m+1);
    for(int i=0;i<m;i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        adj.push_back(Edge(u,v,wt));
        //adj1[u].push_back({v,wt});

    }
    // int u,v;
    // cin>>u>>v;
    // int low,high;
    // cin>>low>>high;
    int src,des;
    cin>>src;
    // int minDistance=1e5;
    // for(int i=low;i<=high;i++)
    // {
    //     int temp=bellmanFord(n,m,src,des,adj);
    // }
    vector<int> ansdis=bellmanFord1(n,m,src,adj);
    //cout<<"*******Distance from the src to other vertex******"<<endl;
    // for(int i=0;i<ansdis.size()-1;i++)
    // {
    //     cout<<i<<"->"<<ansdis[i]<<endl;
    // }
   // cout<<"HERE"<<endl;
    vector<int>ansdis1;
    vector<int> child;
    for(int i=0;i<n;i++)
    {
        ansdis1.push_back(bellmanFord(n,m,i,src,adj,child));
        //cout<<"HI"<<endl;

    }
     //cout<<"*******Distance from the other vertex to src******"<<endl;
    // for(int i=0;i<ansdis1.size()-1;i++)
    // {
    //     cout<<i<<"->"<<ansdis1[i]<<endl;
    // }
    //int distance=bellmanFord(n,m,src,des,adj);
    int min=INT_MAX;
    int index=0;
    for(int i=0;i<n;i++)
    {
        //cout<<i<<"->"<<ansdis1[i]+ansdis[i]<<endl;
        if(i==src)
        {
            continue;
        }
        if(ansdis1[i]+ansdis[i]<min)
        {
            min=ansdis1[i]+ansdis[i];
            index=i;
        }

    }
    cout<<"Minimum total time: "<<min<<endl;
   // cout<<index<<endl;
    int value=bellmanFord(n,m,src,index,adj,child);
    print(src,index,child);
    cout<<" (time: "<<value<<" )";
    cout<<endl;
    bellmanFord(n,m,index,src,adj,child);
    print(index,src,child);
    cout<<" (time: "<<bellmanFord(n,m,index,src,adj,child)<<" )";

    // SSSC1(adj1,n,src,index);
    // SSSC1(adj1,n,index,src);
    //cout<<"Answer is: "<<distance<<endl;
    //int distemp=bellmanFord(n,m,src,u,adj);
   // cout<<"Answer is: "<<distemp<<endl;
    // int distance1=bellmanFord(n,m,v,u,adj);
    // if(distance1==INT_MAX)
    // {
    //     distance1=low;
    // }
   
    // else {
    //     distance1=-distance1;

    // }
    // if(distance1<low)
    // {
    //     distance1=low;
    // }
    //   if(distance1>high)
    // {
    //      cout<<"Impossible"<<endl;
    //     exit(0);
    // }
    // // cout<<"Answer is: "<<distance1<<endl;
    // adj.push_back(Edge(u,v,distance1));
    // // for(int i=0;i<adj.size();i++)
    // // {
    // //     cout<<adj[i].src<<" "<<adj[i].des<<" "<<adj[i].wt<<endl;
    // // }
    // int ans=bellmanFord(n,m+1,src,des,adj);
    // if(ans==distance)
    // {
    //     cout<<"Impossible"<<endl;
    //     exit(0);
    // }
    // cout<<distance1<<" "<<ans<<endl;




    return 0;
}