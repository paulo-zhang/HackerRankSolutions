#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<functional>
#include<math.h>

using namespace std;

string ltrim(const string&);
string rtrim(const string&);

/*
 * Complete the 'getMaxArea' function below.
 *
 * The function is expected to return a LONG_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER w
 *  2. INTEGER h
 *  3. BOOLEAN_ARRAY isVertical
 *  4. INTEGER_ARRAY distance
 */

/******************
 * https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/
 * ****************/
class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        long maxWidth = 0, maxHeight = 0;
        
        // Sort the cuts.
        sort(verticalCuts.begin(), verticalCuts.end());
        sort(horizontalCuts.begin(), horizontalCuts.end());
        
        // Add cuts at 0 and end.
        verticalCuts.insert(verticalCuts.begin(), 0);
        verticalCuts.push_back(w);
        horizontalCuts.insert(horizontalCuts.begin(), 0);
        horizontalCuts.push_back(h);
        
        // Find the max width piece.
        for(size_t i = 1; i < verticalCuts.size();i ++){
            maxWidth = max((int)maxWidth, verticalCuts[i] - verticalCuts[i - 1]);
        }
        
        // Find the max height piece.
        for(size_t i = 1; i < horizontalCuts.size();i ++){
            maxHeight = max((int)maxHeight, horizontalCuts[i] - horizontalCuts[i - 1]);
        }
        
        return (int)((maxWidth * maxHeight) % (long)(pow(10, 9) + 7));
    }
};

vector<long> getMaxArea(int w, int h, vector<bool> isVertical, vector<int> distance) {
    vector<int> verticalSegments;
    vector<int> horizontalSegments;
    verticalSegments.insert(verticalSegments.begin(), w);
    horizontalSegments.insert(horizontalSegments.begin(), h);

    vector<long> result(isVertical.size());
    for (size_t i = 0; i < isVertical.size(); i++) {
        vector<int>* pSegments = isVertical[i] ? &verticalSegments : &horizontalSegments;

        int sum = 0;
        for (auto it = pSegments->begin(); it != pSegments->end(); it++) {
            sum += *it;
            int j = std::distance(pSegments->begin(), it);
            int dis = distance[j];

            if (sum > dis) {
                // Devide the segements;
                int newSeg = *it - (sum - dis);
                *it = sum - dis;
                pSegments->insert(it, newSeg);
                break;
            }
        }

        result[i] = *max_element(verticalSegments.begin(), verticalSegments.end()) * *max_element(horizontalSegments.begin(), horizontalSegments.end());
    }

    return result;
}

int main()
{
    //ofstream cout(getenv("OUTPUT_PATH"));

    string w_temp;
    getline(cin, w_temp);

    int w = stoi(ltrim(rtrim(w_temp)));

    string h_temp;
    getline(cin, h_temp);

    int h = stoi(ltrim(rtrim(h_temp)));

    string isVertical_count_temp;
    getline(cin, isVertical_count_temp);

    int isVertical_count = stoi(ltrim(rtrim(isVertical_count_temp)));

    vector<bool> isVertical(isVertical_count);

    for (int i = 0; i < isVertical_count; i++) {
        string isVertical_item_temp;
        getline(cin, isVertical_item_temp);

        bool isVertical_item = stoi(ltrim(rtrim(isVertical_item_temp))) != 0;

        isVertical[i] = isVertical_item;
    }

    string distance_count_temp;
    getline(cin, distance_count_temp);

    int distance_count = stoi(ltrim(rtrim(distance_count_temp)));

    vector<int> distance(distance_count);

    for (int i = 0; i < distance_count; i++) {
        string distance_item_temp;
        getline(cin, distance_item_temp);

        int distance_item = stoi(ltrim(rtrim(distance_item_temp)));

        distance[i] = distance_item;
    }

    vector<long> result = getMaxArea(w, h, isVertical, distance);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    //cout.close();

    return 0;
}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
