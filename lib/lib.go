package lib

import (
	"math/rand"
	"time"
	"strings"
)

func findRandomNumber(upperLimit int, lowerLimit int) int {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	return r.Intn(upperLimit - lowerLimit) + lowerLimit
}

func swap(string1 uint8, string2 uint8) (uint8, uint8) {
	return string2, string1
}

func Shuffle(column [256] uint8) [256]uint8 {
	var size int = len(column)
	for counter := range column {
		var randomLocation int = findRandomNumber(size, 0)
		column[counter], column[randomLocation] = swap(column[counter], column[randomLocation])
	}

	return column
}

func ChooseRandomPoint(upperLimit int, lowerLimit int) (int, int) {
	return findRandomNumber(upperLimit, lowerLimit), findRandomNumber(upperLimit, lowerLimit)
}

func ChooseRandomDirection(possibleDirections []int) int {
	return possibleDirections[findRandomNumber(len(possibleDirections), 0)]
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

func ByteToString(dataInByte []byte) string {
	return string(dataInByte)
}

func StringToByte(data string) []byte {
	return []byte(data)
}

func GenarateInitialKeyMatrix() [256][256]uint8 {
	keyMatrix := [256][256]uint8{}
	var row, column int

	for row = 0; row <= 255; row++ {
		for column = 0; column <= 255; column++ {
			keyMatrix[column][row] = uint8(column)
		}
	}

	return keyMatrix
}

func CheckError(err error) {
	if (err != nil) {
		panic(err)
	}
}

func CreatePath(folderPath string, fileName string) string {
	if (folderPath != "") {
		paths := strings.Split(fileName, "/")
		fileName = paths[len(paths) - 1];
	}
	if (strings.HasSuffix(folderPath, "/")) {
		return folderPath + fileName;
	}
	if(folderPath == ""){
		return fileName;
	}
	return folderPath + "/" + fileName;
}