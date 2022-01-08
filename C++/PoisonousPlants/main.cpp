#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <deque>

using namespace std;

vector<string> split_string(string);

int poisonousPlants_Non_Optimized(vector<int> p) {
    int maxDays = 0;
    int smallest = p[0];
    vector<int> days(p.size(), 0);
    
    for(int i = 1;i < p.size(); i ++) {
        if(p[i] < smallest) {
            smallest = p[i];
        }
        else if(p[i] > p[i - 1]) {
            days[i] = 1;
            maxDays = max(maxDays, 1);
        }
        else {
            int j = i - 1;
            while(j >= 0 && p[j] >= p[i]) {
                if(days[j] > 0) {
                    days[i] = max(days[i], days[j] + 1);
                    maxDays = max(days[i], maxDays);
                }
                
                j --;
            }
        }
    }
    
    return maxDays;
}

int poisonousPlants(vector<int> p) {
    int maxDays = 0;
    int smallest = p[0];
    vector<int> days(p.size(), 0);
    stack<int> traversedIndexs; // Keep track of the relevant plants that have passed and relevant to the future.
    
    for(int i = 1;i < p.size(); i ++) {
        if(p[i] < smallest){ // p[i] is the smallest so far, this won't die.
            smallest = p[i];
        }
        else if(p[i] > p[i - 1]) { // bigger than the immediate left, die at the first day
            days[i] = 1;
            maxDays = max(maxDays, 1);
        }
        else { // Smaller or equal to the immediate left.
            while(!traversedIndexs.empty()) {
                int j = traversedIndexs.top();
                if(p[j] < p[i])break; // i must die before j, and j is relevant to the plants behind.
                
                // i dies after all non-smaller plants on its left die - the die day is the biggest die day on its left + 1.
                if(days[j] > 0) { // Only case when days[j] == 0 is that all the values are the same.
                    days[i] = max(days[i], days[j] + 1);
                    maxDays = max(days[i], maxDays);
                }
                
                traversedIndexs.pop(); // Remove trace, since this plants won't be relevant to the plants behind, because p[j] >= p[i]. This is key to better performance.
            }
        }
        
        traversedIndexs.push(i);
    }
    
    return maxDays;
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = poisonousPlants(p);

    cout << result << "\n";

    //fout.close();

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
