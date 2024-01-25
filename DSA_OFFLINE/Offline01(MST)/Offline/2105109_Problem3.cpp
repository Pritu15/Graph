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

void printCombination( vector<Edge> &combination)
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
    for (auto v : adj)
    {
        printCombination(v);
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
bool compare(Edge &a, Edge &b)
{
    return a.wt < b.wt;
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
    sort(adj.begin(), adj.end(), compare);
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
bool isCycle(vector<Edge> &adj, int n)
{
    sort(adj.begin(), adj.end(), compare);

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
int howMuch(vector<vector<Edge>> &adj, Edge a)
{
    int cnt = 0;
    for (int i = 0; i < adj.size(); i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            if (sameEdge(a, adj[i][j]))
            {
                cnt++;
            }
        }
    }
    return cnt;
}

void print(const vector<int> &combination)
{
    if (combination.size() == 0)
    {
        cout << "[]" << endl;
        return;
    }
    cout << "[ ";
    int i = 0;
    for (const int &edge : combination)
    {
        cout << edge;
        if (i < combination.size() - 1)
        {
            cout << ",";
            i++;
        }
    }
    cout << "]" << endl;
}
int main()
{
    vector<Edge> edges;
    vector<int> ans;
    vector<Edge> Alledges;
    int n, m;
    cin >> n >> m;
    ans.resize(m);
    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        Alledges.push_back(Edge(u, v, wt));
        edges.push_back(Edge(u, v, wt));
        // Alledges.push_back(Edge(v, u, wt));
    }
    int minwt = MST(edges, n);
    vector<vector<Edge>> OriginalAnswer = getAllSubsets(edges, n - 1, minwt);
    vector<int> criticalEdge;
    vector<int> pseudo;
    for (int i = 0; i < Alledges.size(); i++)
    {
        int temp = howMuch(OriginalAnswer, Alledges[i]);
        if (temp == OriginalAnswer.size())
        {
            // cout<<"Any"<<endl;
            criticalEdge.push_back(i);
        }
        else if (temp == 0)
        {
            // cout<<"NONE"<<endl;
        }
        else
        {
            // cout<<"At least one"<<endl;
            pseudo.push_back(i);
        }
    }
    cout << "Critical Edge: ";
    print(criticalEdge);
    cout << "Pseudo critical Edges: ";
    print(pseudo);
    // cout << "HIIIIIIIIII" << endl;

    return 0;
}
