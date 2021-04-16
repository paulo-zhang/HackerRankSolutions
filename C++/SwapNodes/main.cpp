#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void traverseTree(vector<vector<int>>& indexes, int node, vector<int>& result) {
    if (node == -1) return;

    traverseTree(indexes, indexes[node - 1][0], result); // Left
    result.push_back(node);// In order
    traverseTree(indexes, indexes[node - 1][1], result); // Right
}

void swap(vector<vector<int>>& indexes, int level, int k, int node) {
    if (node == -1) return;

    if (level % k == 0) {
        swap(indexes[node - 1][0], indexes[node - 1][1]);
    }

    swap(indexes, level + 1, k, indexes[node - 1][0]);// left
    swap(indexes, level + 1, k, indexes[node - 1][1]); // right
}
/*
 * Complete the swapNodes function below.
 */
vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    vector<vector<int>> results;

    for (int i = 0; i < queries.size(); i++) {
        int k = queries[i];
        swap(indexes, 1, k, 1);

        vector<int> result;
        traverseTree(indexes, 1, result);
        results.push_back(result);
    }

    return results;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> indexes(n);
    for (int indexes_row_itr = 0; indexes_row_itr < n; indexes_row_itr++) {
        indexes[indexes_row_itr].resize(2);

        for (int indexes_column_itr = 0; indexes_column_itr < 2; indexes_column_itr++) {
            cin >> indexes[indexes_row_itr][indexes_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int queries_count;
    cin >> queries_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> queries(queries_count);

    for (int queries_itr = 0; queries_itr < queries_count; queries_itr++) {
        int queries_item;
        cin >> queries_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        queries[queries_itr] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int result_row_itr = 0; result_row_itr < result.size(); result_row_itr++) {
        for (int result_column_itr = 0; result_column_itr < result[result_row_itr].size(); result_column_itr++) {
            cout << result[result_row_itr][result_column_itr];

            if (result_column_itr != result[result_row_itr].size() - 1) {
                cout << " ";
            }
        }

        if (result_row_itr != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    // fout.close();

    return 0;
}
