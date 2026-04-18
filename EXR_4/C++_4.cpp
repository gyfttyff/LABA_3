#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, variant;
    // Укажите вариант (1 или 2) здесь или считайте из ввода
    variant = 1; 

    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    long long pavel = 0, vika = 0;
    int current = 0;
    int lastP = -1, lastV = -1;
    bool isPavel = true;

    while (current < n) {
        long long max_s = -2e18; // Минимально возможное значение
        int chosen_k = -1;

        // Определяем запрещенное количество по варианту
        int forbidden = -1;
        if (variant == 1) forbidden = (isPavel ? lastP : lastV);
        else forbidden = (isPavel ? lastV : lastP);

        long long running_sum = 0;
        for (int k = 1; k <= m && current + k <= n; k++) {
            running_sum += a[current + k - 1];
            
            if (k == forbidden) continue;

            if (running_sum > max_s) {
                max_s = running_sum;
                chosen_k = k;
            }
        }

        // Если все ходы запрещены или невозможны, берем минимально допустимый ход
        if (chosen_k == -1) {
            for (int k = 1; k <= m && current + k <= n; k++) {
                if (k != forbidden) {
                    chosen_k = k;
                    max_s = 0;
                    for(int j=0; j<k; j++) max_s += a[current+j];
                    break;
                }
            }
        }

        if (isPavel) {
            pavel += max_s;
            lastP = chosen_k;
        } else {
            vika += max_s;
            lastV = chosen_k;
        }

        current += chosen_k;
        isPavel = !isPavel;
    }

    cout << (pavel > vika ? 1 : 0) << endl;
    return 0;
}
