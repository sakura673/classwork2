#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    // Если разная длина - точно не перестановка
    if (s1.length() != s2.length()) {
        cout << "NO" << endl;
        return 0;
    }

    vector<int> count(26, 0);  // счётчик для 26 букв

    // Увеличиваем счётчик для букв из первой строки
    for (char c : s1) {
        count[c - 'a']++;
    }

    // Уменьшаем счётчик для букв из второй строки
    for (char c : s2) {
        count[c - 'a']--;
    }

    // Проверяем, все ли счётчики нулевые
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            cout << "NO" << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
    return 0;
}