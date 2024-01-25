#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>

using namespace std;
class Node
{
public:
    int CityNo;
    int GasLeft;
    int distance;
    Node(int a, int b)
    {
        CityNo = a;
        GasLeft = b;
        distance=INT_MAX;
    }
    bool operator<(const Node& other) const {
        return (CityNo < other.CityNo) || ((CityNo == other.CityNo) && (GasLeft < other.GasLeft));
    }
    //  bool operator<(const Node& other) const {
    //     return (distance<other.distance);
    // }
    
};
// struct CompareDescending {
//     bool operator()(pair<int,Node> & a, pair<int,Node>& b) const {
//         return a > b;
//     }
// };
void Initialize(vector<int> &distance,vector<int>&parent, int V)
{
    for (int i = 0; i < V; i++)
    {
        distance[i] = INT16_MAX;
        parent[i]=i;
    }
}
int  SSSC( map<Node, vector<pair<Node, int>>> MyMap1,int src,int des)
{
    stack<int> ma;
    queue<int> q;
    
    set<pair<int,Node>>st1;
    pair<int,int> key={src,0};
    Node temp1(src,0);
    temp1.distance=0;
   // distance[src] = 0;
    //st.insert({0, src});
    st1.insert({0,temp1});
    int totalCost=0;
    while (!st1.empty())
    {
        //auto top = *(st.begin());
        auto top1=*(st1.begin());
       // int nodeDistance = top.first;
       // int topNode = top.second;
        int nodeDistance1 = top1.first;
        Node topNode1 = top1.second;
        //st.erase(st.begin());
        st1.erase(st1.begin());
        // for (auto neighbour : adj[topNode])
        // {
        //     if (nodeDistance + neighbour.second < distance[neighbour.first])
        //     {
        //         auto record = st.find({distance[neighbour.first], neighbour.first});
        //         if (record != st.end())
        //         {
        //             st.erase(record);
        //         }
        //         distance[neighbour.first] = nodeDistance + neighbour.second;
        //         // cout<<src<<endl;
        //         parent[neighbour.first]=topNode;
        //         st.insert({distance[neighbour.first], neighbour.first});
        //     }
        // }
        vector<pair<Node,int>> ans=MyMap1[topNode1];
       // Node tempo=My[ans];
        for(int i=0;i<ans.size();i++)
        {
            if(nodeDistance1+ans[i].second<ans[i].first.distance)
            {
                
                auto record=st1.find({ans[i].first.distance,ans[i].first});
                {
                    if(record!=st1.end())
                    {
                        st1.erase(record);
                    }
                }
                ans[i].first.distance=nodeDistance1+ans[i].second;
                if(ans[i].first.CityNo==des&&ans[i].first.GasLeft==0)
                {
                    ma.push(ans[i].first.distance);
                    q.push(ans[i].first.distance);
                   // cout<<ans[i].first.distance<<endl;
                    //return ans[i].first.distance;
                }
                st1.insert({ans[i].first.distance,ans[i].first});
            }
        }
        //  for (auto neighbour : MyMap1[topNode1])
        // {
        //     if (nodeDistance + neighbour.second < distance[neighbour.first])
        //     {
        //         auto record = st.find({distance[neighbour.first], neighbour.first});
        //         if (record != st.end())
        //         {
        //             st.erase(record);
        //         }
        //         distance[neighbour.first] = nodeDistance + neighbour.second;
        //         // cout<<src<<endl;
        //         parent[neighbour.first]=topNode;
        //         st.insert({distance[neighbour.first], neighbour.first});
        //     }
        // }
    }

    //return distance;
    if (!q.empty()) {
    cout << q.front() << endl;
    exit(0);
    return q.front();
} else {
    cout << "Impossible" << endl;
    exit(0);
    return -1;  // Return a value to indicate failure, or handle it appropriately
}

   // return ma.top();
}

int main()
{
    // Declare an unordered map with pairs as keys and vectors of pairs as values
    map<pair<int, int>, vector<pair<int, int>>> MyMap;
    map<Node, vector<pair<Node, int>>> MyMap1;
    int n, m, tankCapacity;
    cin >> n >> m >> tankCapacity;
    vector<int> price(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int cost;
        cin >> cost;
        price[i] = cost;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= tankCapacity; j++)
        {
            Node key(i, j);
            vector<pair<Node, int>> temp;
            temp.push_back({Node(i, j + 1), price[i]});
            MyMap1.insert({key, temp});
        }
    }
    for(int i=0;i<m;i++)
    {
        int u,v,wt;
        cin>>u>>v>>wt;
        int k=0;
        for(int j=wt;j<=tankCapacity;j++)
        {
            Node key(u,j);
            
            MyMap1[key].push_back({Node(v,k++),0});
        }
    }
    for (const auto &entry : MyMap1)
    {
        cout << "Key: (" << entry.first.CityNo << ", " << entry.first.GasLeft <<") Values: ";
        for (const auto &value : entry.second)
        {
            cout << "(" << value.first.CityNo << ", " << value.first.GasLeft << ", " << value.second << ") ";
        }
        cout << endl;
    }
    int src,des;
    cin>>src>>des;
    cout<<SSSC(MyMap1,src,des)<<endl;

    

    // // Example usage: insert a key-value pair into the m
    // pair<int, int> key = make_pair(1, 2);
    // vector<pair<int, int>> values = {{3, 4}, {5, 6}};

    // inputs[key] = values;

    // Access the values associated with a key
    // cout << "Values for key (1, 2): ";
    // for (const auto& value : MyMap[key]) {
    //     cout << "(" << value.first << ", " << value.second << ") ";
    // }

    return 0;
}
