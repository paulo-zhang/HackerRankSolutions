#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Complete the minimumBribes function below.
void minimumBribes(vector<int> q) {
    // Bubble sort
    vector<int> counts(q.size(), 0);
    int totalCount = 0;

    bool swapped = true;
    for (int i = 0; swapped && i < q.size() - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < q.size() - 1 - i; j++) {
            if (q[j] > q[j + 1]) {
                swapped = true;
                counts[q[j] - 1] ++;
                totalCount++;
                if (counts[q[j] - 1] > 2) {
                    cout << "Too chaotic" << endl;
                    return;
                }

                int temp = q[j];
                q[j] = q[j + 1];
                q[j + 1] = temp;
            }
        }
    }

    cout << totalCount << endl;
}

/// <summary>
/// Solution: https://www.hackerrank.com/challenges/new-year-chaos/forum/comments/143969
/// Count the brided number.
/// </summary>
/// <param name="q"></param>
void minimumBribes2(vector<int> q)
{
    int ans = 0;
  for(int i = q.size() - 1; i >= 0; i --) {
      if(q[i] > i + 3) { // Move more than two steps ahead.
          cout << "Too chaotic\n";
          return;
      }
      
      int pre = max(0, q[i] - 2); // q[i] - 2: the furtest that q[i]'s immediate after element can move ahead to.
      while(pre < i) {
          if(q[pre] > q[i]) { // The element that moves ahead of q[i]
              ans ++; 
          }
          
          pre ++;
      }
  }
  
  cout << ans << "\n";
}

/// <summary>
/// Solution: https://www.hackerrank.com/challenges/new-year-chaos/forum/comments/487629
/// Queue scenario
/// </summary>
/// <param name="q"></param>
void minimumBribes1(vector<int> q) {
    int totalBribes = 0;

    int expectedFirst = 1;
    int expectedSecond = 2;
    int expectedThird = 3;

    for (unsigned int i = 0; i < q.size(); ++i) {
        if (q[i] == expectedFirst) { // q[i] doesn't move.
            expectedFirst = expectedSecond;
            expectedSecond = expectedThird;
            ++expectedThird;
        }
        else if (q[i] == expectedSecond) { // q[i] moves one step ahead.
            ++totalBribes;
            expectedSecond = expectedThird;
            ++expectedThird;
        }
        else if (q[i] == expectedThird) { // q[i] moves two steps ahead.
            totalBribes += 2;
            ++expectedThird;
        }
        else { // q[i] moves more than one step.
            cout << "Too chaotic" << endl;
            return;
        }
    }

    cout << totalBribes << endl;
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

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
