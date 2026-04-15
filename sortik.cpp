#include <iostream>
#include <vector>

std::vector<int> stalinSort(const std::vector<int>& arr) {
    if (arr.empty()) return {};
    
    std::vector<int> result;
    result.push_back(arr[0]);
    int maxSoFar = arr[0];
    
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] >= maxSoFar) {
            result.push_back(arr[i]);
            maxSoFar = arr[i];
        }
    }
    return result;
}

int main() {
    std::vector<int> arr = {5, 1, 3, 6, 2, 7, 8, 4};
    std::vector<int> sorted = stalinSort(arr);
    
    std::cout << "Результат сортировки Сталина: ";
    for (int x : sorted) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
