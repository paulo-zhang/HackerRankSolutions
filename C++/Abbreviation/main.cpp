#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) {
    int a_start = 0;
    a += 'z' + 1;
    b += 'z' + 1;
    
    for(int i = 0;i < b.size();i ++){
        bool matched = false;
        for(int j = a_start;j < a.size(); j++){
            if(!matched && (a[j] == b[i] + 'a' - 'A' || a[j] == b[i])){
                a_start = j + 1;
                // cout << "match: " << i << "-" << j << ", ";
                matched =true;
                break;
            }
            else if(a[j] < 'a'){
                // Not matched uppercase.
                int k = i - 1;
                while(k >= 0 && a[j] != b[k]){k--;}
                
                if(k < 0){
                    return "NO";
                }

                a_start = j + 1;
                i = k; // back to k.
                matched = true;
                break;
            }
        }
        
        if(!matched){
            return "NO";
        }
    }
    
    return "YES";
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));
    ifstream fin("input14.txt");

    int q;
    fin >> q;
    fin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(fin, a);

        string b;
        getline(fin, b);

        string result = abbreviation(a, b);

        cout << result << "\n";
    }

    // fout.close();

    return 0;
}
