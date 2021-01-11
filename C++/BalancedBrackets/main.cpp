#include <string>
#include <iostream>
#include <stack>

using namespace std;

// Complete the isBalanced function below.
string isBalanced(string str) {
    stack<char> s;
    for (auto it = str.begin(); it != str.end(); it++) {
        if (s.empty()) {
            s.push(*it);
            continue;
        }

        switch (*it) {
        case '}':
            if (s.top() == '{') {
                // matched
                s.pop();
                break;
            }

            s.push(*it);
            break;
        case ')':
            if (s.top() == '(') {
                // matched
                s.pop();
                break;
            }
            s.push(*it);
            break;
        case ']':
            if (s.top() == '[') {
                // matched
                s.pop();
                break;
            }
            s.push(*it);
            break;
        default:
            s.push(*it);
            break;
        }
    }

    return s.size() > 0 ? "NO" : "YES";
}

int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string result = isBalanced(s);

        cout << result << "\n";
    }

    //cout.close();

    return 0;
}
