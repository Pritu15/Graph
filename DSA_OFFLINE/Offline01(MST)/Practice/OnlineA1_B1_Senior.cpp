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
class Point{
     public:
    int x,y;
   
    Point(int a,int b)
    {
        x=a;
        y=b;
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
bool comp(Point &a, Point &b)
{
    return a.x < b.x;
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
int MST(vector<Edge> &adj, int n)
{
    //sort(adj.begin(), adj.end(), compare);
    vector<int> parent(n + 1);
    vector<int> rank(n + 1);
    makeSet(parent, rank, n + 1);
    int minwt = 0;
    vector<Edge> mst;
    for (int i = 0; i < adj.size(); i++)
    {
        int u = findParent(parent, adj[i].src);
        int v = findParent(parent, adj[i].des);
        int wt = adj[i].wt;
        if (u != v)
        {
            minwt += wt;
            mst.push_back(adj[i]);
            unionSet(u, v, parent, rank);
        }
    }

    return minwt;
}
int distance(Point p,Point q)
{
    int wt = abs((p.x-q.x))+abs((p.y-q.y));
    return wt;

}
pair<int,int> undf(vector<Point>& adj,Point p)
{
   // int i=0;
    int index=0;
    int wt = 14444;
    // if(wt==0)
    // {
    //       wt = abs((p.x-adj[1].x))+abs((p.y-adj[1].y));
    //       cout<<wt<<endl;
    // }
    for(int i=0;i<adj.size();i++)
    {
        if(p.x==adj[i].x&&p.y==adj[i].y)
        {
            continue;
        }
        if(distance(adj[i],p)<wt)
        {
            wt=distance(adj[i],p);
            index=i;
        }
    }
    cout<<wt<<endl;
    return {index,wt};

}
int Answer(vector<Point> &adj, int n)
{
    sort(adj.begin(), adj.end(), comp);
    for(int i=0;i<adj.size();i++)
    {
        cout<<adj[i].x<<" "<<adj[i].y<<endl;
    }
    vector<int> parent(n + 1);
    vector<int> rank(n + 1);
    makeSet(parent, rank, n + 1);
    int minwt = 0;
    vector<Edge> mst;
    for (int i = 0; i < adj.size(); i++)
    {
       
        pair<int,int> temp=undf(adj,adj[i]);
         int u = findParent(parent, i);
        int v = findParent(parent, temp.first);
        int wt = temp.second;
        //Point p=adj[i];
        if (u != v)
        {
            minwt += wt;
           // mst.push_back(adj[i]);
            unionSet(u, v, parent, rank);
        }
    }

    return minwt;
}
bool isCycle(vector<Edge> &adj, int n)
{
   // sort(adj.begin(), adj.end(), comp);

    vector<int> parent(n + 1);
    vector<int> rank(n + 1);
    makeSet(parent, rank, n + 1);
    for (int i = 0; i < adj.size(); i++)
    {

        int u = findParent(parent, adj[i].src);
        int v = findParent(parent, adj[i].des);
        int wt = adj[i].wt;
        if (u != v)
        {
            unionSet(u, v, parent, rank);
        }
        else
        {

            return false;
        }
    }
    return true;
}
vector<vector<Edge>> getAllSubsets(vector<Edge> &nums, int p, int minwt)
{
    int n = nums.size();
    vector<vector<Edge>> result;

    for (int mask = 0; mask < (1 << n); ++mask)
    {
        vector<Edge> current;
        for (int i = 0; i < n; ++i)
        {
            if (mask & (1 << i))
            {
                current.push_back(nums[i]);
            }
        }
        if (current.size() == p && minwt == Count(current) && isCycle(current, p + 1))
        {

            result.push_back(current);
        }
    }

    return result;
}

bool sameEdge(Edge a, Edge b)
{
    if (a.src == b.src && a.des == b.des && a.wt == b.wt)
    {
        return true;
    }
    return false;
}
bool isIntheAdjList(vector<Edge> &adj, Edge a)
{
    bool flag;
    for (auto v : adj)
    {
        flag = sameEdge(v, a);
        if (flag)
        {
            return flag;
        }
    }
    return false;
}
bool okay(vector<Edge> &mst, vector<Edge> &adj)
{
    int flag;
    for (auto v : mst)
    {
        flag = isIntheAdjList(adj, v);
        if (!flag)
        {
            return flag;
        }
    }
    return true;
}
int main()
{
    vector<Edge> edges;
    vector<Point> input;
    vector<Edge> Alledges;
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        //Alledges.push_back(Edge(u, v, wt));
       // edges.push_back(Edge(u, v, wt));
       input.push_back(Point(u,v));
        // edges.push_back(Edge(v, u, wt));
        // Alledges.push_back(Edge(v, u, wt));
    }
    int ans=Answer(input,n);
    cout<<ans<<endl;
    // int minwt = MST(edges, n);
    // cout << minwt << endl;
    // cout << "***************All the Combinations*****************************" << endl;
   // vector<vector<Edge>> MSTs = getAllSubsets(edges, n - 1, minwt);
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
