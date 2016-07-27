package V2

import "../lib"

func Encrypt(data [256][256] uint8) [256][256]uint8 {
	for row := 0; row < 256; row++ {
		for column := 0; column < 256; column++ {
			data[row][column] = lib.SBoxOf(data[row][column])
		}
	}
	return data
}