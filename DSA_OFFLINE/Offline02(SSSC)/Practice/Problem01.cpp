#include <bits/stdc++.h>
using namespace std;
class thrice
{
public:
    int price, distance, index;
    thrice(int a, int b, int c)
    {
        price = a;
        distance = b;
        index = c;
    }
    bool operator<(const thrice &other) const
    {
        if (price != other.price)
            return price < other.price;
        if (distance != other.distance)
            return distance < other.distance;
        return index < other.index;
    }
    bool operator==(const thrice &other) const
    {
        return price == other.price && distance == other.distance && index == other.index;
    }
};
void Initialize(vector<int> &distance, vector<int> &parent, int V)
{
    for (int i = 0; i < V; i++)
    {
        distance[i] = INT16_MAX;
        parent[i] = i;
    }
}
pair<int,bool> findLessPrice(vector<vector<pair<int, int>>> &adj,vector<int> &priceList,int src,int price)
{
    int min=0;
    int v;
    int wt;
    bool flag=false;
    for(auto neighbour: adj[src])
    {
        
        if(priceList[neighbour.first]<price)
        {
            price=priceList[neighbour.first];
            v=neighbour.first;
            wt=neighbour.second;
            flag=true;
        }
        
    }
return {wt,flag};

}
vector<int> SSSC(vector<vector<pair<int, int>>> &adj, vector<int> &price, int V, int E, int src, int des, int tankCapacity)
{
    vector<int> distance(101);
    vector<int> parent(101);
    Initialize(distance, parent, 101);
    set<pair<int, int>> st;
    set<thrice> st1;
    distance[src] = 0;
    //if(findLessPrice(adj,price,src,price[src]));
    //st.insert({0, src});
    st1.insert(thrice(price[src], 0, src));
    int totalCost = 0;
    while (!st1.empty())
    {
       // auto top = *(st.begin());
        auto top1 = *(st1.begin());
        // if(findLessPrice(adj,price,src,price[src]).second)
        // {
        //     totalCost+=findLessPrice(adj,price,src,price[src]).first*
        // }
       // int nodeDistance = top.first;
        //int topNode = top.second;
        int nodeDistance1 = top1.distance;
        int topNode1 = top1.index;
        int gasPrice=top1.price;
       // st.erase(st.begin());
        st1.erase(st1.begin());
        for (auto neighbour : adj[topNode1])
        {
            // if (nodeDistance + neighbour.second < distance[neighbour.first])
            // {
            //     auto record = st.find({distance[neighbour.first], neighbour.first});
            //     auto record1= st1.find(thrice(price[neighbour.first],distance[neighbour.first],neighbour.first));
            //     if (record != st.end())
            //     {
            //         st.erase(record);
            //     }
            //     if(record1!=st1.end())
            //     {
            //         st1.erase(record1);
            //     }
            //     distance[neighbour.first] = nodeDistance + neighbour.second;
            //     // cout<<src<<endl;
            //     parent[neighbour.first]=topNode;
            //     st.insert({distance[neighbour.first], neighbour.first});
            // }
            
            if (nodeDistance1 + neighbour.second < distance[neighbour.first])
            {
                cout<<"HIIIII"<<endl;
                // auto record = st.find({distance[neighbour.first], neighbour.first});
                auto record1 = st1.find(thrice(price[neighbour.first], distance[neighbour.first], neighbour.first));
                // if (record != st.end())
                // {
                //     st.erase(record);
                // }
                if (record1 != st1.end())
                {
                    st1.erase(record1);
                }
                distance[neighbour.first] = nodeDistance1 + neighbour.second;
                // cout<<src<<endl;
                parent[neighbour.first] = topNode1;
                st1.insert({price[neighbour.first], distance[neighbour.first], neighbour.first});
                cout << "Elements of the set (thrice): ";
            for (const auto &element : st1)
            {
                cout << "(" << element.price << ", " << element.distance << ", " << element.index << ") ";
            }
            cout << endl;
            }
        }
    }
    for (int i = 0; i < parent.size(); i++)
    {
        cout << parent[i] << " ";
    }
    cout << endl;
    while (parent[des] != des)
    {
        cout << des << "->";
        des = parent[des];
    }
    cout << des << endl;
    return distance;
}
int main()
{
    int n, m, tankCapacity;
    // unordered_map<pair<int,int>,vector<pair<int,int>>> inputs;
    cin >> n >> m >> tankCapacity;
    vector<vector<pair<int, int>>> adj(1000);
    vector<int> price(101);
    for (int i = 0; i < n; i++)
    {
        int money;
        cin >> money;
        price[i + 1] = money;
    }
    // adj.resize(n+1);
    for (int i = 0; i < m; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    for (int i = 0; i <7; i++)
    {
        cout << "adj list for " << i << " :" << endl;
        for (int j = 0; j < adj[i].size(); j++)
        {
            cout << adj[i][j].first << " " << adj[i][j].second << endl;
        }
    }
    int src, des;
    cin >> src >> des;
    vector<int> distance = SSSC(adj, price, n, m, src, des, tankCapacity);
    for (int i = 0; i < distance.size(); i++)
    {
        cout << distance[i] << " ";
    }
    return 0;
}