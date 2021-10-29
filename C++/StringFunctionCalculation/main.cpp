#include <bits/stdc++.h>

using namespace std;

struct Suffix{
    int index; // original index.
    int rank1;
    int rank2;
};

bool compare(Suffix suffix1, Suffix suffix2) {
        if(suffix1.rank1 < suffix2.rank1){
            return true;
        }
        else if(suffix1.rank1 > suffix2.rank1) {
            return false;
        }
        
        return suffix1.rank2 < suffix2.rank2;
    }

// https://www.geeksforgeeks.org/suffix-array-set-1-introduction/
// https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
// Sort suffix strings with O(nLogn) algorithm
vector<Suffix> getSuffixArray(const string& text){
    vector<Suffix> suffixArr(text.size());

    auto n = suffixArr.size();

    // Assign original index & rank1.
    for(int i = 0;i < n; ++i){
        suffixArr[i].index = i;
        suffixArr[i].rank1 = text[i] - 'a';
    }

    // Assign rank2.
    suffixArr.back().rank2 = -1; // The last one has no next rank.
    for(int i = 1;i < n; ++i){
        suffixArr[i - 1].rank2 = suffixArr[i].rank1; // Next rank.
    }

    sort(suffixArr.begin(), suffixArr.end(), compare); // Sort by the ranks.

    for(int k = 2; k < n; k = 2*k){
        vector<int> selfIndexes(n); // Index position of suffix.
        // Re-assign rank1
        int preRank1 = suffixArr[0].rank1, preRank2 = suffixArr[0].rank2;
        suffixArr[0].rank1 = 0;
        selfIndexes[suffixArr[0].index] = 0;
        for(int i = 1;i < n; ++i){
            selfIndexes[suffixArr[i].index] = i; // Save the index position of current suffix, to help get the next suffix.

            if(suffixArr[i].rank1 == preRank1 && suffixArr[i].rank2 == preRank2){
                suffixArr[i].rank1 = suffixArr[i - 1].rank1;
            }
            else{
                suffixArr[i].rank1 = suffixArr[i - 1].rank1 + 1;
                preRank1 = suffixArr[i].rank1;
                preRank2 = suffixArr[i].rank2;
            }
        }

        // Re-assign rank2.
        for(int i = 0; i < n; ++i){
            int nextIndex = suffixArr[i].index + k;
            suffixArr[i].rank2 = nextIndex < n ? suffixArr[selfIndexes[nextIndex]].rank1 : -1;
        }

        sort(suffixArr.begin(), suffixArr.end(), compare); // Sort by the ranks.
    }
    
    return suffixArr;
}

// https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/
// kasai’s Algorithm 
void makeLcp(Suffix suffix){
    
}

// https://www.hackerrank.com/challenges/string-function-calculation/forum/comments/1031872
// https://www.hackerrank.com/challenges/string-function-calculation/forum/comments/1024871
int maxValue(string t) {
    int maxVal = 0;
    vector<Suffix> suffixArr = getSuffixArray("banana");
    for(auto s : suffixArr){
        cout << s.index << "\n";
    }

    return maxVal;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t;
    getline(cin, t);

    int result = maxValue(t);

    fout << result << "\n";

    fout.close();

    return 0;
}
