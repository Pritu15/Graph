#include<iostream>
#include<vector>
using namespace std;
const int N=1e3+10;
//int graph1[N][N];
vector<pair<int,int>> graph2[N];

int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int v1,v2,wt;
        cin>>v1>>v2>>wt;
       // graph1[v1][v2]=wt;
        graph2[v1].push_back(make_pair(v2,wt));

    }
    cout<<"HEllo"<<endl;
    return 0;
}