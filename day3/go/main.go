/*
	super slow but the funn way to do it :3
*/

package main;

import (
	"io/ioutil"
	"strings"
	"strconv"
	"time"
	"regexp"
	"fmt"
)


func get_data(path string) string {
	data, err := ioutil.ReadFile(path);

	if err != nil {
		fmt.Println("error opening file");
		return "";
		
	}
	// fmt.Println(string(data));
	return string(data);
}

func main() {

	start := time.Now();

	var data string;

	fmt.Println("<START>");
	data = get_data("../data");
	split_pure := strings.Split(data,"\n");
	
	path1 := strings.Split(split_pure[0],",");
	path2 := strings.Split(split_pure[1],",");

	pos1 := find_all(path1);
	pos2 := find_all(path2);

	var best_dist int = 9999999;

	for i := 0; i < len(pos1); i++ {
		if itemExists(pos2, pos1[i]) {
			dist := anti_neg(pos1[i][0]) + anti_neg(pos1[i][1]);
			
			
			if dist < 0 {
				dist = dist - dist - dist;
			}

			if dist < best_dist && dist != 0 {
				best_dist = dist;
			}
		}
	}
	fmt.Println("best dist = ", best_dist);
	fmt.Println((time.Now()).Sub(start));
}
/////////////////////////////////////////////////////////////////////
func itemExists(arr [][]int, pos []int) bool {
	for i := 0; i < len(arr); i++ {
		if arr[i][0] == pos[0] && arr[i][1] == pos[1] {
			return true;
		}
	}
	return false;
}

func anti_neg(data int) int {
	if data < 0 {
		return data - data - data;
	} else {
		return data;
	}
}

func find_all(path []string) [][]int {
	var X int = 0;
	var Y int = 0;
	var out [][]int;
	r,_ := regexp.Compile("(?P<dir>U|D|L|R)(?P<length>[0-9]{1,})");
	
	for i := 0; i < len(path); i++ {
		var Xm int = 0;
		var Ym int = 0;
		args := r.FindStringSubmatch(path[i]);
		
		if args[1] == "U" {
			Ym = 1;
		} else if args[1] == "D" {
			Ym = -1;
		} else if args[1] == "L" {
			Xm = 1;
		} else if args[1] == "R" {
			Xm = -1;
		}

		steps,err := strconv.Atoi(args[2]);

		if err != nil {
			return nil;
		}

		for j := 0; j < steps; j++ {
			X += Xm;
			Y += Ym;

			var l []int = []int{X,Y};

			
			out = append(out,l);
		}
	}
	return out;
}

func max(a,b int) int {
	if(a > b) {
		return a;
	}
	return b;
}