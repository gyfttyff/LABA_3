#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double xStart, xEnd, dx;
    
  
    cout << "Введите xStart, xEnd, dx: ";
    cin >> xStart >> xEnd >> dx;
    cout << endl << endl;


    cout << "-----------------------" << endl;
    cout << setw(8) << "X" << " | " << setw(8) << "Y" << endl;
    cout << "-----------------------" << endl;


    for (double x = xStart; x <= xEnd + dx/2; x += dx) 
    {
        double y;

        if (x >= -7 && x <= -6) {
            // Участок 1: Прямая
            y = -2 * x - 14;
        } 
        else if (x > -6 && x <= -2) {
            // Участок 2: Окружность (центр -4, -2; выгнута вверх)
            y = -2 + sqrt(4 - pow(x + 4, 2));
        } 
        else if (x > -2 && x <= 2) {
            // Участок 3: Логарифм
            y = log2(2 + x);
        } 
        else if (x > 2 && x <= 4) {
            // Участок 4: Окружность (центр 3, 0; выгнута вверх)
            y = sqrt(1 - pow(x - 3, 2));
        } 
  
        if (x < -7 || x > 4) {
            cout << setw(8) << setprecision(2) << x << " | " << "Вне графика" << endl;
            continue; 
        }
        else {
            cout << setw(8) << fixed << setprecision(2) << x << " | " 
                 << setw(8) << y << endl;
        }
      
    }

    return 0;
}

