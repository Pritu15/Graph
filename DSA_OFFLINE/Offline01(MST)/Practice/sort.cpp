#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:2000000")

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
vector<vector<Edge>> AllMST;
void PrintEdge(vector<Edge> &adj)
{
    for(int i=0;i<adj.size();i++)
    {
        cout<<adj[i].src<<" "<<adj[i].des<<" "<<adj[i].wt<<endl;
    }

}
void printMST(vector<Edge> &mst)
{
    cout << "[ ";
    for (int i = 0; i < mst.size(); i++)
    {
        cout << "[" << mst[i].src << "," << mst[i].des << "," << mst[i].wt << "]";
        if (i < mst.size() - 1)
        {
            cout << ",";
        }
    }
    cout << " ]" << endl;
}

bool compare(Edge &a, Edge &b)
{
    // if(a.wt==b.wt)
    // {
    //     return a.src<b.src;
    // }
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
bool cmp(vector<int> &a, vector<int> &b)
{
    return a[2] < b[2];
}
int MST(vector<Edge> &adj, int n)
{
    sort(adj.begin(), adj.end(), compare);
    cout<<"Printing Sorted List:  "<<endl;
    PrintEdge(adj);
    // for(int i=0;i<adj.size();i++)
    // {
    //     cout<<"src: "<<adj[i].src<<" Des: "<<adj[i].des<<" wt: "<<adj[i].wt<<endl;
    // }
    vector<int> parent(n);
    vector<int> rank(n);
    makeSet(parent, rank, n);
    int minwt = 0;
    vector<Edge> mst;
    for (int i = 0; i < adj.size(); i++)
    {
        //  cout<<"Finding MST"<<endl;
        int u = findParent(parent, adj[i].src);
        int v = findParent(parent, adj[i].des);
        int wt = adj[i].wt;
        // cout<<"Found the Parent"<<endl;
        if (u != v)
        {
            minwt += wt;
            mst.push_back(adj[i]);
            // if (i == 0)
            // {
            //     cout << "[ ";
            // }
            // cout << "[" << adj[i].src << "," << adj[i].des << "," << adj[i].wt << "],";
            unionSet(u, v, parent, rank);
        }
        // cout<<"FOUND"<<endl;
        // if (mst.size() == n - 1)
        // {
        //     AllMST.push_back(mst);
        //    // printMST(mst);
        //    mst.clear();
        //   // mst=vector<Edge>();
        //     makeSet(parent, rank, n);
        //     //i=0;
        // }
    }
    // cout << "]" << endl;
    //  cout << "[ ";
    //  for (int i = 0; i < mst.size(); i++)
    //  {
    //      cout << "[" << mst[i].src << "," << mst[i].des << "," << mst[i].wt << "]";
    //      if (i < mst.size() - 1)
    //      {
    //          cout << ",";
    //      }
    //  }
    //  cout << " ]" << endl;
    printMST(mst);
    return minwt;
}
vector<vector<Edge>> combination(vector<Edge>& adj)
{
    vector<vector<Edge>> ans;
     ans.push_back({});
    for(Edge e: adj)
    {
        int n=ans.size();
        for(int j=0;j<n;j++)
        {
            vector<Edge> temp;
            temp=ans[j];
            temp.push_back(e);
            ans.push_back(temp);

        }
    } 
    return ans;
}

void generateCombinations(vector<Edge>& nums, vector<Edge>& current, int index, vector<vector<Edge>>& result) {

    result.push_back(current);
    for(int i=index;i<nums.size();i++)
    {
        current.push_back(nums[i]);
        generateCombinations(nums,current,i+1,result);
        current.pop_back();
    }
}

vector<vector<Edge>> getAllCombinations(vector<Edge>& nums) {
    vector<vector<Edge>> result;
    vector<Edge> current;
    generateCombinations(nums, current, 0, result);
    return result;
}

int main()
{
    vector<Edge> edge;
    int n, m;
    int u, v, wt;
    cin >> n >> m;
    // edge.resize(2*m);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> wt;
        Edge a(u, v, wt);
        Edge b(v, u, wt);

        edge.push_back(a);
        edge.push_back(b);
    }
    // sort(edge.begin(),edge.end(),compare);

    // int sum=MST(edge, n);
    // cout << "HIIIIII" << endl;
    // for (auto x : AllMST)
    // {
    //     printMST(x);
    // }
    // cout<<"MST's Weight: "<<sum<<endl;
    vector<vector<Edge>> ans=getAllCombinations(edge);
    cout<<"HIIIII"<<endl;
    for(auto v: ans)
    {
        printMST(v);
    }

    return 0;
}