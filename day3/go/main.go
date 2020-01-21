package main;

import (
	"io/ioutil"
	"fmt"
)

func get_data(path string) string {
	data, err := ioutil.ReadFile(path);

	if err != nil {
		fmt.Println("error opening file");
		return;
	}
	// fmt.Println(string(data));
	return string(data);
}

func main() {
	fmt.Println("<START>");
	fmt.Println(get_data("../data"));

}