#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

long long mod_pow(long long base, long long exp, long long m) {
    if (m == 1) return 0;
    long long res = 1;
    base = base % m;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % m;
        base = (__int128)base * base % m;
        exp = exp / 2;
    }
    return res;
}

int main() {
    vector<bool> sieve(501, true);
    sieve[0] = sieve[1] = false;
    for (int p = 2; p * p <= 500; p++) {
        if (sieve[p]) {
            for (int i = p * p; i <= 500; i += p) sieve[i] = false;
        }
    }

    int bits;
    cout << "Введите разрядность t: ";
    cin >> bits;


    int target_q_bits = (bits + 1) / 2; 
    
    long long q_min = pow(2, target_q_bits - 1);
    long long q_max = pow(2, target_q_bits) - 1;
    
    unsigned int q = 0;
    string marker;

    // Идем по решету, чтобы найти q из таблицы
    for (int i = q_min; i <= q_max && i <= 500; i++) {
        if (sieve[i]) {
            q = i;
            cout << "Выбрано q = " << q <<  " Использовать это q? (+/-): ";
            cin >> marker;
            if (marker == "+") break; 
        }
    }

    if (q == 0) {
        cout << "Подходящее q не найдено!" << endl;
        return 1;
    }

    unsigned int u = 0;
    long long p = 0;
    long long p_test = 1;

    while (p == 0) {
        long long pow2 = pow(2, bits - 1); 
        long long N = pow2 / q;
        if (N % 2 != 0) N++;

        p_test = (N + u) * q + 1;
        
        long long check1 = mod_pow(2, p_test - 1, p_test); 
        long long check2 = mod_pow(2, N + u, p_test); 

        // Проверка попадания p в нужную разрядность t
        if (p_test >= pow(2, bits - 1) && p_test < pow(2, bits)) {
            if (check1 == 1 && check2 != 1) {
                p = p_test;
                break;
            }
        }

        u += 2; 
        if (p_test > pow(2, bits)) {
            cout << "В этом диапазоне p не найдено. Попробуйте другое q." << endl;
            break;
        }
    }

    string border = "------------------------------------------------------------------------------------";
    int w1 = 20, w2 = 8; 

    if (p != 0) {
        cout << border << endl;
        cout << "| " << left << setw(w1) << "№" << "|";
        for (int i = 0; i < 10; i++) cout << setw(w2) << i + 1 << "|";
        cout << endl << border << endl;

        cout << "| " << left << setw(w1) << "Простое число p" << "|";
        for (int i = 0; i < 10; i++) cout << setw(w2) << p << "|";
        cout << endl << border << endl;
    }

    return 0;
}

