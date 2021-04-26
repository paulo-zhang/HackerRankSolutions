#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

long Decibinary2Decimal(long n){
    long mod = 10;
    long dec = 0;
    int ex = 0;
    
    while(n > 0){
        int a = n % mod;
        n /= mod;

        dec += a * pow(2, ex ++);
    }

    return dec;
}

void print_pattern(){
    for(int i = 0;i < 50;i ++){
        if(i % 10 == 0){
            cout <<"\n";
        }

        for(int j = i * 10;j < 10 * (i + 1);j ++){
            cout << right << setw(4) << j << "-" << left << setw(4) << Decibinary2Decimal(j) << " ";
        }

        cout << "\n";
    }
}

/*
 * Complete the 'decibinaryNumbers' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER x as parameter.
 */

long decibinaryNumbers(long x) {
    vector<int> decimal_count(28, 0);// number count for the first decimal metrix.
    for(int i = 0;i < 10;i ++){
        for(int j = i * 10;j < 10 * (i + 1);j ++){
            decimal_count[Decibinary2Decimal(j)] ++;
        }
    }

    int n = 0;
    long count = 0;
    // The count of a decmial n in metrix i is decimal_count[n - 4i].
    while(n < x){
        for(int k = 0; n - 4 * k >= 0; k++){ // Go through the metrix to count.
            int index = n - 4 * k;
            
            long temp = decimal_count[index] + count;
            if(temp >= x){// Found it.
                // Find the exact position
                int m = x - count;
                for(int i = 0;i < 10;i ++){
                    for(int j = i * 10;j < 10 * (i + 1);j ++){
                        if(Decibinary2Decimal(j) == index){
                            m --;
                            if(m == 0){
                                return k * 100 + j;
                            }
                        }
                    }
                }
            }

            count = temp;
        }

        n ++;
    }
    
    cout << "weird!";
    return 0;
}

int main()
{
    ofstream fout("output.txt");

    print_pattern();

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string x_temp;
        getline(cin, x_temp);

        long x = stol(ltrim(rtrim(x_temp)));

        long result = decibinaryNumbers(x);

        fout << result << "\n";
    }

    fout.close();

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
