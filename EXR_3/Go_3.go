package main

import (
	"fmt"
	"math"
)

// Функция для нахождения НОД (аналог std::gcd)
func gcd(a, b int64) int64 {
	for b != 0 {
		a %= b
		a, b = b, a
	}
	return a
}

func main() {
	var a, b int64
	fmt.Print("Введите a и b: ")
	fmt.Scan(&a, &b)
	fmt.Println()

	// 1. Проверка на расходимость
	if b == 1 {
		fmt.Println("infinity")
		return
	}

	// 2. Числа Эйлера A(a, k)
	// Создаем двумерный срез (аналог vector<vector<ll>>)
	euler := make([][]int64, a+1)
	for i := range euler {
		euler[i] = make([]int64, a+1)
	}
	euler[0][0] = 1

	for n := 1; n <= int(a); n++ {
		for k := 0; k < n; k++ {
			var term1 int64 = 0
			if k > 0 {
				term1 = int64(n-k) * euler[n-1][k-1]
			}
			term2 := int64(k+1) * euler[n-1][k]
			euler[n][k] = term1 + term2
		}
	}

	// 3. Считаем числитель
	var num int64 = 0
	for k := 0; k < int(a); k++ {
		// math.Pow работает с float64, поэтому приводим типы (аналог (ll)pow)
		power_b := int64(math.Pow(float64(b), float64(a-int64(k))))
		num += euler[a][k] * power_b
	}

	// 4. Считаем знаменатель
	den := int64(math.Pow(float64(b-1), float64(a+1)))

	// 5. Сокращаем дробь через НОД
	common := gcd(num, den)

	fmt.Printf("%d/%d\n", num/common, den/common)
	fmt.Println()
}

