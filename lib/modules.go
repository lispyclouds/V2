package lib

import (
	"math/rand"
	"time"
)

func FindRandomNumber(upperLimit int, lowerLimit int) int {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))

	return r.Intn(upperLimit - lowerLimit) + lowerLimit
}

func swap(string1 uint8, string2 uint8) (uint8, uint8) {
	return string2, string1
}

func Shuffle(column [256] uint8) [256]uint8 {
	var size int = len(column)
	for counter := range column {
		var randomLocation int = FindRandomNumber(size, 0)
		column[counter], column[randomLocation] = swap(column[counter], column[randomLocation])

	}

	return column
}

func ChooseRandomPoint(upperLimit int, lowerLimit int) (int, int) {
	return FindRandomNumber(upperLimit, lowerLimit), FindRandomNumber(upperLimit, lowerLimit)
}

func ChooseRandomDirection(possibleDirections []int) int {
	return possibleDirections[FindRandomNumber(len(possibleDirections), 0)]
}

func MoveTowards(direction int, px int, py int) (int, int) {
	switch(direction){
	case 0:
		py--;
		break;

	case 1:
		px++;
		py--;
		break;

	case 2:
		px++;
		break;

	case 3:
		px++;
		py++;
		break;

	case 4:
		py++;
		break;

	case 5:
		px--;
		py++;
		break;

	case 6:
		px--;
		break;

	case 7:
		px--;
		py--;
		break;
	}
	return px, py
}
