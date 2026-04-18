#include <iostream>
#include <vector>
#include <numeric> // Для std::gcd Наибольшего общего делителя
#include <cmath>   // Для std::pow Степени числа

using namespace std;

typedef long long ll;

int main() {
    ll a, b;
    cout << endl;
    cout << "Введите a и b: ";
    cin >> a >> b;
    cout << endl;

    // Проверка на расходимость
    if (b == 1) { //  Ряд сходится только тогда, когда основание знаменателя |b| > 1. Если b = 1, то каждое слагаемое это бесконечная сумма
        cout << "infinity" << endl;
        return 0;
    }

    // числа Эйлера A(a, k)
    vector<vector<ll>> euler(a + 1, vector<ll>(a + 1, 0));
    euler[0][0] = 1;

    for (int n = 1; n <= a; ++n) {
        for (int k = 0; k < n; ++k) {
            ll term1 = (k > 0) ? (n - k) * euler[n - 1][k - 1] : 0;
            ll term2 = (k + 1) * euler[n - 1][k];
            euler[n][k] = term1 + term2;
        }
    }

    // Считаем числитель 
    ll num = 0;
    for (int k = 0; k < a; ++k) {
        // Нам нужно привести результат pow к long long
        num += euler[a][k] * (ll)pow(b, a - k);
    }
    // Это знаменатель			
    ll den = (ll)pow(b - 1, a + 1);

    // 4. Сокращаем дробь, используя встроенный std::gcd из <numeric>
    ll common = gcd(num, den); 
    
    cout << num / common << "/" << den / common << endl; 
    cout << endl;

    return 0;
}

