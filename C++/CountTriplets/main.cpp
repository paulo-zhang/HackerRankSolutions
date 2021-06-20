#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);
vector<string> split(const string&);

// Complete the countTriplets function below.
long countTriplets(vector<long> arr, long r) {
    long totalCount = 0;
    unordered_map<long, long> allThePassedNumberCounts;
    unordered_map<long, long> combinationCounts;// Combinations of first and second number.
    for (size_t i = 0; i < arr.size(); i++) {
        
        if (arr[i] % r == 0) {
            long preValue = arr[i] / r;
            totalCount += combinationCounts[preValue];
            // Calculate the combinations of first & second number for future use.
            // This must be after calculating totalCount to pass the test case input02.txt.
            combinationCounts[arr[i]] += allThePassedNumberCounts[preValue];
            // cout << preValue << "-" << arr[i] << "; " << "add: " << combinationCounts[preValue] <<endl;
        }
        
        // This must be the last line to pass test case input02.txt.
        allThePassedNumberCounts[arr[i]] ++;
    }

    return totalCount;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    fstream fin("input02.txt");

    string nr_temp;
    getline(fin, nr_temp);

    vector<string> nr = split(rtrim(nr_temp));

    int n = stoi(nr[0]);

    long r = stol(nr[1]);

    string arr_temp_temp;
    getline(fin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    long ans = countTriplets(arr, r);

    // fout << ans << "\n";

    // fout.close();

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string& str) {
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
