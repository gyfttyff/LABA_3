package main

import (
	"fmt"
	"math"
)

func main() {
	var xStart, xEnd, dx float64

	// 1. Ввод данных
	fmt.Print("Введите xStart, xEnd, dx: ")
	_, err := fmt.Scan(&xStart, &xEnd, &dx)
	if err != nil {
		return
	}
	fmt.Println("\n") // Два перевода строки, как в твоем коде

	// 2. Печать заголовка
	fmt.Println("-----------------------")
	fmt.Printf("%8s | %8s\n", "X", "Y")
	fmt.Println("-----------------------")

	// 3. Цикл расчета
	// Добавка dx/2 для компенсации точности float64
	for x := xStart; x <= xEnd+dx/2; x += dx {
		var y float64

		// Условия точно по твоему алгоритму
		if x >= -7 && x <= -6 {
			// Участок 1: Прямая
			y = -2*x - 14
		} else if x > -6 && x <= -2 {
			// Участок 2: Окружность (центр -4, -2)
			y = -2 + math.Sqrt(4-math.Pow(x+4, 2))
		} else if x > -2 && x <= 2 {
			// Участок 3: Логарифм
			y = math.Log2(2 + x)
		} else if x > 2 && x <= 4 {
			// Участок 4: Окружность (центр 3, 0)
			y = math.Sqrt(1 - math.Pow(x-3, 2))
		}

		// Вывод строки
		if x < -7 || x > 4 {
			// Вывод "Вне графика" с сохранением ширины колонки
			fmt.Printf("%8.2f | Вне графика\n", x)
		} else {
			// Формат %8.2f заменяет одновременно setw(8) и setprecision(2)
			fmt.Printf("%8.2f | %8.2f\n", x, y)
		}
	}
}
