#include <bits/stdc++.h>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) {
    long candy_num;
    vector<int> dis(arr.size(), 0);
    dis[0] = 1;
    candy_num = 1;
    
    int desc_index = -2;
    for(int i = 1; i < arr.size(); i ++){
        if(arr[i] > arr[i - 1]){
            dis[i] = dis[i - 1] + 1;
            desc_index = -2;
            candy_num += dis[i];
        }
        else {
            if(desc_index == -2){
                desc_index = i - 1;
            }
            
            if(desc_index == 0 || i - desc_index == dis[desc_index] && arr[desc_index] != arr[desc_index + 1]){
                desc_index --;
            }
            
            dis[i] = 1;
            if(arr[i] == arr[i - 1]){
                candy_num += 1;
                desc_index = i - 1;
            }
            else{
                candy_num += i - desc_index;
            }
        }
    }
    cout << "\n";
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
