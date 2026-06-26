package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	fmt.Println("Hello, World!")
	files, err := os.ReadDir("./assets")
	if err != nil {
		log.Fatal(err)
	}

	println(len(files))
	for _, file := range files {
		if file.IsDir() == false {
			var name string = strings.ToLower(file.Name())
			if strings.Contains(name, ".jpg") {
				println(name)
			}
		}
	}
}
