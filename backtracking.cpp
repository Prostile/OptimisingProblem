#include <iostream>
#include <vector>
#include <algorithm>

struct Item {
    int weight;
    int value;
};

bool compareItems(Item a, Item b) {
    return (a.value * 1.0 / a.weight) > (b.value * 1.0 / b.weight);
}

double knapsack(int capacity, std::vector<Item>& items, int index, double current_value, int current_weight) {
    if (current_weight > capacity) {
        return 0;
    }
    
    if (index >= items.size()) {
        return current_value;
    }
    
    double max_value = current_value;
    
    for (int i = index; i < items.size(); i++) {
        if (current_weight + items[i].weight <= capacity) {
            max_value = std::max(max_value, knapsack(capacity, items, i + 1, current_value + items[i].value, current_weight + items[i].weight));
        }
    }
    
    return max_value;
}

int main() {
    int capacity = 10, n;
    std::vector<Item> items;
    
     std::cout << "введите количество элементов" << std::endl;
    std::cin >> n;
    
    Item temp;
    for (int i = 0; i < n; i++) {
        temp.weight = (temp.value = rand() % 1000) / (rand() % 33 + 1);
        capacity += temp.weight;
        items.push_back(temp);
        std::cout << temp.weight << " " << temp.value << std::endl;
    }
    capacity *= 0.3;
    
    std::cout << "вместимость рюкзака: " << capacity << std::endl;
    
    std::sort(items.begin(), items.end(), compareItems);
    
    double max_value = knapsack(capacity, items, 0, 0, 0);
    
    std::cout << "Maximum value that can be obtained: " << max_value << std::endl;
    
    return 0;
}
