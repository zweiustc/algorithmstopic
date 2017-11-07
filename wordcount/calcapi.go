package main

import (
	"log"
	"io/ioutil"
)


func main() {
    var filename string = "./text.file"
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		log.Fatal(err)
	}
	log.Printf(string(data))
	//calcWord(data)

	var wordMap map[string]int = make(map[string]int, 0)
	string2Word(string(data), wordMap)

	for i,v := range wordMap {
		log.Printf("word = %s, count = %d", i, v)
	}
	
}


func string2Word(data string, wordMap  map[string]int) {		

    //var wordMap map[string]int = make(map[string]int, 0)

	startIndex := 0
	letterStart := false
	for i, v := range data {
        // Letter yes or no
		if (v >=65 && v <=90) || (v >= 97 && v<=122) {
			if !letterStart {
				letterStart = true
				startIndex = i
			}
		} else {
			if letterStart {
				letterStart = false
				wordMap[data[startIndex:i]]++	
			}
		}
	}
	
	if letterStart {
		wordMap[data[startIndex:]]++ 
	}

}
