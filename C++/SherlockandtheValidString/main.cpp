#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Complete the isValid function below.
string isValid(string s) {
    map<char, int> m;
    for (auto c : s) {
        m[c] ++;
    }

    map<int, int> countMap;// it->first: occurency, it->second: letter count.
    for (auto p : m) {
        countMap[p.second] ++;
        if (countMap.size() > 2) {
            return "NO"; // more than two differences
        }
    }

    auto it = countMap.begin(); // first element 
    auto it2 = it;
    advance(it2, 1); // second element

    cout << "p1: " << it->first << "-" << it->second << " p2: " << it2->first << "-" << it2->second << endl;

    if (countMap.size() != 0 &&
        (countMap.size() == 1 || // same occurent for all letters
        it->first == 1 && it->second == 1 || // only letter and appear only once
        it2->second == 1 && it2->first - it->first == 1)) // only letter and appear once more than others
    {
        return "YES";
    }

    return "NO"; // probably size == 0
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    cout << result << "\n";

    //fout.close();

    return 0;
}