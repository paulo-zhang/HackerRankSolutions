#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>
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
            visited[start] = true; // Set visited when the node is being pushed in.
            q.push(start);
            nodes[start].dis = 0;
            
            while (!q.empty()) {
                int n = q.front();
                q.pop();
                result[n] = nodes[n].dis;
                
                for(size_t i = 0; i < nodes[n].adj_nodes.size(); ++i){
                    int child = nodes[n].adj_nodes[i];
                    if(visited[child])continue;
                    
                    visited[child] = true; // Set visited when the node is being pushed in.
                    nodes[child].dis = nodes[n].dis + 6;
                    q.push(child);
                }
            }
            
            return result;
        }
};

int main() {
    ifstream fin("input01.txt");
    int queries;
    fin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
		int n, m;
        fin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        fin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            fin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
		int startId;
        fin >> startId;
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