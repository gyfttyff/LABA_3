package main

import "fmt"

func main() {
    var n, m int
    fmt.Scan(&n, &m)

    // Читаем веса камней (аналог vector)
    a := make([]int64, n)
    for i := 0; i < n; i++ {
        fmt.Scan(&a[i])
    }

    var pavel, vika int64
    current := 0
    lastP, lastV := -1, -1
    isPavelTurn := true

    for current < n {
        var maxScore int64 = -999999999999999999
        chosenK := -1

        // ВАРИАНТ 2: Запрет на ход оппонента
        forbidden := lastP
        if isPavelTurn {
            forbidden = lastV
        }

        currentSum := int64(0)
        for k := 1; k <= m && current+k <= n; k++ {
            currentSum += a[current+k-1]
            if k == forbidden {
                continue
            }
            if currentSum > maxScore {
                maxScore = currentSum
                chosenK = k
            }
        }

        // Аварийный выбор хода
        if chosenK == -1 {
            for k := 1; k <= m && current+k <= n; k++ {
                if k != forbidden {
                    chosenK = k
                    maxScore = 0
                    for j := 0; j < k; j++ {
                        maxScore += a[current+j]
                    }
                    break
                }
            }
        }

        if chosenK == -1 { break }

        // Начисление очков и сохранение хода
        if isPavelTurn {
            pavel += maxScore
            lastP = chosenK
        } else {
            vika += maxScore
            lastV = chosenK
        }

        current += chosenK
        isPavelTurn = !isPavelTurn
    }

    if pavel > vika {
        fmt.Println(1)
    } else {
        fmt.Println(0)
    }
}

