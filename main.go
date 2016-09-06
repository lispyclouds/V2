package main

import (
	"./V2"
	"./lib"
	"errors"
	"flag"
	"fmt"
	"io/ioutil"
	"strings"
)

func main() {
	isEncrypt := flag.Bool("encrypt", false, "To encrypt data")
	isDecrypt := flag.Bool("decrypt", false, "To decrypt data")
	var sourceFileName, credentialFileName, destinationDirectoryPath string
	flag.StringVar(&sourceFileName, "f", "", "Pass the source file name")
	flag.StringVar(&credentialFileName, "c", "", "Pass the credential file name")
	flag.StringVar(&destinationDirectoryPath, "d", "", "Pass the destination folder path")
	flag.Parse()

	if *isEncrypt {
		if sourceFileName == "" {
			err := errors.New("Please provide source file name to decrypt the data")
			panic(err)
		}

		dataStream, err := ioutil.ReadFile(sourceFileName)
		lib.CheckError(err)
		credential, cipherDataStream := V2.Encrypt(dataStream)
		credentialFilePath := lib.CreatePath(destinationDirectoryPath, sourceFileName+".credential")
		cipherDataPath := lib.CreatePath(destinationDirectoryPath, sourceFileName+".encrypted")
		err = ioutil.WriteFile(credentialFilePath, credential, 0744)
		err = ioutil.WriteFile(cipherDataPath, cipherDataStream, 0744)
		lib.CheckError(err)
		fmt.Println("Encryption successfully completed.\nThe encryted data and credential file paths are following " + cipherDataPath + ", " + credentialFilePath)
		return
	}

	if *isDecrypt {
		if credentialFileName == "" {
			err := errors.New("Please provide credential file name to decrypt the data")
			panic(err)
		}
		if sourceFileName == "" {
			err := errors.New("Please provide source file name to decrypt the data")
			panic(err)
		}

		credentialAsByte, err := ioutil.ReadFile(credentialFileName)
		lib.CheckError(err)
		cipherDataStream, err := ioutil.ReadFile(sourceFileName)
		lib.CheckError(err)
		dataAsByte := V2.Decrypt(credentialAsByte, cipherDataStream)
		sourceFileName = lib.CreatePath(destinationDirectoryPath, sourceFileName)
		decryptedFilePath := strings.Split(sourceFileName, ".encrypted")[0] + ".decrypted"
		err = ioutil.WriteFile(decryptedFilePath, dataAsByte, 0744)
		lib.CheckError(err)
		fmt.Println("Decryption successfully completed.\nThe decrypted file path is " + decryptedFilePath)
	}
}
