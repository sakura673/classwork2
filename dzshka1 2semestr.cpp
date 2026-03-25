#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// Задача 1
int search(const int* nums, int size, int target) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

// Задача 2
int singleNumber(const int* nums, int size) {
    int result = 0;
    for (int i = 0; i < size; ++i) {
        result ^= nums[i];
    }
    return result;
}

// Задача 3
void findTwoUnique(const int* nums, int size, int* first, int* second) {
    // 1. XOR всех чисел дает first ^ second
    int xorAll = 0;
    for (int i = 0; i < size; ++i) {
        xorAll ^= nums[i];
    }

    // 2. Находим любой  бит, в котором отличаются наши 2 числа
    int diffBit = xorAll & (-xorAll); 

    // 3. Разделяем числа на две группы по этому биту(в каждой из групп 10000% наше число)
    int x = 0, y = 0;
    for (int i = 0; i < size; ++i) {
        if (nums[i] & diffBit) {
            x ^= nums[i];
        }
        else {
            y ^= nums[i];
        }
    }
    *first = x;
    *second = y;
}

int main() {
    setlocale(LC_ALL, "RUS");
    // Пример 1
    int arr1[] = { -1, 0, 3, 5, 9, 12 };
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int target = 9;
    int wwwwwww = search(arr1, size1, target);
    printf("Индекс %d: %d\n", target, wwwwwww);

    // Пример 2
    int arr2[] = { 4, 1, 2, 1, 2 };
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int unique = singleNumber(arr2, size2);
    printf("Уникальный элемент: %d\n", unique);

    // Пример 3
    int arr3[] = { 1, 2, 1, 3, 2, 5 };
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int a, b;
    findTwoUnique(arr3, size3, &a, &b);
    printf("Два уникальных ЭлЕмЕнТа: %d и %d\n", a, b);

    return 0;
}