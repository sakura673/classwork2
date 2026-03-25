#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> arr(n); 
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    long long max_ending_here = arr[0];  // максимальная сумма подмассива
    long long max_so_far = arr[0];        // максимальная сумма среди всех подмассивовкак

    for (int i = 1; i < n; i++) {
        // либо продолжаем текущий подмассив, либо начинаем новый с текущего элемента
        max_ending_here = max(arr[i], max_ending_here + arr[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }

    cout << max_so_far << endl;

    return 0;
}