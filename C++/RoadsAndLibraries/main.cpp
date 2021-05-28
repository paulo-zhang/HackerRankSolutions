#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

struct city{
    vector<int> adj_cities;
};

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    long totalCost = (long)c_lib * (long)n;
    if(c_lib <= c_road){
        return totalCost;
    }

    vector<city> nodes(n);
    for(int i = 0;i < cities.size();i ++){
        nodes[cities[i][0] - 1].adj_cities.push_back(cities[i][1] - 1);
        nodes[cities[i][1] - 1].adj_cities.push_back(cities[i][0] - 1);
    }
    
    stack<int> s;
    vector<bool> visited(n);

    for(int i = 0;i < cities.size();i ++){
        if(visited[cities[i][0] - 1] && visited[cities[i][1] - 1])continue;

        if(!visited[cities[i][0] - 1]){
            s.push(cities[i][0]);
        }
        
        if(!visited[cities[i][1] - 1]){
            s.push(cities[i][1]);
        }

        visited[cities[i][0] - 1] = true;
        visited[cities[i][1] - 1] = true;

        int count = 2; // Count of cities.
        while(!s.empty()){
            int m = s.top();
            s.pop();

            for(auto a : nodes[m - 1].adj_cities){
                if(!visited[a]){
                    visited[a] = true;
                    count ++;
                    s.push(a + 1); // missed this line in the first place.
                }
            }
        }
        
        totalCost += (count - 1) * (c_road - c_lib); // There are (count - 1) roads to connect count cities.
    }
    
    return totalCost;
}

int main()
{
    ofstream fout("output.txt");
    ifstream fin("input04.txt");

    string q_temp;
    getline(fin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(fin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(fin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

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
