package main

import (
	"./V2"
	"./lib"
	"io/ioutil"
	"flag"
)

func main() {
	isEncrypt := flag.Bool("encrypt", false, "To encrypt data");
	isDecrypt := flag.Bool("decrypt", false, "To decrypt data");
	var sourceFileName, credentialFileName, destinationDirectoryPath string
	flag.StringVar(&sourceFileName, "f", "", "Pass the source file name");
	flag.StringVar(&credentialFileName, "c", "", "Pass the credential file name");
	flag.StringVar(&destinationDirectoryPath, "d", "", "Pass the destination folder path");
	flag.Parse();
	if *isEncrypt {
		dataStream, err := ioutil.ReadFile(sourceFileName);
		lib.CheckError(err);
		credential, cipherDataStream := V2.Encrypt(dataStream);
		err = ioutil.WriteFile(lib.CreatePath(destinationDirectoryPath, sourceFileName + ".credential"), credential, 0744)
		err = ioutil.WriteFile(lib.CreatePath(destinationDirectoryPath, sourceFileName + ".encrypt"), cipherDataStream, 0744)
		lib.CheckError(err);
	}
	if *isDecrypt {
		credentialAsByte, err := ioutil.ReadFile(credentialFileName);
		cipherDataStream, err := ioutil.ReadFile(sourceFileName);
		lib.CheckError(err);
		dataAsByte := V2.Decrypt(credentialAsByte, cipherDataStream);
		ioutil.WriteFile(lib.CreatePath(destinationDirectoryPath, sourceFileName + ".decrypt"), dataAsByte, 0744);
	}
}
