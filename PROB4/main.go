// QueenChessProblem project main.go
package main

import (
	"fmt"
	"os"
	"strconv"
)

const MAX_SIZE = 63

var (
	N          int
	chessBoard [][]bool
	initialRow []bool
	counter    int
	fout       *os.File
)

func spanResultString(where int) string {
	var rtn = ""
	for i := 1; i <= N; i++ {
		if i == where {
			rtn = rtn + "X "
		} else {
			rtn = rtn + "0 "
		}
	}
	rtn = rtn + "\r\n"
	return rtn
}

func solve(row int, columnStatus, leftSlash, rightSlash []bool, result string, f *os.File) {
	if row == 1 {
		// Default: columnStatus, leftSlash, rightSlash = []; result = ""
		for i := 0; i < N; i++ {
			//GO语言最让我不爽的就是这点：slice传的是引用，需要copy一个新的，但copy之前还要make()
			newcolumnStatus := make([]bool, N, N)
			newleftSlash := make([]bool, N, N)
			newrightSlash := make([]bool, N, N)

			_ = copy(newcolumnStatus, initialRow[:])
			_ = copy(newleftSlash, initialRow[:])
			_ = copy(newrightSlash, initialRow[:])

			newcolumnStatus[i] = false
			if i > 0 {
				newleftSlash[i-1] = false
			}
			if i != N-1 {
				newrightSlash[i+1] = false
			}
			solve(2, newcolumnStatus, newleftSlash, newrightSlash, spanResultString(i+1), f)
		}
	} else if row == N+1 {
		counter += 1
		f.WriteString("情况" + strconv.Itoa(counter) + "：\r\n" + result)
		return
	} else {
		for i := 0; i < N; i++ {
			if (columnStatus[i] == true) && (leftSlash[i] == true) && (rightSlash[i] == true) {

				var nextColumnSlash = make([]bool, N, N)
				var nextLeftSlash = make([]bool, N, N)
				var nextRightSlash = make([]bool, N, N)

				_ = copy(nextColumnSlash, columnStatus)
				_ = copy(nextLeftSlash, leftSlash)
				_ = copy(nextRightSlash, rightSlash)

				nextColumnSlash[i] = false

				for j := 0; j < (N - 1); j++ {
					nextLeftSlash[j] = nextLeftSlash[j+1]
				}
				nextLeftSlash[N-1] = true
				if i > 0 {
					nextLeftSlash[i-1] = false
				}

				for j := N - 1; j > 0; j-- {
					nextRightSlash[j] = nextRightSlash[j-1]
				}
				nextRightSlash[0] = true
				if i != N-1 {
					nextRightSlash[i+1] = false
				}

				solve(row+1, nextColumnSlash, nextLeftSlash, nextRightSlash, result+spanResultString(i+1), f)
			}
		}
		return
	}
}

func main() {
	/*Initialize file io*/
	outputFileName := "output.txt"
	fout, err := os.OpenFile(outputFileName, os.O_CREATE|os.O_TRUNC|os.O_RDWR, 0660)
	defer fout.Close()
	if err != nil {
		fmt.Println(outputFileName, err)
		return
	}

	/*Initialize and input number N*/
	fmt.Println("现有N*N的棋盘，放入N个皇后，要求所有的皇后不在同一行，列和斜线上。")
	fmt.Print("请输入皇后的个数N（建议不要超过13个……否则算到明天天亮可能都算不完~）：")
	fmt.Scanf("%d", &N)

	fout.WriteString("结果如下：\r\n")

	if N == 1 {
		fout.WriteString("情况1：\r\nX\r\n")
		return
	}

	for i := 0; i < N; i++ {
		initialRow = append(initialRow, true)
	}
	for i := 0; i < N; i++ {
		chessBoard = append(chessBoard, initialRow)
	}
	counter = 0
	solve(1, make([]bool, N, N), make([]bool, N, N), make([]bool, N, N), "", fout)
	fmt.Println("结果已输出到output.txt。")
	return
}
