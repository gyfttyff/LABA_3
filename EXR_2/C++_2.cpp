#include <iostream>
#include <vector>
#include <random>   // для генерации случайных чисел
#include <iomanip>  // для красивого вывода таблицы
#include <string>

using namespace std;

// Используем long long, чтобы работать с большими числами (до 64 бит)
typedef unsigned long long uint64;

// --- ФУНКЦИЯ ДЛЯ ВОЗВЕДЕНИЯ В СТЕПЕНЬ ПО МОДУЛЮ ---
// Нужно для теста на простоту, чтобы не было переполнения
uint64 mod_pow(uint64 base, uint64 exp, uint64 m) {
    uint64 res = 1;
    base %= m;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % m; // __int128 защищает от ошибок при умножении
        base = (__int128)base * base % m;
        exp /= 2;
    }
    return res;
}

// --- ШАГ 5 и 6: ТЕСТ МИЛЛЕРА-РАБИНА ---
// Проверяет, является ли число n простым. t — количество проверок (надежность)
bool is_prime(uint64 n, int t) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    // Параметры теста Миллера-Рабина
    uint64 d = n - 1;
    while (d % 2 == 0) d /= 2;

    for (int i = 0; i < t; i++) {
        uint64 a = 2 + rand() % (n - 3); // Выбираем случайное основание
        uint64 x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        
        bool composite = true;
        // Дополнительные проверки (Шаг 6 по заданию)
        for (uint64 r = d; r < n - 1; r *= 2) {
            x = (__int128)x * x % n;
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");

    // --- ШАГ 1: РЕШЕТО ЭРАТОСФЕНА (упрощенно) ---
    vector<int> small_primes;
    for (int i = 2; i <= 500; i++) {
        bool simple = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) { simple = false; break; }
        }
        if (simple) small_primes.push_back(i);
    }

    // ВХОДНЫЕ ДАННЫЕ
    int bits;
    cout << "Введите разрядность (например, 10 или 16): ";
    cin >> bits;

    // Настройка генератора случайных чисел
    random_device rd;
    mt19937_64 gen(rd());
    uint64 min_val = 1ULL << (bits - 1); // Минимальное число заданной разрядности
    uint64 max_val = (1ULL << bits) - 1; // Максимальное число заданной разрядности
    uniform_int_distribution<uint64> dist(min_val, max_val);

    // Структура для хранения данных одного столбца таблицы
    struct Result { 
        uint64 number; 
        string status; 
        int rejected; 
    };
    vector<Result> table;

    // --- ШАГ 3: ЦИКЛ ДЛЯ ПОСТРОЕНИЯ 10 ЧИСЕЛ ---
    for (int i = 1; i <= 10; i++) {
        int rejected = 0;
        uint64 candidate;

        while (true) {
            candidate = dist(gen); // Генерируем случайное число

            // Проверка делимости на малые простые числа из Шага 1
            bool div_by_small = false;
            for (int p : small_primes) {
                if (candidate % p == 0 && candidate != p) {
                    div_by_small = true;
                    break;
                }
            }

            if (div_by_small) {
                rejected++; // Увеличиваем счетчик rejected (Шаг 5.а)
                continue;
            }

            // ШАГ 5: Проверка основным тестом
            if (is_prime(candidate, 1)) {
                // ШАГ 6: Дополнительная проверка с параметром t=2
                bool final_check = is_prime(candidate, 2);
                table.push_back({candidate, final_check ? "true" : "false", rejected});
                break;
            } else {
                rejected++; // Не прошло тест — в мусор
            }
        }
    }

    // --- ВЫВОД РЕЗУЛЬТАТОВ (ТАБЛИЦА 2) ---
    cout << "\nРезультаты выполнения тестов (Таблица 2)\n";
    string border = "-----------------------------------------------------------------------------------------";
    
    cout << border << endl;
    cout << "| " << left << setw(18) << "№" << " |";
    for (int i = 1; i <= 10; i++) cout << setw(5) << i << " |";
    cout << "\n" << border << endl;

    cout << "| " << left << setw(18) << "Простое число" << " |";
    for (auto item : table) cout << setw(5) << item.number << " |";
    cout << "\n" << border << endl;

    cout << "| " << left << setw(18) << "Результат" << " |";
    for (auto item : table) cout << setw(5) << (item.status == "true" ? "tr" : "fl") << " |";
    cout << "\n" << border << endl;

    cout << "| " << left << setw(18) << "rejected" << " |";
    for (auto item : table) cout << setw(5) << item.rejected << " |";
    cout << "\n" << border << endl;

    return 0;
}
