#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;


void traverseTree(vector<int>& heap, int i, vector<int>& result) {
    if (i >= heap.size() || heap[i] == -1) return;

    traverseTree(heap, 2 * i + 1, result);// Left
    result.push_back(heap[i]);// In order
    traverseTree(heap, 2 * i + 2, result);// Left
}

void print_indexes(vector<vector<int>>& indexes)
{
    for_each(indexes.begin(), indexes.end(), [&](auto node) {
            for(auto n : node){
                cout << n << " ";
            }
            cout << endl;
        });
}

vector<int> traverseSwap(vector<vector<int>> &indexes, int k)
{
    // Problem: only swap the nodes instead of subtrees.
    vector<int> heap(2048, -1);
    heap[0] = 1;
    int heap_index = 0;
    vector<int> result;

    int level = 0;
    queue<int> parents;
    parents.push(1);
    int n = 1;

    for (int i = 0; i < indexes.size() && !parents.empty();)
    {
        level++;
        vector<int> children;
        while (!parents.empty()) {
            if (n * k == level) {// Swap
                swap(indexes[i][0], indexes[i][1]);
            }

            if (indexes[i][0] != -1) {
                children.push_back(indexes[i][0]);
            }
            if (indexes[i][1] != -1) {
                children.push_back(indexes[i][1]);
            }

            int p = parents.front();
            parents.pop();
            // Construct a complete tree
            while (heap[heap_index] != p) {
                heap_index++;
            }
            heap[2 * heap_index + 1] = indexes[i][0]; // Left leafe
            heap[2 * heap_index + 2] = indexes[i][1]; // Right leafe
            
            i++;
        }

        if (n * k == level) {
            n++;
        }

        // Children become parents.
        for_each(children.begin(), children.end(), [&](auto c) {parents.push(c); });
    }

    traverseTree(heap, 0, result);

    return result;
}

/*
 * Complete the swapNodes function below.
 */
vector<vector<int>> swapNodes(vector<vector<int>> &indexes, vector<int> queries) {
    vector<vector<int>> result;
    for (auto k : queries) {
        auto res = traverseSwap(indexes, k);
        print_indexes(indexes);
        result.push_back(res);
    }

    return result;
}

int main1()
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
