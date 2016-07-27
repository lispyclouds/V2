package main

import "fmt"
import (
	"./V2"
	"./lib"
)

func genMatrix() [256][256]uint8 {
	mat := [256][256]uint8{}
	var i, j uint16

	for i = 0; i <= 255; i++ {
		for j = 0; j <= 255; j++ {
			mat[j][i] = uint8(j)
		}
	}

	return mat
}

func main() {
	data := genMatrix()
	for columnCounter := 0; columnCounter < len(data); columnCounter++ {
		column := [256] uint8{}
		for rowCounter := 0; rowCounter < 256; rowCounter++ {
			column[rowCounter] = data[rowCounter][columnCounter]
		}
		data[columnCounter] = lib.Shuffle(column)
	}
	V2.Encrypt(data)

	fmt.Println(data)
}



