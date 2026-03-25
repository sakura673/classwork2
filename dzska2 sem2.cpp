#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_set<int> unique_ids;

    for (int i = 0; i < n; i++) {
        int id;
        cin >> id;
        unique_ids.insert(id); // добавляем число в списочек
    }

    cout << unique_ids.size();  // количество уникальных

    return 0;
}