#include <bits/stdc++.h>
using namespace std;

void Initialize(vector<int> &distance, vector<int> &parent, int V)
{
    for (int i = 0; i < V; i++)
    {
        distance[i] = INT16_MAX;
        parent[i] = i;
    }
}
string returnString(vector<pair<string, int>> &city, int x)
{
    for (int i = 0; i < city.size(); i++)
    {
        if (city[i].second == x)
        {
            return city[i].first;
        }
    }
}
int SSSC(vector<vector<pair<int, int>>> &adj, int V, int E, int src, int des, vector<pair<string, int>> &city)
{
    vector<int> distance(101);
    vector<int> parent(V + 1);
    Initialize(distance, parent, V + 1);
    set<pair<int, int>> st;
    distance[src] = 0;
    st.insert({0, src});
    int totalCost = 0;
    while (!st.empty())
    {
        auto top = *(st.begin());
        int nodeDistance = top.first;
        int topNode = top.second;
        st.erase(st.begin());
        for (auto neighbour : adj[topNode])
        {
            if (nodeDistance + neighbour.second < distance[neighbour.first])
            {
                auto record = st.find({distance[neighbour.first], neighbour.first});
                if (record != st.end())
                {
                    st.erase(record);
                }
                distance[neighbour.first] = nodeDistance + neighbour.second;
                // cout<<src<<endl;
                parent[neighbour.first] = topNode;
                st.insert({distance[neighbour.first], neighbour.first});
            }
        }
    }

    int temp = des;
    vector<int> outputs;
    for (auto v : parent)
    {
        cout << v << "->";
    }
    cout << endl;
    while (parent[des] != des)
    {
        // cout<<des<<"->";
        outputs.push_back(des);
        des = parent[des];
    }
    outputs.push_back(des);
    // cout<<des<<endl;
    // cout<<"Now the destination is: "<<des<<endl;
    for (int i = outputs.size() - 1; i >= 0; i--)
    {
        cout << returnString(city, outputs[i]) << " " << outputs[i];
        if (i != 0)
        {
            cout << "->";
        }
    }
    cout << endl;
    return distance[temp];
}
int returnIndex(vector<pair<string, int>> &city, string x)
{
    for (int i = 0; i < city.size(); i++)
    {
        if (city[i].first == x)
        {
            return city[i].second;
        }
    }
}

int main()
{
    int n, m, tankCapacity;
    vector<pair<string, int>> city;
    // queue<string> q;

    cin >> n >> m;
    vector<int> delays(n + 1);
    vector<int> distance(n + 1, INT_MAX);
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1; i <= n; i++)
    {
        string temp;
        int delay;
        cin >> temp >> delay;
        delays[i] = delay;
        city.push_back({temp, i});
        // cout << returnIndex(city, temp) << endl;
    }
    for (int i = 0; i < m; i++)
    {
        string u, v;
        int dis;
        cin >> u >> v >> dis;
        int u1 = returnIndex(city, u);
        int v1 = returnIndex(city, v);
        adj[u1].push_back({v1, dis + delays[v1]});
        adj[v1].push_back({u1, dis + delays[u1]});
    }
    cout << "Printing Adjacency List: " << endl;
    for (int i = 1; i < adj.size(); i++)
    {
        cout << i << "-> ";
        for (int j = 0; j < adj[i].size(); j++)
        {
            cout << "[" << adj[i][j].first << "," << adj[i][j].second << "] ";
        }
        cout << endl;
    }
    string src, des;
    cin >> src >> des;
    int src1 = returnIndex(city, src);
    int des1 = returnIndex(city, des);
    cout << SSSC(adj, n, m, src1, des1, city) << endl;
    // int space = n * (tankCapacity + 1) + 1;
    // vector<vector<int>> states(n + 1, vector<int>(tankCapacity + 1));
    // vector<int> price(n + 1);
    // for (int i = 1; i <= n; i++)
    // {
    //     int cost;
    //     cin >> cost;
    //     price[i] = cost;
    // }
    // int start = 1;
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 0; j <= tankCapacity; j++)
    //     {

    //         states[i][j] = start++;
    //     }
    // }

    // vector<int> distance(space, {INT_MAX});
    // vector<vector<pair<int, int>>> adj(space);
    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = 0; j <= tankCapacity; j++)
    //     {
    //         if (j == tankCapacity)
    //         {
    //             continue;
    //         }
    //         adj[states[i][j]].push_back({states[i][j + 1], price[i]});
    //     }
    // }
    // for (int i = 0; i < m; i++)
    // {
    //     int u, v, wt;
    //     cin >> u >> v >> wt;
    //     int Gassleft = 0;
    //     for (int i = wt; i <= tankCapacity; i++)
    //     {
    //         adj[states[u][i]].push_back({states[v][Gassleft], 0});
    //         adj[states[v][i]].push_back({states[u][Gassleft], 0});
    //         Gassleft++;
    //     }
    // }
    // // for (int i = 0; i < adj.size(); i++)
    // // {
    // //     cout << "Node " << i << ": ";
    // //     for (auto neighbor : adj[i])
    // //     {
    // //         cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
    // //     }
    // //     cout << endl;
    // // }

    // int src, des;
    // cin >> src >> des;
    // int cost = SSSC(adj, distance, price, src, des, states);
    // if (cost == INT_MAX)
    // {
    //     cout << "Impossible" << endl;
    //     exit(0);
    // }
    // cout << cost << endl;
    return 0;
}