#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <fstream>

using namespace std;
// Problem: https://www.hackerrank.com/contests/code-cpp-may-2015/challenges/almost-equal-strings
class Solution{
    struct RankNode{int first, second, index;};
    string s;// The original string.
    vector<int> suffixArr; // Suffix array.
    vector<int> reversedArr; // reverse array of the suffix array.
    // The LCP (Longest Common Prefix) array is an array of size 'N' (size of string 'S') where lcpArr[i], for 'i' from 0 to N - 1, contains lengths of the longest common prefix between the suffixes SUF[i] and SUF[i+1].
    vector<int> lcpArr; 
    vector<vector<int>> lookup; // Sparse Table Algorithm. https://www.geeksforgeeks.org/range-minimum-query-for-static-array/
    // Build suffix array using the result of position 2i-1 to sort position 2i: O(n * Log2n). 
    // We first sort all suffixes according to the first character, then according to the first 2 characters, then first 4 characters, and so on.
    // Optimize to O(n * Logn) with radix sort which uses counting sort to achieve O(Logn).
    // https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
    void createSuffixArray(){
        // Helper rank array.
        vector<RankNode> rank(s.size());
        reversedArr.resize(rank.size());
        
        // Assign position 0, 1.
        for(int i = 0; i < s.size() - 1; i++){
            rank[i].index = i;
            rank[i].first = s[i] - 'a'; // The first character of the suffix string.
            rank[i].second = s[i + 1] - 'a';// The second character of the suffix string.
        }
        //Assign the last rank.
        int lastIndx = s.size() - 1;
        rank[lastIndx].index = lastIndx;
        rank[lastIndx].first = s.back() - 'a';
        rank[lastIndx].second = -1; // Cannot put into for loop.
        
        // Sort position 0, 1.
        sortRank(rank);
        
        // At this point, all suffixes are sorted according to first
        // 2 characters.  Let us sort suffixes according to first 4 characters, then first 8 and so on.
        for(int k = 4; k < 2 * s.size(); k *= 2){
            assignNewRank(rank);
            // Assign position k to second ranking index.
            assignCharacterRank(rank, k);
            // Sort position k.
            sortRank(rank);
        }
        
        // Copy result.
        for(int i = 0; i < rank.size(); i++){
            suffixArr.push_back(rank[i].index);
        }
    }
    
    // IMPORTANT: When we assign the next rank for k, we assign the next k/2 sorted string's rank to k string's rank, not the k character's rank.
    void assignCharacterRank(vector<RankNode>& rank, int k){
        for(int i = 0; i < rank.size(); i++){
            int next = rank[i].index + k / 2;
            rank[i].second = (next < s.size()) ? rank[reversedArr[next]].first : -1;
        }
    }
    
    // Sort rank according to first & second.
    void sortRank(vector<RankNode>& rank){
        sort(rank.begin(), rank.end(), [](const auto& r1, const auto& r2){
            if(r1.first != r2.first){
                return r1.first < r2.first;
            }
            
            return r1.second < r2.second;
        });

        // Maintain reversed array.
        for(int i = 0; i < rank.size(); i++){
            reversedArr[rank[i].index] = i;
        }
    }
    
    // Assign new rank. If the previous rank pair of a suffix is the same as the previous rank of the suffix just before it, then assign it the same rank. Otherwise, assign a rank of the previous suffix plus one. 
    void assignNewRank(vector<RankNode>& rank){
        int preRank = rank[0].first;
        rank[0].first = 0;
        for(int i = 1; i < rank.size(); i++){
            if(preRank == rank[i].first && rank[i - 1].second == rank[i].second){
                rank[i].first = rank[i - 1].first;
            }
            else{
                preRank = rank[i].first;
                rank[i].first = rank[i - 1].first + 1;
            }
        }
    }
    
    // LCP array construction: For the suffix starting at index 'i', LCP is 'len'. Now, the LCP for the suffix beginning at index 'i +1' will be at least 'len - 1' if 'len' is greater than zero. It is because we are removing the first matching character from both the suffix strings, which decreases the matching prefix characters for the suffixes by one. https://www.codingninjas.com/codestudio/library/longest-common-prefix-from-suffix-array
    void generateLCPArray(){
        lcpArr.resize(reversedArr.size());
        
        for(int i = 0; i < reversedArr.size(); ++ i){
            int index = reversedArr[i];
            if(index + 1 >= suffixArr.size()){
                lcpArr.back() = -1; 
                continue;
            }
            
            int len = (i == 0 ? 0 : lcpArr[reversedArr[i - 1]] - 1);
            if(len < 0) len = 0;

            int next = suffixArr[index + 1];
            while(len < + i < s.size() && len + next < s.size()){
                if(s[len + i] == s[len + next]){
                    len ++;
                }
                else{
                    break;
                }
            }

            // cout << "lcp: " << s.substr(i) << ", " << s.substr(next) << ": " << len << "\n";
            lcpArr[index] = len;
        }
        
        lcpArr.pop_back(); // The last one is -1;
    }
    
