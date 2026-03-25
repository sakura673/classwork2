#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // элемент на позиции k-1 будет тем,который оказался бы там после полной сортировки
    // который оказался бы там после полной сортировки
    nth_element(arr.begin(), arr.begin() + (k - 1), arr.end());

    cout << arr[k - 1] << endl;

    return 0;
}