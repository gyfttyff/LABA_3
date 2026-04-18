package main

import (
	"fmt"
)

func main() {
	var n, m int
	variant := 1 // Измените на 2 для соответствующего варианта
	fmt.Scan(&n, &m)

	a := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	var pavel, vika int64
	current := 0
	lastP, lastV := -1, -1
	isPavel := true

	for current < n {
		maxS := int64(-2e18)
		chosenK := -1

		var forbidden int
		if variant == 1 {
			if isPavel {
				forbidden = lastP
			} else {
				forbidden = lastV
			}
		} else {
			if isPavel {
				forbidden = lastV
			} else {
				forbidden = lastP
			}
		}

		var runningSum int64
		for k := 1; k <= m && current+k <= n; k++ {
			runningSum += a[current+k-1]
			if k == forbidden {
				continue
			}
			if runningSum > maxS {
				maxS = runningSum
				chosenK = k
			}
		}

		if chosenK == -1 {
			for k := 1; k <= m && current+k <= n; k++ {
				if k != forbidden {
					chosenK = k
					maxS = 0
					for j := 0; j < k; j++ {
						maxS += a[current+j]
					}
					break
				}
			}
		}

		if isPavel {
			pavel += maxS
			lastP = chosenK
		} else {
			vika += maxS
			lastV = chosenK
		}
		current += chosenK
		isPavel = !isPavel
	}

	if pavel > vika {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}
