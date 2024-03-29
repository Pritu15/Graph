#include<bits/stdc++.h>
using namespace std;
void makeSet(vector<int>& parent,vector<int>& rank,int n)
{
    for(int i=0;i<n;i++)
    {
        parent[i]=i;
        rank[i]=0;
    }
    
}
int findParent(vector<int>& parent,int Node)
{
    if(parent[Node]==Node)
    {
        return Node;

    }
    return parent[Node]=findParent(parent,Node);
}
void unionSet(int u,int v,vector<int>&parent,vector<int>& rank)
{
    u=findParent(parent,u);
    v=findParent(parent,v);
    if(rank[u]<rank[v])
    {
        parent[u]=v;
    }
    else if(rank[u]>rank[v])
    {
        parent[v]=u;
    }
    else {
        parent[v]=u;
        rank[u]++;
    }
}
bool cmp(vector<int>& a,vector<int>& b)
{
    return a[2]<b[2];
}
int MST(vector<vector<int>>&edges,int n)
{
    sort(edges.begin(),edges.end(),cmp);
    vector<int> parent(n);
    vector<int> rank(n);
    makeSet(parent,rank,n);
    int minwt=0;
    for(int i=0;i<edges.size();i++)
    {
        int u=findParent(parent,edges[i][0]);
        int v=findParent(parent,edges[i][1]);
        int wt=edges[i][2];
        if(u!=v)
        {
            minwt+=wt;
            cout<<"["<<edges[i][0]<<","<<edges[i][1]<<","<<edges[i][2]<<"] ";
            unionSet(u,v,parent,rank);
        }
    }
    return minwt;
}
int main()
{
    vector<vector<int>>edges;
    int n,m;
    cin>>n>>m;
    //for(int);
    
    return 0;
}