#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Функция быстрого возведения в степень по модулю
long long mod_pow(long long base, long long exp, long long m) { // Основание, степень, 
    long long res = 1;
    base = base % m;
    while (exp > 0) {
        // Используем __int128, чтобы не было переполнения при умножении
        if (exp % 2 == 1) res = (__int128)res * base % m;
        base = (__int128)base * base % m;
        exp = exp / 2;
    }
    return res;
}

int main() {

    //ЭТАП 1: РЕШЕТО ЭРАТОСФЕНА
    vector<bool> sieve(501, true);
    sieve[0] = sieve[1] = false;
    for (int p = 2; p * p <= 500; p++) {
        if (sieve[p]) {
            for (int i = p * p; i <= 500; i += p) sieve[i] = false;
        }
    }

    //ЭТАП 2: ВВОД ДАННЫХ
    int bits;
    cout << "Введите разрядность t: ";
    cin >> bits;

    // Параметры для ГОСТа
    long long q = 11;  // Простое число из решета
    long long u = 0;   // Смещение u

    // Векторы для хранения 10 результатов таблицы
    vector<long long> table_p;
    vector<string> table_res;

    //ЭТАП 3-5: ГЕНЕРАЦИЯ И ПРОВЕРКА 
    for (int i = 0; i < 10; i++) { // Количество кандидатов 10
        // 1. Считаем 2^(bits-1)
        long long pow2 = 1;
        for (int k = 0; k < bits - 1; k++) pow2 *= 2;

        // 2. Расчет N по ГОСТ (Шаг 2)
        long long N = pow2 / q; // При сигме 0
        if (N % 2 != 0) N++; // N должно быть четным

        // 3. Расчет кандидата p = (N + u) * q + 1
        long long p = (N + u) * q + 1;

        // 4. Проверка тестом Диемитко (Шаг 6 по ГОСТ, без параметра t)
        long long check1 = mod_pow(2, p - 1, p); // Условие 1
        long long check2 = mod_pow(2, N + u, p); // Условие 2

        // Сохраняем данные
        table_p.push_back(p);
        
  

        // Если оба условия выполнены — число простое
        if (check1 == 1 && check2 != 1) {
            table_res.push_back("tr");
        } else {
            table_res.push_back("fl");
        }

        // Переходим к следующему числу
        u += 2;
    }

    // --- ВЫВОД ТАБЛИЦЫ (РОВНО ПО СКРИНШОТУ) ---
    cout << "\n\t\tРезультаты выполнения тестов (Таблица 2)\n";
    string border = "-----------------------------------------------------------------------------";
    
    int w1 = 25; // Ширина первой колонки
    int w2 = 4;  // Ширина колонок с данными

    cout << border << endl;
    cout << "| " << left << setw(w1) << "№" << "|";
    for (int i = 1; i <= 10; i++) cout << setw(w2) << i << "|";
    cout << endl << border << endl;

    cout << "| " << left << setw(w1) << "Простое число" << "|";
    for (int i = 0; i < 10; i++) cout << setw(w2) << table_p[i] << "|";
    cout << endl << border << endl;

    cout << "| " << left << setw(w1) << "Результат проверки" << "|";
    for (int i = 0; i < 10; i++) cout << setw(w2) << table_res[i] << "|";
    cout << endl << border << endl;


    return 0;
}

