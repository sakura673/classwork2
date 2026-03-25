#include <iostream>
using namespace std;

const long long MOD = 1000000007;

long long binpow(long long a, long long b) {
    long long result = 1;
    a %= MOD;  // приводим a к диапазону MOD

    while (b > 0) {
        // Если текущий бит степени равен 1, умножаем результат на a
        if (b & 1) {
            result = (result * a) % MOD;
        }
        // Возводим a в квадрат для следующего бита
        a = (a * a) % MOD;
        // Сдвигаем степень вправо (переходим к следующему биту)
        b >>= 1;
    }

    return result;
}

int main() {
    long long a, b;
    cin >> a >> b;

    cout << binpow(a, b) << endl;

    return 0;
}