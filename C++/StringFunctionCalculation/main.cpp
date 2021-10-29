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
                preRank1 = suffixArr[i].rank1;
                preRank2 = suffixArr[i].rank2;
                suffixArr[i].rank1 = suffixArr[i - 1].rank1 + 1;
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
// Let lcp of suffix beginning at txt[i] be k. If k is greater than 0, then lcp for suffix beginning at txt[i+1] will be at-least k-1. 
// The reason is, relative order of characters remain same. If we delete the first character from both suffixes, we know that at least k - 1 characters will match. 
// For example for substring “ana”, lcp is 3, so for string “na” lcp will be at-least 2. Refer this for proof.
vector<int> getLcp(const vector<Suffix>& suffixArr, const string& text){
    int n = suffixArr.size();
    vector<int> lcp(n);
    vector<int> selfIndexes(n); // The index position of the suffixes.

    for(int i = 0;i < n; ++i){
        selfIndexes[suffixArr[i].index] = i;
    }

    int leastMatch = 0; // ... at least k - 1 characters will match
    for(int i = 0;i < n; ++i){ // i represents original index. In order to use pre-calculated k, we don't compare strings in suffixArr's order, but instead use original index's order.
        int next = selfIndexes[i] + 1; // The next suffix index  of the i-th string in suffixArr.
        if(next >= n) continue;

        int p = leastMatch + i;
        int q = leastMatch + suffixArr[next].index;
        while(p < text.size() && q < text.size() && text[p] == text[q]){ // compare from leastMatch.
            leastMatch ++;
            p ++;
            q ++;
        }

        lcp[selfIndexes[i]] = leastMatch; // Don't forget the i-th string's position is selfIndexes[i].
        if(leastMatch > 0){
            leastMatch --; // Next least matches.
        }
    }

    lcp[n - 1] = 0;
    return lcp;
}

// https://www.hackerrank.com/challenges/string-function-calculation/forum/comments/1024871
int findLargestRetangleInHistogram(vector<int> lcp){
    stack<int> s;
    
    int maxRect = 0;
    int n = 0;
    while(n < lcp.size() || !s.empty()){
        if(s.empty() || n < lcp.size() && lcp[s.top()] <= lcp[n]) {
            s.push(n);
            n ++;
        }
        else {
            int top = s.top();
            s.pop();
            maxRect = max(maxRect, (lcp[top] + 1) * (s.empty() ? n : n - s.top() - 1));
        }
    }

    return maxRect;
}

// https://www.hackerrank.com/challenges/string-function-calculation/forum/comments/1031872
int maxValue(string t) {
    
    vector<Suffix> suffixArr = getSuffixArray(t);
    for(auto s : suffixArr){
        cout << s.index << " ";
    }
    cout << "\n";

    vector<int> lcp = getLcp(suffixArr, t);
    for(auto n : lcp){
        cout << n << " ";
    }

    cout << "\n";
    int maxVal = 0;
    maxVal = findLargestRetangleInHistogram(lcp);
    cout << maxVal;
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
