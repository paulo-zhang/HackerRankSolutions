#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

// Complete the almostSorted function below.
bool isSorted(const vector<int> &arr, int begin, int end, int incr)
 {
     int i = begin;
     while(i != end){
         if(arr[i] > arr[i + incr]) return false;
         
         i += incr;
     }
     
     return true;
 }

void almostSorted(vector<int> arr) {
    // find l.
    int l = -1;
    for(int i = 0; i < arr.size() - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            l = i;
            break;
        }
    }
    
    if(l == -1) {
        cout << "yes";
        return;
    }
    
    // find r;
    int r = -1;
    for(int i = arr.size() - 1; i > 0 && i > l; i --)
    {
        if(arr[i] < arr[i - 1]){
            r = i;
            break;
        }
    }
    
    // can we swap?
    swap(arr[l], arr[r]);
    if((l > 0 && arr[l] < arr[l - 1]) || arr[l] > arr[l + 1] || (r < arr.size() - 1 && arr[r] > arr[r + 1]) || arr[r] < arr[r - 1]){
        cout << "no";
        return;
    }
    
    if(isSorted(arr, l, r, 1))
    {
        cout << "yes\n" << "swap " << l + 1 << " " << r + 1;
        return;
    }
    swap(arr[l], arr[r]); // restore the data back to original
    
    // can we reverse (ascending from the back)?
    if(isSorted(arr, r, l, -1))
    {
        cout << "yes\n" << "reverse " << l + 1 << " " << r + 1;
        return;
    }
    
    cout << "no";
}

int main()
{
    ifstream fin("input22.txt");
    int n;
    fin >> n;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(fin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

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
