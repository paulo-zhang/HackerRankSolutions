#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <deque>

using namespace std;

vector<string> split_string(string);

//https://www.hackerrank.com/challenges/poisonous-plants/forum

//w00tles(https://www.hackerrank.com/w00tles)
//it can be done with a list of stacks *
//
//let's say we start with
//
//6 5 8 7 4 7 3 1 1 10
//
//we'll represent it as a list of stacks like this:
//
//monday 6 > 5, 8 > 7 > 4, 7 > 3 > 1 > 1, 10
//
//each stack is a maximal non - increasing chain
//
//now, to let one day pass :
//
//pop the top element from every stack(excluding the unique leftmost stack).these are the plants that die on this day.
//tuesday 6 > 5, 7 > 4, 3 > 1 > 1, -
//
//now check to see if any adjacent stacks can be merged.here we see that 7 > 4 and 3 > 1 > 1 can be merged to form a longer chain.stacks can be merged in O(1)
//tuesday 6 > 5, 7 > 4 > 3 > 1 > 1
//
//one day has now passed.repeat the process.
//wednesday 6 > 5, 4 > 3 > 1 > 1
//
//wednesday 6 > 5 > 4 > 3 > 1 > 1
//
//now that just one stack remains in our list, we know we are done.
//NB these stacks are linked - list - based and maintain a pointer to their base element.This allows for O(1) merge operations, and O(1) checking of the topand bottom values.

// Complete the poisonousPlants function below.
int poisonousPlants(vector<int> p) {
    vector<int> days(p.size());
    int minPoison = p[0];
    int maxDay = 0;
    stack<int> traversedIndexs;

    traversedIndexs.push(0);

    for (int i = 1; i < p.size(); i++)
    {
        if (p[i] > p[i - 1]) {
            days[i] = 1; // Bigger than previous number, die on the first day.
        }

        minPoison = min(minPoison, p[i]);// Mark mallest.

        while (!traversedIndexs.empty() && p[traversedIndexs.top()] >= p[i]) // Smaller than previous number (belong to current stack) or the prevoius stack top (merge with previous stack).
        {
            if (p[i] > minPoison) {
                days[i] = max(days[i], days[traversedIndexs.top()] + 1); // die after previous number (orignal stack) or the number of previous stack (merge stack scenario).
            }

            traversedIndexs.pop(); // Remove trace, since this number won't be relevant to the numbers behind.
        }

        maxDay = max(maxDay, days[i]); // Is this the max?
        traversedIndexs.push(i); // Mark trace for future number.
    }

    return maxDay;
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
