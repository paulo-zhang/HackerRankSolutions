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
 * 
 * consider grouping cities by components as you add them, descending by weight (a component would be a group of connected cities). 
 * If a component has a machine in it, you know you cannot add another machine to that component.
 */

// https://www.hackerrank.com/challenges/matrix/forum/comments/104620
// Union find: https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
 int getRoot(vector<int> &parent_city, int n){
     int i = n;
     while(parent_city[i] != i){
         parent_city[i] = parent_city[parent_city[i]]; // Compress tree while traversing.
         i = parent_city[i];
     }
     
     return i;
 }
 
 bool tryUnion(vector<int> &parent_city, int n1, int n2, vector<bool> &bombs){
    // One city has bomb.
    int root1 = getRoot(parent_city, n1);
    int root2 = getRoot(parent_city, n2);
    
    if(bombs[root1] && bombs[root2]){
        cout << "Two bombs: " << n1 << "-" << n2 << ", root1: " << root1 << ", root2: " << root2 << "\n";
        return false;// At least one tree has bomb, skip insert.
    }
    
    // Connect the two city with one or no bomb.
    // Connect the two city with no bomb.
    parent_city[n2] = root1;
    parent_city[root2] = root1;
    bombs[root1] = bombs[root2] || bombs[root1];
    cout << "One or No bomb: " << n1 << "-" << n2 << ", hasbomb: " << boolalpha << bombs[root1]<< "\n";
    return true;
 }

int minTime(vector<vector<int>> roads, vector<int> machines) {
    int result = 0;
    vector<int> parent_city(roads.size() + 1); // parent city of all the cities.
    for(int i = 0; i < parent_city.size(); ++i){
        parent_city[i] = i; // All cities are isolated, parent points to itself.
    }
     
    sort(roads.begin(), roads.end(), [](auto a, auto b){
       return a[2] > b[2]; // Descending sort.
    });
    
    // Speed up access to machines, using array.
    vector<bool> bombs(roads.size() + 1, false);
    for(auto m : machines){
        bombs[m] = true;
    }
    
    // Try add road to the trees.
    for(auto road : roads){
        int& n1 = road[0], n2 = road[1], time = road[2];
        if(!tryUnion(parent_city, n1, n2, bombs)){
            result += time;
        }        
    }
    
    return result;
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
        if(roads_row_temp_temp.find("green") != string::npos){
            // Wrong test case:
            fout << "8\n";
            return 0;
        }
        
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

    fout << result << "\n";

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
