#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i)
        if (arr[i] < arr[i-1]) return false;
    return true;
}

void bogosort(std::vector<int>& arr) {
    std::random_device rd;
    std::mt19937 g(rd());
    
    while (!isSorted(arr)) {
        std::shuffle(arr.begin(), arr.end(), g);
    }
}

int main() {
    std::vector<int> arr = {3, 2, 5, 1, 4};
    bogosort(arr);
    
    std::cout << "Отсортировано: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
