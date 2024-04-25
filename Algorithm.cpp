#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Item {
    int weight;
    int value;
};

bool compareItems(Item a, Item b) {
    return (a.value * 1.0 / a.weight) > (b.value * 1.0 / b.weight);
}

double backracking(int capacity, vector<Item>& items, int index, double current_value, int current_weight) {
    if (current_weight > capacity) {
        return 0;
    }

    if (index >= items.size()) {
        return current_value;
    }

    double max_value = current_value;

    for (int i = index; i < items.size(); i++) {
        if (current_weight + items[i].weight <= capacity) {
            max_value = max(max_value, backracking(capacity, items, i + 1, current_value + items[i].value, current_weight + items[i].weight));
        }
    }

    return max_value;
}

double Greedy(int capacity, vector<Item>& items) {
    double max_value = 0.0;
    int current_weight = 0;

    vector<Item> CopyItems = items;

    sort(CopyItems.begin(), CopyItems.end(), compareItems);

    for (const auto& item : CopyItems) {
        if (current_weight + item.weight <= capacity) {
            max_value += item.value;
            current_weight += item.weight;
        }
    }

    return max_value;
}

int Dymamic(int capacity, vector<Item> items) {
    int n = items.size();

    vector<Item> CopyItems = items;

    sort(CopyItems.begin(), CopyItems.end(), compareItems);

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (CopyItems[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - CopyItems[i - 1].weight] + CopyItems[i - 1].value);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][capacity];
}

int main() {
    int capacity = 10, n;
    vector<Item> items1;
    vector<Item> items2;
    vector<Item> items3;

    cout << "number of items: "; cin >> n;
    cout << endl;
    cout << "items:" << endl;
    cout << "weight\tvalue" << endl;
    Item temp;
    for (int i = 0; i < n; i++) {
        temp.weight = (temp.value = rand() % 1000 + 1) / (rand() % 33 + 1);
        capacity += temp.weight;
        items1.push_back(temp);
        items2.push_back(temp);
        items3.push_back(temp);
        cout << temp.weight << "\t" << temp.value << endl;
    }
    capacity *= 0.3;

    cout << "backpack capacity: " << capacity << endl;

    double max_value1 = backracking(capacity, items1, 0, 0, 0);
    double max_value2 = Greedy(capacity, items2);
    double max_value3 = Dymamic(capacity, items3);

    cout << "Bactracking. Maximum value that can be obtained: " << max_value1 << endl;
    cout << "Greedy Algorithm. Maximum value that can be obtained: " << max_value2 << endl;
    cout << "Dymamic Programing. Maximum value that can be obtained: " << max_value3 << endl;

    return 0;
}
