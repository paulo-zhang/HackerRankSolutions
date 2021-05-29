#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct node{
    vector<int> adj_nodes;
    int dis;
};

class Graph {
    private:
        vector<node> nodes;
    public:
        Graph(int n) {
            nodes.resize(n);
        }
    
        void add_edge(int u, int v) {
            nodes[u].adj_nodes.push_back(v);
            nodes[v].adj_nodes.push_back(u);
        }
    
        vector<int> shortest_reach(int start) {
            vector<int> result(nodes.size(), -1);
            vector<int> visited(nodes.size(), false);
            queue<int> q;
            q.push(start);
            nodes[start].dis = 0;
            
            while (!q.empty()) {
                int n = q.front();
                q.pop();
                visited[n] = true;
                result[n] = nodes[n].dis;
                
                for(size_t i = 0; i < nodes[n].adj_nodes.size(); ++i){
                    if(visited[nodes[n].adj_nodes[i]])continue;
                    
                    nodes[nodes[n].adj_nodes[i]].dis = nodes[n].dis + 6;
                    q.push(nodes[n].adj_nodes[i]);
                }
            }
            
            return result;
        }
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
		int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
		int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}