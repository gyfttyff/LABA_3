#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>
#include <string>

using namespace std;

// Используем стандартный 64-битный тип
typedef unsigned long long uint64;

// 1. Решето Эратосфена до 500
vector<int> sieve_500() {
    vector<int> primes;
    vector<bool> is_prime(501, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= 500; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= 500; i += p)
                is_prime[i] = false;
        }
    }
    for (int p = 2; p <= 500; p++) {
        if (is_prime[p]) primes.push_back(p);
    }
    return primes;
}

// Безопасное умножение по модулю (чтобы не было переполнения)
uint64 safe_mul(uint64 a, uint64 b, uint64 m) {
    uint64 res = 0;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % m;
        a = (a * 2) % m;
        b /= 2;
    }
    return res;
}

// Быстрое возведение в степень по модулю
uint64 mod_pow(uint64 base, uint64 exp, uint64 mod) {
    uint64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = safe_mul(res, base, mod);
        base = safe_mul(base, base, mod);
        exp /= 2;
    }
    return res;
}

// Шаг 6: Проверка теоремы Диемитко
bool check_gost(uint64 p, uint64 q, uint64 N, uint64 u) {
    if (p <= 1) return false;
    // 1) 2^(p-1) == 1 (mod p)
    if (mod_pow(2, p - 1, p) != 1) return false;
    // 2) 2^(N+u) != 1 (mod p)
    if (mod_pow(2, N + u, p) == 1) return false;
    return true;
}

// 2. Генерация простого числа
uint64 generate_gost_prime(int bits, uint64 q, int& rejected) {
    random_device rd;
    mt19937_64 gen(rd());
    
    // Граница 2^(bits-1)
    uint64 min_val = 1ULL << (bits - 1);
    uint64 max_val = (bits == 64) ? 0xFFFFFFFFFFFFFFFFULL : (1ULL << bits) - 1;

    while (true) {
        // Вычисляем стартовое N
        uint64 N_start = min_val / q;
        uniform_int_distribution<uint64> dist(0, N_start);
        uint64 N = N_start + dist(gen);
        
        if (N % 2 != 0) N++; // N должно быть четным

        uint64 u = 0;
        // Ограничиваем цикл, чтобы не уйти в бесконечность
        for (int attempt = 0; attempt < 1000; attempt++) {
            uint64 p = (N + u) * q + 1;
            
            // Если вышли за разрядность
            if (p > max_val || p < min_val) break;

            if (check_gost(p, q, N, u)) return p;

            rejected++;
            u += 2;
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    int bits;
    cout << "Введите разрядность (рекомендуется 32-60): ";
    cin >> bits;

    if (bits > 62) {
        cout << "Ошибка: стандартный uint64 не потянет больше 62 бит для этого алгоритма." << endl;
        return 1;
    }

    vector<int> small_primes = sieve_500();
    // q должно быть примерно в два раза меньше p по разрядности (из текста ГОСТ)
    uint64 q = 1000003; 

    cout << "\nРезультаты выполнения тестов (ГОСТ Р 34.10-94):\n";
    cout << "----------------------------------------------------------------------\n";
    cout << " №  | Простое число           | Результат теста | rejected\n";
    cout << "----------------------------------------------------------------------\n";

    for (int i = 1; i <= 10; i++) {
        int rejected = 0;
        uint64 p = generate_gost_prime(bits, q, rejected);
        
        // Повторная проверка для колонки "Результат"
        bool is_p = check_gost(p, q, (p - 1) / q, 0);

        cout << left << setw(3) << i << " | " 
             << left << setw(23) << p << " | " 
             << left << setw(14) << (is_p ? "true" : "false") << " | " 
             << rejected << endl;
    }

    return 0;
}
