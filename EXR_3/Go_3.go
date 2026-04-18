package main

import (
	"fmt"
	"math/big"
)

func gcd(a, b *big.Int) *big.Int {
	return new(big.Int).GCD(nil, nil, a, b)
}

func main() {
	var a, b int64
	_, err := fmt.Scan(&a, &b)
	if err != nil {
		return
	}

	if b == 1 {
		fmt.Println("infinity")
		return
	}

	// Вычисляем таблицу чисел Эйлера A(n, k)
	euler := make([][]*big.Int, a+1)
	for i := range euler {
		euler[i] = make([]*big.Int, i+1)
		for j := range euler[i] {
			euler[i][j] = big.NewInt(0)
		}
	}

	euler[0][0] = big.NewInt(1)
	for n := 1; n <= int(a); n++ {
		for k := 0; k < n; k++ {
			// A(n, k) = (n-k)A(n-1, k-1) + (k+1)A(n-1, k)
			term1 := big.NewInt(0)
			if k > 0 {
				term1.Mul(big.NewInt(int64(n-k)), euler[n-1][k-1])
			}
			term2 := big.NewInt(0).Mul(big.NewInt(int64(k+1)), euler[n-1][k])
			euler[n][k].Add(term1, term2)
		}
	}

	// Числитель: sum_{k=0}^{a-1} A(a, k) * b^(a-k)
	num := big.NewInt(0)
	for k := 0; k < int(a); k++ {
		powerB := new(big.Int).Exp(big.NewInt(b), big.NewInt(a-int64(k)), nil)
		term := new(big.Int).Mul(euler[int(a)][k], powerB)
		num.Add(num, term)
	}

	// Знаменатель: (b-1)^(a+1)
	den := new(big.Int).Exp(big.NewInt(b-1), big.NewInt(a+1), nil)

	// Сокращаем дробь
	common := gcd(num, den)
	num.Div(num, common)
	den.Div(den, common)

	fmt.Printf("%s/%s\n", num.String(), den.String())
}
