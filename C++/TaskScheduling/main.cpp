#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'taskScheduling' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER d
 *  2. INTEGER m
 */

struct Task{
    int d;
    int m;
    int t;
};

auto cmp = [](const auto& t1, const auto& t2){
    // if(t1.m < t2.m) return true;
    // if(t1.m > t2.m) return false;
    
    return t1.d < t2.d; 
};

multiset<Task, decltype(cmp)> tasks(cmp);
int overshoots = 0;
int taskScheduling(int d, int m) {
    auto it = tasks.insert({d, m});
    
    int time = 0;
    if(it != tasks.begin() && tasks.size() > 0){
        auto pre_it = it;
        advance(pre_it, -1);
        time = pre_it->t;
    }
    
    while(it != tasks.end()){
        time += it->m;
        const_cast<int&>(it->t) = time; // I swear this is not the key.
        overshoots = max(overshoots, time - it->d);
        it ++;
    }
    
    return overshoots;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int d = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int result = taskScheduling(d, m);

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
