#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minTime' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY roads
 *  2. INTEGER_ARRAY machines
 */
 
 struct node{
    bool machine = false;
    vector<vector<int>> adj_nodes;  
 };
 struct edge{
     int u;
     int v;
     int time;
     edge& operator = (edge & e){
         u = e.u;
         v = e.v;
         time = e.time;
         return *this;
     }
 };
 
 int dfs_delete_path(vector<node> &nodes, vector<int> &machines, int root, vector<bool> &visited, vector<edge> path){
     int totalTime = 0;
     for(size_t i = 0; i < nodes[root].adj_nodes.size(); i++){
        if(visited[nodes[root].adj_nodes[i][0]])continue;
        
        visited[nodes[root].adj_nodes[i][0]] = true;
        vector<edge> newPath(path);
        edge e = {.u = root, .v = nodes[root].adj_nodes[i][0], .time = nodes[root].adj_nodes[i][1]};
        newPath.push_back(e);
        
        if(nodes[nodes[root].adj_nodes[i][0]].machine){
            edge min_edge;
            min_edge = newPath[0];
            // cout << "path: " << min_edge.u << "-" << min_edge.v << "," << min_edge.time << ";";
            for(size_t j = 1; j < newPath.size();j ++){
                if(newPath[j].time < min_edge.time){
                    min_edge = newPath[j];
                }
                
                // cout << min_edge.u << "-" << min_edge.v << "," << min_edge.time << ";";
            }
            
            totalTime += min_edge.time;
            for(size_t j = 0; j < nodes[min_edge.u].adj_nodes.size(); ++j){
                if(nodes[min_edge.u].adj_nodes[j][0] == min_edge.v){
                    nodes[min_edge.u].adj_nodes.erase(nodes[min_edge.u].adj_nodes.begin() + j);
                    break;
                }
            }
            for(size_t j = 0; j < nodes[min_edge.v].adj_nodes.size(); ++j){
                if(nodes[min_edge.v].adj_nodes[j][0] == min_edge.u){
                    nodes[min_edge.v].adj_nodes.erase(nodes[min_edge.v].adj_nodes.begin() + j);
                    break;
                }
            }
            
            // cout << "delete: " << min_edge.u << "-" << min_edge.v << ", time: " << min_edge.time<<endl;
            continue;
        }
        
        totalTime += dfs_delete_path(nodes, machines, nodes[root].adj_nodes[i][0], visited, newPath);
    }
    
    return totalTime;
 }

int minTime(vector<vector<int>> roads, vector<int> machines) {
    vector<node> nodes(roads.size() + 1);
    for(size_t i = 0;i < roads.size();i ++){
        vector<int> v1(2);
        v1[0] = roads[i][1];
        v1[1] = roads[i][2];
        nodes[roads[i][0]].adj_nodes.push_back(v1);
        
        vector<int> v2(2);
        v2[0] = roads[i][0];
        v2[1] = roads[i][2];
        nodes[roads[i][1]].adj_nodes.push_back(v2);
    }
    
    for(size_t i = 0;i < machines.size();i ++){
        nodes[machines[i]].machine = true;
    }
    
    int minTime = 0;
    for(size_t i = 0;i < machines.size();i ++){
        auto visited = vector<bool>(nodes.size(), false);
        visited[machines[i]] = true;
        minTime += dfs_delete_path(nodes, machines, machines[i], visited, vector<edge>());
    }
    
    return minTime;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    vector<vector<int>> roads(n - 1);

    for (int i = 0; i < n - 1; i++) {
        roads[i].resize(3);

        string roads_row_temp_temp;
        getline(cin, roads_row_temp_temp);

        vector<string> roads_row_temp = split(rtrim(roads_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int roads_row_item = stoi(roads_row_temp[j]);

            roads[i][j] = roads_row_item;
        }
    }

    vector<int> machines(k);

    for (int i = 0; i < k; i++) {
        string machines_item_temp;
        getline(cin, machines_item_temp);

        int machines_item = stoi(ltrim(rtrim(machines_item_temp)));

        machines[i] = machines_item;
    }

    int result = minTime(roads, machines);

    cout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
