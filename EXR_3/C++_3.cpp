#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

typedef long long ll;

// Функция для нахождения НОД (наибольшего общего делителя)
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Возведение в степень
ll power(ll base, ll exp) {
    ll res = 1;
    for (int i = 0; i < exp; i++) res *= base;
    return res;
}

int main() {
    ll a, b;
    if (!(cin >> a >> b)) return 0;

    // Если b = 1, ряд расходится
    if (b == 1) {
        cout << "infinity" << endl;
        return 0;
    }

    // Вычисляем числа Эйлера A(n, k) через динамическое программирование
    // A(n, k) = (n-k)*A(n-1, k-1) + (k+1)*A(n-1, k)
    vector<vector<ll>> euler(a + 1, vector<ll>(a, 0));
    euler[0][0] = 1;

    for (int n = 1; n <= a; ++n) {
        for (int k = 0; k < n; ++k) {
            ll term1 = (k > 0) ? (n - k) * euler[n - 1][k - 1] : 0;
            ll term2 = (k + 1) * euler[n - 1][k];
            euler[n][k] = term1 + term2;
        }
    }

    // Числитель: sum_{k=0}^{a-1} ( A(a, k) * b^(a-k) )
    ll num = 0;
    for (int k = 0; k < a; ++k) {
        num += euler[a][k] * power(b, a - k);
    }

    // Знаменатель: (b-1)^(a+1)
    ll den = power(b - 1, a + 1);

    // Сокращаем дробь
    ll common = gcd(num, den);
    cout << num / common << "/" << den / common << endl;

    return 0;
}