    // Build lookup according to formular: lookup[i][j] = minInRange(i, i + 2 ^ j - 1) = min(lookup[i][j - 1], lookup[i + 2 ^ (j - 1)][j - 1]);
    void generateLookup(){
        int col = log2(lcpArr.size()) + 1, row = lcpArr.size();
        lookup.resize(row, vector<int>(col, -1));
        
        for(int i = 0; i < lookup.size(); ++i){
            lookup[i][0] = lcpArr[i];
        }
        
        for(int j = 1; j < col; ++j){
            for(int i = 0; i < row; ++i){
                if(i + (1 << j) - 1 >= row) break; // The range is out of array size.
                lookup[i][j] = min(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]); // Use the super formular: lookup[i][j] = min(lookup[i][j - 1], lookup[i + 2 ^ (j - 1)][j - 1]);
            }
        }
    }
    
    // Perform range minimum query using sparse table: lookup[i][j] = minInRange(i, i + 2 ^ j - 1) = min(lookup[i][j - 1], lookup[i + 2 ^ (j - 1)][j - 1]);.
    int rangeMinimumQuery(int index1, int index2){
        if(index1 > index2){
            swap(index1, index2);
        }
        
        index2 --;// The lcp of i and i + 1 suffix is saved in lcpArr[i], no need to check lcpArr[i + 1].
        // cout <<"RMQ: " << index1 << "-" << index2 << ": ";
        int minVal = INT_MAX;
        while(index1 <= index2){
            // index2 = i + 2 ^ j - 1;
            int j = log2(index2 + 1 - index1);
            minVal = min(minVal, lookup[index1][j]);
            index1 += (1 << j); // Next start: i + 2 ^ j.
        }
        
        // cout << minVal << "\n";
        return minVal;
    }
    
    int commonPrefixLength(int low1, int high1, int low2, int high2){
        if(low1 > high1 || low2 > high2) return 0;
        
        if(low1 == low2) return high1 - low1 + 1; // Same suffix start.
        
        int index1 = reversedArr[low1], index2 = reversedArr[low2];// Get the suffix array index.
        return rangeMinimumQuery(index1, index2);
    }
    
    bool isSimilar(int low1, int high1, int low2, int high2){
        int maxLen = min(high1 - low1 + 1, high2 - low2 + 1) - 1;
        
        int len1 = commonPrefixLength(low1, high1, low2, high2);
        return len1 >= maxLen || len1 + commonPrefixLength(low1 + len1 + 1, high1, low2 + len1 + 1, high2) >= maxLen;
    }
public:
    void prepare(const string &input) {
        s = input;
        createSuffixArray();
        generateLCPArray();
        /*for(int n : suffixArr){
            cout << n << " ";
        }
        cout << "lcp:\n";
        for(int n : lcpArr){
            cout << n << " ";
        }
        cout << "\n";
        for(int n : reversedArr){
            cout << n << " ";
        }
        cout << "\n";*/

        generateLookup();
    }
    
    // The LCP array only contains the length of the longest common prefix of every pair of consecutive suffixes in the suffix array.
    // lcp(i, j) = rangeMinimumQuery(reversedArr[i], reversedArr[j])
    string query(int low1, int high1, int low2, int high2){
        // cout << "query: " << low1 << "-" << high1 << ", " << low2 << "-" << high2 << ", " << s.substr(low1, high1-low1+1) << ", " << s.substr(low2, high2-low2+1) << "\n";
        if(high1 - low1 != high2 - low2){
            return "DIFFERENT";// The difference must be > 1.
        }
        
        if(low1 == low2){
            return "SIMILAR"; // Same start position, same suffix strings.
        }
        
        if(isSimilar(low1, high1, low2, high2)){
            return "SIMILAR"; // Only one letter is different.
        }
        
        return "DIFFERENT";
    }
};

int main() {
    int n;
    string input;
    cin >> n;
    cin >> input;
    cin >> n;
    Solution solution;
    solution.prepare(input);
    
    ofstream out("output.txt");

    while(n-- > 0){
        int i, j, k, l;
        cin >> i >> j >> k >> l;
        out << solution.query(--i, --j, --k, --l) << "\n";
    }
    
    return 0;
}