#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i] < arr[i-1]) return false;
    return true;
}

void bozoSort(std::vector<int>& arr) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<size_t> dist(0, arr.size() - 1);
    
    while (!isSorted(arr)) {
        size_t i = dist(g);
        size_t j = dist(g);
        std::swap(arr[i], arr[j]);
    }
}

int main() {
    std::vector<int> arr = {5, 1, 4, 2, 8};
    bozoSort(arr);
    
    std::cout << "Результат Bozo Sort: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
