#include <bits/stdc++.h>
using namespace std;
int SSSC(vector<vector<pair<int, int>>> &adj, vector<int> &distance, vector<int> &price, int src, int des, vector<vector<int>> &states)
{
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

                st.insert({distance[neighbour.first], neighbour.first});
            }
        }
    }

    return distance[states[des][0]];
}
int main()
{
    int n, m, tankCapacity;
    cin >> n >> m >> tankCapacity;
    int space = n * (tankCapacity + 1) + 1;
    vector<vector<int>> states(n + 1, vector<int>(tankCapacity + 1));
    vector<int> price(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int cost;
        cin >> cost;
        price[i] = cost;
    }
    int start = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= tankCapacity; j++)
        {

            states[i][j] = start++;
        }
    }

    vector<int> distance(space, {INT_MAX});
    vector<vector<pair<int, int>>> adj(space);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= tankCapacity; j++)
        {
            if (j == tankCapacity)
            {
                continue;
            }
            adj[states[i][j]].push_back({states[i][j + 1], price[i]});
        }
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        int Gassleft = 0;
        for (int i = wt; i <= tankCapacity; i++)
        {
            adj[states[u][i]].push_back({states[v][Gassleft], 0});
            adj[states[v][i]].push_back({states[u][Gassleft], 0});
            Gassleft++;

        }
    }
    // for (int i = 0; i < adj.size(); i++)
    // {
    //     cout << "Node " << i << ": ";
    //     for (auto neighbor : adj[i])
    //     {
    //         cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
    //     }
    //     cout << endl;
    // }

    int src, des;
    cin >> src >> des;
    int cost = SSSC(adj, distance, price, src, des, states);
    if (cost == INT_MAX)
    {
        cout << "Impossible" << endl;
        exit(0);
    }
    cout << cost << endl;
    return 0;
}