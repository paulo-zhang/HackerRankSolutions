#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'insertionSort' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
 // Same as: https://www.hackerrank.com/challenges/ctci-merge-sort/problem
 // More slolutions: https://afteracademy.com/blog/inversion-count-in-an-array
long merge(vector<int> &arr, vector<int> &temp, int start, int mid, int end){
     long count = 0;
     int i = start;
     int j = mid;
     int n = start;
     
     while(i < mid && j < end){
         if(arr[i] <= arr[j]){
             temp[n ++] = arr[i ++];
         }
         else{
             temp[n ++] = arr[j ++];
             count += mid - i;
         }
     }
     
     while(i < mid){
         temp[n ++] = arr[i ++];
     }
     
     while(j < end){
         temp[n ++] = arr[j ++];
     }
     
     while(start < end){
         arr[start] = temp[start];
         start ++;
     }
     
     return count;
}
 
 long mergeSort(vector<int> &arr, vector<int> &temp, int start, int end){
     if(end - start <= 1) return 0;
     
     int mid = start + (end - start) / 2;
     
     long count = 0;
     count += mergeSort(arr, temp, start, mid);
     count += mergeSort(arr, temp, mid, end);
     
     count += merge(arr, temp, start, mid, end);
     
     return count;
 }

long insertionSort(vector<int> &arr) {
    vector<int> temp(arr.size());
    return mergeSort(arr, temp, 0, arr.size());
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input07.txt");

    string t_temp;
    getline(fin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(fin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(fin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        long result = insertionSort(arr);

        cout << result << "\n";
    }

    // fout.close();

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
