/*
example program for the bench to run for testing
*/
package main

import (
	"fmt"
)

func main() {
	fmt.Println("say hello to example, I'll pretend to do stuff for you")
	for i := range 100 {
		fmt.Print("mieh", i)
	}
}
