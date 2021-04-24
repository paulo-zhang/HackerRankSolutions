#include <bits/stdc++.h>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
    vector<int> dis(arr.size(), 1);
    for(int i = 1;i < arr.size();i ++){
        if(arr[i] > arr[i - 1]){
            dis[i] = dis[i - 1] + 1;
        }
    }
    
    long candy_num = dis[arr.size() - 1];
    for(int i = arr.size() - 2;i >= 0;i --){
        if(arr[i] > arr[i + 1]){
            int num = dis[i + 1] + 1;
            if(num > dis[i]){
                dis[i] = num;
            }
        }
        
        candy_num += dis[i];
    }
    
    return candy_num;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    fstream fin("input07.txt");

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    cout << result << "\n";

    fout.close();

    return 0;
}
