#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdlib>

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
    srand(time(NULL));

    vector<bool> sieve(501, true);
    sieve[0] = sieve[1] = false;
    for (int p_s = 2; p_s * p_s <= 500; p_s++) {
        if (sieve[p_s]) {
            for (int i = p_s * p_s; i <= 500; i += p_s) sieve[i] = false;
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
    for (int i = q_min; i <= q_max && i <= 500; i++) {
        if (sieve[i]) {
            q = i;
            cout << "Выбрано q = " << q << ". Использовать? (+/-): ";
            cin >> marker;
            if (marker == "+") break;
        }
    }

    if (q == 0) return 1;

    vector<long long> table_p;

    while (table_p.size() < 10) {
        double xi = (double)rand() / RAND_MAX;
        if (xi == 0) xi = 0.1;

        long long N = floor(pow(2, bits - 1) / q) + floor((pow(2, bits - 1) * xi) / q);

        if (N % 2 != 0) N++;

        unsigned int u = 0;

        while (true) {
            long long p_candidate = (N + u) * q + 1;

            if (p_candidate >= pow(2, bits)) break;

            long long check1 = mod_pow(2, p_candidate - 1, p_candidate);
            long long check2 = mod_pow(2, N + u, p_candidate);

            if (check1 == 1 && check2 != 1) {
                table_p.push_back(p_candidate);
                break;
            }

            u += 2;
        }
    }

    string border = "------------------------------------------------------------------------------------";
    int w1 = 20, w2 = 10; 

    cout << border << endl;
    cout << "| " << left << setw(w1) << "№" << "|";
    for (int i = 0; i < 10; i++) cout << setw(w2) << i + 1 << "|";
    cout << endl << border << endl;

    cout << "| " << left << setw(w1) << "Простое число p" << "|";
    for (int i = 0; i < 10; i++) cout << setw(w2) << table_p[i] << "|";
    cout << endl << border << endl;

    return 0;
}

