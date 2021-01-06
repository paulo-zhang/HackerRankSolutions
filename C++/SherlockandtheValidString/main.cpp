#include <map>
#include <string>
#include <iostream>

using namespace std;

// Complete the isValid function below.
string isValid(string s) {
    map<char, int> m;
    for (auto c: s) {
        m[c] ++;
    }

    map<int, int> countMap;// it->first: occurency, it->second: letter count.
    for (auto it = m.begin(); it != m.end(); it++) {
        cout << it->first << "-" << it->second << " ";
        auto countIt = countMap.find(it->second);
        if (countIt == countMap.end()) {
            countMap[it->second] = 1;
            if (countMap.size() > 2) {
                return "NO";
            }
        }
        else {
            countIt->second++;
        }
    }

    int size = countMap.size();
    auto it = countMap.begin();
    auto it2 = it++;
    if (size == 1 || // same occurent
        size == 2 && (it->first == 1 && it->second == 1 || it2->first == 1 && it2->second == 1 || // only letter and appear only onice
            it->second == 1 && it->first - it2->first == 1 || it2->second == 1 && it2->first - it->first == 1)) // only letter and appear once more than others
    {
        return "YES";
    }

    return "NO";
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