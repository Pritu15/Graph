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
int SSSC(vector<vector<pair<int, int>>> &adj,int src, int des, vector<pair<string, int>> &citiesInI1)
{
    vector<int> distance(101);
    vector<int> parent(101);
    Initialize(distance, parent, 101);
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
    while (parent[des] != des)
    {
        // cout<<des<<"->";
        outputs.push_back(des);
        des = parent[des];
    }
    outputs.push_back(des);
    // cout<<des<<endl;
    // cout<<"Now the destination is: "<<des<<endl;
    for (int i = outputs.size() - 1;
         i >= 0; i--)
    {
        cout << returnString(citiesInI1, outputs[i]);
        if (i != 0)
        {
            cout << "->";
        }
    }
    cout << endl;
    return distance[temp];
}
bool AlreadyExist(vector<pair<string, int>> &city, string x)
{
    for (int i = 0; i < city.size(); i++)
    {
        if (city[i].first == x)
        {
            return true;
        }
    }
    return false;
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
    //int n, m, tankCapacity;
    int statesInI1, roadsInI1, statesInI2, roadsInI2;

    cin >> statesInI1 >> roadsInI1 >> statesInI2 >> roadsInI2;
    vector<int> portCostI1(statesInI1 + statesInI2 + 2);
    // vector<int>portCostI2(statesInI2+1);
    vector<pair<string, int>> citiesInI1;
    vector<pair<string, int>> citiesInI2(statesInI2 + 1);
    vector<vector<pair<int, int>>> adj(100);
    string x, y;
    int wt, u1, v1;
    cin >> x >> y >> wt;
    int i = 1;
    u1 = i;
    citiesInI1.push_back({x, i++});
    v1 = i;
    citiesInI1.push_back({y, i++});
    adj[u1].push_back({v1, wt});
    adj[v1].push_back({u1, wt});
    // adj[u1].push_back({v1,wt});
    for (int j = 1; j < roadsInI1; j++)
    {

        cin >> x >> y >> wt;
        int u, v;
        if (AlreadyExist(citiesInI1, x))
        {
            cout << "here" << endl;
            u = returnIndex(citiesInI1, x);
        }
        else
        {
            citiesInI1.push_back({x, i});
            u = i++;
        }
        if (AlreadyExist(citiesInI1, y))
        {
            v = returnIndex(citiesInI1, y);
        }
        else
        {
            citiesInI1.push_back({y, i});
            v = i++;
        }
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    cin >> x >> y >> wt;
    // i=1;
    u1 = i;
    citiesInI1.push_back({x, i++});
    v1 = i;
    citiesInI1.push_back({y, i++});
    adj[u1].push_back({v1, wt});
    adj[v1].push_back({u1, wt});
    for (int j = 1; j < roadsInI2; j++)
    {
        cin >> x >> y >> wt;
        int u, v;
        if (AlreadyExist(citiesInI1, x))
        {
            u = returnIndex(citiesInI1, x);
        }
        else
        {
            citiesInI1.push_back({x, i});
            u = i++;
        }
        if (AlreadyExist(citiesInI1, y))
        {
            v = returnIndex(citiesInI1, y);
        }
        else
        {
            citiesInI1.push_back({y, i});
            v = i++;
        }
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    int portcityI1;
    cin >> portcityI1;
    vector<int> connectionI1;
    vector<int> connectionI2;
    for (int j = 0; j < portcityI1; j++)
    {
        cin >> x >> wt;
        int u = returnIndex(citiesInI1, x);
        connectionI1.push_back(u);
        portCostI1[u] = wt;
    }
    int portcityI2;
    cin >> portcityI2;
    // vector<int>connection;
    for (int j = 0; j < portcityI2; j++)
    {
        cin >> x >> wt;
        int u = returnIndex(citiesInI1, x);
        connectionI2.push_back(u);
        portCostI1[u] = wt;
    }

    for (int i = 0; i < connectionI1.size(); i++)
    {
        for (int j = 0; j < connectionI2.size(); j++)
        {

            adj[connectionI1[i]].push_back({connectionI2[j], portCostI1[connectionI1[i]] + portCostI1[connectionI2[j]]});
            // adj[connectionI1[j]].push_back({connectionI2[i],portCostI1[connectionI1[j]]+portCostI1[connectionI2[i]]});
            // cout<<adj[connection[i]][j].first<<"->"<<adj[connection[i]][j].second<<endl;
        }
    }

    string src, des;
    cin >> src >> des;
    //  cout<<src<<"->"<<des<<endl;
    int src1 = returnIndex(citiesInI1, src);
    int des1 = returnIndex(citiesInI1, des);
    // cout<<src1<<"->"<<des1<<endl;
    cout << SSSC(adj,src1, des1, citiesInI1) << endl;
    return 0;
}