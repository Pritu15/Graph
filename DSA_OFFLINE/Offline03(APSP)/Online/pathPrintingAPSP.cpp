#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void printPath(vector<vector<int>>& path, int src, int dest) {
    if (path[src][dest] == -1) {
        cout << "No path from " << src << " to " << dest << endl;
    } else {
        cout << "Shortest path from " << src << " to " << dest << ": " << src;
        while (src != dest) {
            src = path[src][dest];
            cout << " -> " << src;
        }
        cout << endl;
    }
}

void floydWarshall(vector<vector<int>>& graph, vector<vector<int>>& path,int n) {
   // int n = graph.size();

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX && (graph[i][k] + graph[k][j] < graph[i][j])) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
}

int main() {

    int n, m; // Number of vertices
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INT_MAX));

    vector<vector<int>> path(n + 1, vector<int>(n + 1, -1));
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;

        graph[u][v] = wt;
        graph[v][u] = wt;
    }

    floydWarshall(graph, path,n);

    int src = 8;
    int dest = 2;
    printPath(path, src, dest);

    return 0;
}
