#include <iostream>
#include <vector>
#include <algorithm>
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
void printCombination(vector<Edge> &combination)
{
    cout << "[ ";
    int i = 0;
    for (const Edge &edge : combination)
    {
        cout << "[" << edge.src << "," << edge.des << "," << edge.wt << "] ";
        if (i < combination.size() - 1)
        {
            cout << ",";
            i++;
        }
    }
    cout << "]" << endl;
}
void printAll(vector<vector<Edge>> &adj)
{
    int i = 1;
    cout << "MSTs:" << endl;
    for (auto v : adj)
    {
        cout << i << " : ";
        printCombination(v);
        i++;
    }
}
int Count(vector<Edge> &adj)
{
    int sum = 0;
    for (int i = 0; i < adj.size(); i++)
    {
        sum += adj[i].wt;
    }
    return sum;
}
bool compare(pair<int,int> &a, pair<int,int> &b)
{
    return a.first < b.first;
}
void makeSet(vector<int> &parent, vector<int> &rank, int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}
int findParent(vector<int> &parent, int Node)
{
    if (parent[Node] == Node)
    {
        return Node;
    }
    return parent[Node] = findParent(parent, parent[Node]);
}
void unionSet(int u, int v, vector<int> &parent, vector<int> &rank)
{
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if (rank[u] > rank[v])
    {
        parent[v] = u;
    }
    else
    {
        parent[v] = u;
        rank[u]++;
    }
}
int distance(pair<int,int>& a,pair<int,int>& b)
{

    int dis=abs((a.first-b.first))+abs(a.second-b.second);
    return dis;
}
pair<int,int>Answer(vector<pair<int,int>>& adj,pair<int,int> &a)
{
    int minwt=INT16_MAX;
    int index=0;

    for(int i=0;i<adj.size();i++)
    {
        if(a.first==adj[i].first&&a.second==adj[i].second)
        {

            continue;
        }
        if(distance(a,adj[i])<minwt)
        {

            minwt=distance(a,adj[i]);
            index=i;
        }
    }
    return {index,minwt};
}
int MSTCost(vector<pair<int,int>>&adj, int n)
{
    sort(adj.begin(), adj.end(), compare);
    vector<int> parent(n + 1);
    vector<int> rank(n + 1);
    makeSet(parent, rank, n + 1);
    int minwt = 0;
    //vector<Edge> mst;
    for (int i = 0; i < adj.size(); i++)
    {
        pair<int,int> temp=Answer(adj,adj[i]);
        int u = findParent(parent, i);
        int v = findParent(parent, temp.first);
        int wt = temp.second;
        if (u != v)
        {
            minwt += wt;
           // mst.push_back(adj[i]);
            unionSet(u, v, parent, rank);
        }
    }

    return minwt;
}








int main()
{
    vector<pair<int,int>>houses;
    vector<Edge> edges;
    vector<Edge> Alledges;
    int n, m;
    cin >> n;
  for(int i=0;i<n;i++)
  {

      int x,y;
      cin>>x>>y;
      houses.push_back({x,y});
  }
    int minCOst = MSTCost(houses, n);
     cout << minCOst << endl;
    // cout << "***************All the Combinations*****************************" << endl;
    //vector<vector<Edge>> MSTs = getAllSubsets(edges, n - 1, minwt);
    // cout << "Total Mst's: " << combinations.size() << endl;
    // vector<vector<Edge>> realAnswer;
    //printAll(MSTs);
    //     for (auto v : combinations)
    //     {
    //         int wt = Count(v);
    //         if (minwt == wt)
    //         {
    //             realAnswer.push_back(v);
    //         }
    //     }
    //     cout << "Total Mst's: " << realAnswer.size() << endl;
    //     int i = 1;
    //     vector<vector<Edge>> OriginalAnswer;
    //     for (auto v : realAnswer)
    //     {
    //         bool flag = isCycle(v, n);
    //         if (flag == true)
    //         {
    //             OriginalAnswer.push_back(v);
    //         }
    //     }
    //     cout << "Total Mst's: " << OriginalAnswer.size() << endl;
    //    // printAll(OriginalAnswer);
    //      vector<vector<Edge>> OriginalAnswer2;
    //     for (auto v : OriginalAnswer)
    //     {
    //         bool flag = okay(v,Alledges);
    //         if (flag == true)
    //         {
    //             OriginalAnswer2.push_back(v);
    //         }
    //     }
    //     cout << "Total Mst's: " << OriginalAnswer2.size() << endl;
    //     printAll(OriginalAnswer2);
    // cout << "HIIIIIIIIII" << endl;

    return 0;
}
