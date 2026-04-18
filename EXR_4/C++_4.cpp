#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long pavel = 0;
    long long vika = 0;
    int current = 0;
    int lastP = -1;
    int lastV = -1;
    bool Pavel_Play = true;

    while (current < n) {
        long long max_score = - pow(10, 10); 
        int chose_kam = -1;

        // ВАРИАНТ 2: Запрет зависит от хода ОППОНЕНТА
        // Если ходит Павел - нельзя брать как Вика (lastV), и наоборот
        int forbidden = (Pavel_Play ? lastV : lastP);

        long long current_sum = 0;
        for (int k = 1; k <= m; k++) {
            if (current + k > n) break;

            current_sum += a[current + k - 1];

            if (k == forbidden) continue;

            if (current_sum > max_score) {
                max_score = current_sum;
                chose_kam = k;
            }
        }

        // Если все ходы были forbidden, берем первый доступный ход
        if (chose_kam == -1) {
            for (int k = 1; k <= m && current + k <= n; k++) {
                if (k != forbidden) {
                    chose_kam = k;
                    max_score = 0;
                    for (int j = 0; j < k; j++) max_score += a[current + j];
                    break;
                }
            }
        }

        if (chose_kam == -1) break;

        if (Pavel_Play) {
            pavel += max_score;
            lastP = chose_kam; // Сохраняем ход Павла для следующего хода Вики
        } else {
            vika += max_score;
            lastV = chose_kam; // Сохраняем ход Вики для следующего хода Павла
        }

        current += chose_kam;
        Pavel_Play = !Pavel_Play;
    }

    if (pavel > vika) cout << 1 << endl;
    else cout << 0 << endl;

    return 0;
}

