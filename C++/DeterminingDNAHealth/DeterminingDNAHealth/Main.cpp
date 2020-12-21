#include <string>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <algorithm>    // std::unique, std::distance
#include<algorithm>
#include <queue>

using namespace std;

vector<string> split_string(string);
struct Strand {
    int first;
    int last;
    string d;
    int health;
};

int countFreq(const string& txt, const string& pat)
{
    int M = pat.length();
    int N = txt.length();
    int res = 0;

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        /* For current index i, check for
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
        if (j == M)
        {
            res++;
        }
    }
    return res;
}

// returns count of occurrences of 'sub' in 'str'
int countSubstring(const string& str, const string& sub)
{
    if (sub.length() == 0) return 0;

    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
        offset = str.find(sub, offset + 1))
    {
        ++count;
    }

    return count;
}

int getOccurrency(string text, const string &keyword)
{
    int j = 0;
    int c = 0;
    int len2 = text.length();
    while (true)
    {
        j = text.find(keyword);
        if (j != -1)
        {
            c++;
            text = text.substr(j + 1);
            len2 = text.length();
            j = 0;
            if (len2 == 0)
            {
                return c;
            }
            continue;
        }
        if (j == -1)
        {
            return c;
            break;
        }
    }
}

void printGeneHealth(vector<string> genes, vector<int> health, list<Strand> strands) {
    int minHealth = -1, maxHealth = 0;

    for (auto strandIt = strands.begin(); strandIt != strands.end(); strandIt++) {
        map<string, int> searchedMap;
        for (auto i = strandIt->first; i <= strandIt->last; i++) {
            string gen = genes[i];
            auto mapIt = searchedMap.find(gen);
            if (mapIt != searchedMap.end()) {
                // same gen searched before
                strandIt->health += health[i] * mapIt->second;
                continue;
            }

            // calculate health.
            int count = countSubstring(strandIt->d, gen);

            searchedMap[gen] = count;
            strandIt->health += health[i] * count;
        }

        if (minHealth == -1 || minHealth > strandIt->health) {
            minHealth = strandIt->health;
        }
        if (maxHealth < strandIt->health) {
            maxHealth = strandIt->health;
        }
    }

    cout << minHealth << " " << maxHealth;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    vector<string> genes_temp = split_string(genes_temp_temp);

    vector<string> genes(n);

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];

        genes[i] = genes_item;
    }

    string health_temp_temp;
    getline(cin, health_temp_temp);

    vector<string> health_temp = split_string(health_temp_temp);

    vector<int> health(n);

    for (int i = 0; i < n; i++) {
        int health_item = stoi(health_temp[i]);

        health[i] = health_item;
    }

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    list<Strand> strands;
    for (int s_itr = 0; s_itr < s; s_itr++) {
        string firstLastd_temp;
        getline(cin, firstLastd_temp);

        vector<string> firstLastd = split_string(firstLastd_temp);

        Strand s;
        s.first = stoi(firstLastd[0]);
        s.last = stoi(firstLastd[1]);
        s.d = firstLastd[2];
        s.health = 0;

        strands.push_back(s);
    }

    printGeneHealth(genes, health, strands);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char& x, const char& y) {
        return x == y and x == ' ';
        });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
