package V2

import (
	"../lib"
)

type point struct {
	x int
	y int
}

type EncryptedCredential struct {
	key [256][256] uint8
	startingPosition point
	moves []int
}

func shuffle(data [256][256] uint8) [256][256] uint8 {
	for columnCounter := 0; columnCounter < len(data); columnCounter++ {
		column := [256] uint8{}
		for rowCounter := 0; rowCounter < 256; rowCounter++ {
			column[rowCounter] = data[rowCounter][columnCounter]
		}
		data[columnCounter] = lib.Shuffle(column)
	}
	return data
}

func sBoxOfEachCell(data [256][256] uint8) [256][256] uint8 {
	for row := 0; row < 256; row++ {
		for column := 0; column < 256; column++ {
			data[row][column] = lib.SBoxOf(data[row][column])
		}
	}
	return data
}

func reachToAside(px int, py int) (bool) {
	if px == 255 || py == 255 || px == 0 || py == 0 {
		return true
	}
	return false
}

func getPossibleDirection(directions [] int, px int, py int) [] int {
	possibleDirection := []int{}
	if px == 0 && py == 0 {
		possibleDirection = []int{2, 3, 4}
	} else if py == 255 && px == 255 {
		possibleDirection = []int{0, 6, 7}
	} else if px == 0 && py == 255 {
		possibleDirection = []int{0, 1, 2}
	} else if px == 255 && py == 0 {
		possibleDirection = []int{4, 5, 6}
	} else if py == 0 && px != 255 {
		possibleDirection = []int{2, 3, 4, 5, 6}
	} else if py == 255 && px != 0 {
		possibleDirection = []int{0, 1, 2, 6, 7}
	} else if px == 255 && py != 0 {
		possibleDirection = []int{4, 5, 6, 7}
	} else if px == 0 && py != 255 {
		possibleDirection = []int{0, 1, 2, 3, 4}
	} else {
		possibleDirection = directions
	}
	return possibleDirection
}

func Encrypt(dataStream []byte) (EncryptedCredential, []byte) {
	key := lib.GenarateInitialKeyMatrix()
	cipherDataStream := make([]byte, 0)
	var dataLength int = len(dataStream)
	allDirections := [] int{0, 1, 2, 3, 4, 5, 6, 7}
	moves := make([]int, 0)

	initialCipherKey := shuffle(key)
	startingPX, startingPY := lib.ChooseRandomPoint(255, 0)
	cipherKey := initialCipherKey
	possibleDirection := getPossibleDirection(allDirections, startingPX, startingPY)
	startingDirection := lib.ChooseRandomDirection(possibleDirection)
	moves = append(moves, startingDirection)
	px, py, direction := startingPX, startingPY, startingDirection

	for recentIndex := 0; recentIndex < dataLength; recentIndex++ {
		cipherDataStream = append(cipherDataStream, dataStream[recentIndex] ^ cipherKey[px][py])
		if (!reachToAside(px, py)) {
			px, py = lib.MoveTowards(direction, px, py)

		} else {
			cipherKey = sBoxOfEachCell(cipherKey)
			direction = lib.ChooseRandomDirection(getPossibleDirection(allDirections, px, py))
			px, py = lib.MoveTowards(direction, px, py)
			moves = append(moves, direction)
		}

	}
	return EncryptedCredential{key:initialCipherKey,startingPosition:point{x:startingPX,y:startingPY}, moves:moves}, cipherDataStream
}

func Decrypt(credential EncryptedCredential, cipherDataStream []byte) []byte {
	data := make([]byte, 0)
	counter :=0
	px,py := credential.startingPosition.x, credential.startingPosition.y
	dataLength := len(cipherDataStream)
	cipherKey := credential.key
	moves := credential.moves
	direction := moves[counter]
	for recentIndex := 0; recentIndex < dataLength; recentIndex++ {
		data = append(data, cipherDataStream[recentIndex] ^ cipherKey[px][py])
		if (!reachToAside(px, py)) {
			px, py = lib.MoveTowards(direction, px, py)

		} else {
			cipherKey = sBoxOfEachCell(cipherKey)
			counter++
			direction = moves[counter]
			px, py = lib.MoveTowards(direction, px, py)
		}

	}
	return data
}