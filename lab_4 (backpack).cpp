#include <iostream>
#include <vector>

using namespace std;

struct Thing
{
    int weight;
    int cost;
};

int n;
int W;
int Copt = 0, Sopt = 0;
int max_value = 0;

vector<Thing> vault;
vector<Thing> backpack;
int indexes[1000]{0};

bool fullSolve(int current_weight){
    if (current_weight > W) return false;
    for (int i = 0; i < vault.size(); i++)
        if (current_weight + vault[i].weight <= W)
            return false;
    return true;
}


void search(int idx, int current_weight, int current_value) {
    while (idx < vault.size())
    {
        if((current_weight < W) && (indexes[idx] == 0)){
            Thing temp = vault[idx];
            //vault.pop_back();
            //backpack.push_back(temp);
            current_weight += temp.weight;
            current_value += temp.cost;
            cout << idx << " " << temp.weight << " " << temp.cost << " " << current_weight << " " << current_value << endl;
            if (fullSolve(current_weight) && current_value < Copt){
                Sopt = current_weight; Copt = current_value;
                cout << "===" << endl;
            }
            else if (current_value < Copt) {
                indexes[idx] = 1;
                search(0, current_weight, current_value);
                indexes[idx] = 0;
                //cout << "@@@" << endl;
            }
            else if (current_value > Copt) {
                indexes[idx] = 1;
            }
            current_weight -= temp.weight;
            current_value -= temp.cost;
        }
        idx++;
        //backpack.pop_back();
    }
}

int main() {

    setlocale(LC_ALL, "ru");

    cout << "Введите количество грузов: ";
    cin >> n;

    Thing temp;
    for (int i = 0; i < n; i++) {
        temp.weight = (temp.cost = rand() % 1000) / (rand() % 33 + 1);
        W += temp.weight;
        vault.push_back(temp);
    }
    W = 0.3 * W;

    for (int i = 0; i < n; i++)
        cout << vault[i].weight << " " << vault[i].cost << endl;

    for (int i = 0; i < n; i++){
        if (Sopt + vault[i].weight <= W) {
            Sopt += vault[i].weight;
            Copt += vault[i].cost;
        }
    }
    cout << "Sopt: " << Sopt << endl;
    cout << "Copt: " << Copt << endl;

    search(0, 0, 0);

    for (int i = 0; i < n; i++)
        cout << indexes[i] << " ";
    cout << endl;

    cout << "Вместимость рюкзака: " << W << endl;
    cout << "Максимальный вес грузов, которые можно поместить в рюкзак: " << Sopt << endl;
    cout << "Максимальная стоимость грузов, которые можно поместить в рюкзак: " << Copt << endl;

    for (int i = 0; i < backpack.size(); i++)
        cout << backpack[i].weight << " " << backpack[i].cost << endl;

    return 0;
}

//int main()
//{
//    int n, WeightCapacity = 0, CurrentCost = 0;
//    cin >> n;
//
//    vector<Thing> vault;
//
//    for (int i = 0; i < n; i++) {
//        vault[i].weight = (vault[i].cost = rand() % 1000) / (rand() % 33 + 1);
//        WeightCapacity += vault[i].weight;
//
//    }
//
//    cout << WeightCapacity << endl;
//    WeightCapacity = 0.3*WeightCapacity;
//    
//    cout << WeightCapacity << endl;
//}
